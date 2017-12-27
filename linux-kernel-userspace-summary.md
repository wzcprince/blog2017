
[TOC]

# 用户态
## 进程虚拟地址空间
### malloc()的glibc实现
参见 Linux System Programming 2nd Edition P308 Section Anonymous Memory Mappings

#### buddy memory allocation scheme

## glibc

## socket API
### raw socket
#### PF_INET raw socket直接操作IP层级的报文

例如 NQA 收发 ICMP报文  socket(PF_INET,SOCK_RAW,IPPROTO_ICMP)
- IP_HDRINCL可以自定义IP头
- IP_TOS IP_TTL

#### PF_PACKET raw socket直接操作数据链路层，操作对象是接口/device
linux raw socket - CSDN博客
http://blog.csdn.net/lizhia1221/article/details/51946592


# 同步互斥机制
## 自旋锁 spin lock

## RCU
## MCS自旋锁【好牛叉】
### 降低普通自旋锁cache line bouncing问题
Linux同步机制--MCS自旋锁 | Just another kernel n00b
http://larmbr.com/2014/07/26/mcs-spinlock/

# 内存

# 网络
参考 2010年 Linux 下网络性能优化方法简析
https://www.ibm.com/developerworks/cn/linux/l-cn-network-pt/index.html
【比较古老了，新代码很多已经变化了】

## 收包
### none-NAPI (注意总线地址的概念)
以 
D:\!learn\code\linux-4.4.82\tailored\drivers\net\ethernet\i825xx\82596.c 网卡驱动为例：
#### RX_RING
rfd里存的是标志、状态，
rbd里存的是packet 数据
struct i596_private  :: struct i596_rfd  *rfd_head[RX_RING_SIZE];
struct i596_private  :: struct i596_rbd  *rbd_head[RX_RING_SIZE];

![](http://p14ws25od.bkt.clouddn.com/201712251014_563.png)

#### 初始化 
##### module init , probe device
##### net_device_ops.ndo_open= i596_open
##### request_irq(dev->irq, i596_interrupt,  flags = 0, "i82596", dev)
##### i596_interrupt 调用 i596_rx(struct net_device *dev) 遍历 ring，为packet分配描述符skb和报文数据区
【注意区分两者】 
##### newskb = netdev_alloc_skb(dev, PKT_BUF_SZ);

### NAPI-newer newer
核心结构体 napi_struct
**网卡多接收队列 ** 的时候每个接收队列对应一个napi_struct
``` C
void netif_napi_add(struct net_device *dev, struct napi_struct *napi,
		    int (*poll)(struct napi_struct *, int), int weight)
	list_add(&napi->dev_list, &dev->napi_list);
	napi->dev = dev;
```

#### 以e1000e为例
<http://blog.csdn.net/wzcprince/article/details/78895283>

### RPS RFS
Receive Packet Steering 把软中断的负载均衡到各个cpu
RPS（Receive Packet Steering）主要是把软中断的负载均衡到各个cpu，简单来说，是网卡驱动对每个流生成一个hash标识，这个HASH值得计算可以通过四元组来计算（SIP，SPORT，DIP，DPORT），然后由中断处理的地方根据这个hash标识分配到相应的CPU上去，这样就可以比较充分的发挥多核的能力了。
由于RPS只是单纯把数据包均衡到不同的cpu，这个时候如果应用程序所在的cpu和软中断处理的cpu不是同一个，此时对于cpu cache的影响会很大，那么RFS（Receive flow steering）确保应用程序处理的cpu跟软中断处理的cpu是同一个，这样就充分利用cpu的cache，这两个补丁往往都是一起设置，来达到最好的优化效果, 主要是针对单队列网卡多CPU环境。


### GRO
在 napi\_struct对象中，有一个 GRO 的包的列表 gro\_list，用保存收到的包，然后传递给网络协议层，
比较复杂，以 inet_gro_receive 处理IP报文的合并为例，
** 合并条件： /* All fields must match except length and checksum. */ **
** 还有 tcp4_gro_receive 呢！！ ** 
```
static struct packet_offload ip_packet_offload  = {
	.type = cpu_to_be16(ETH_P_IP),
	.callbacks = {
		.gso_segment = inet_gso_segment,
		.gro_receive = inet_gro_receive,
		.gro_complete = inet_gro_complete,
	},
};

static const struct net_offload tcpv4_offload = {
	.callbacks = {
		.gso_segment	=	tcp4_gso_segment,
		.gro_receive	=	tcp4_gro_receive,
		.gro_complete	=	tcp4_gro_complete,
	},
};

```



### LRO-Large Receive Offload 已被GRO取代


## 发包
### TSO-TCP Segmentation Offload
网卡硬件来做TCP的分片
### GSO-Generic Segmentation Offload
作用，尽量推迟分片的时间点，从而减少内核处理的报文个数，提升效率
**体现batching思想**
相关源代码：
![](http://p14ws25od.bkt.clouddn.com/201712191036_260.png)
也就是在 queue discipline之后，即 dequeue 出来skb以后，才考虑GSO分片

```
static inline bool netif_needs_gso(struct sk_buff *skb,
				   netdev_features_t features)
```

## packet_mmap接口/机制

参见 https://blog.cloudflare.com/kernel-bypass/
重要观点：
- Packet_mmap is a Linux API for fast packet sniffing. While it's not strictly a kernel bypass technique, 
- Since the goal of kernel bypass is to spare the kernel from processing packets, we can rule out packet_mmap. It doesn't take over the packets - it's just **a fast interface for packet sniffing**. 


### 通过socket API、mmap()提供
### 可用于报文接口和发送
 - Capture process
     setsockopt(fd, SOL_PACKET, PACKET_RX_RING, (void *) &req, sizeof(req))
 - Transmission process
     setsockopt(fd, SOL_PACKET, PACKET_TX_RING, (void *) &req, sizeof(req))

https://www.kernel.org/doc/Documentation/networking/packet_mmap.txt

A complete tutorial is available at: http://wiki.gnu-log.net/

## PF_RING

参见 https://blog.cloudflare.com/kernel-bypass/
重要观点：
- PF_RING is another known technique that intends to speed up packet capture. Unlike packet_mmap, 
- plain PF_RING without ZC modules is unattractive since its main goal is to speed up libpcap.

## Userspace I/O UIO
DPDK is a networking framework written in C, created especially for Intel chips. It's similar to snabbswitch in spirit, since it's a full framework and **relies on UIO**.

UIO: user-space drivers [Posted May 2, 2007 by corbet]
https://lwn.net/Articles/232575/

## NetMap

参见 https://blog.cloudflare.com/kernel-bypass/
重要观点：
- Netmap is also a rich framework, but as opposed to UIO techniques it is implemented as a couple of kernel modules. 

http://info.iet.unipi.it/~luigi/netmap/
关键点：
- netmap is a framework for high speed packet I/O. 
- netmap supports access to network cards (NICs), host stack, virtual ports (the "VALE" switch), and "netmap pipes". 
-  It can easily reach line rate on 10G NICs (14.88 Mpps), over 30 Mpps on 40G NICs (limited by the NIC's hardware), over 20 Mpps on VALE ports, and over 100 Mpps on netmap pipes. 
- netmap/VALE can be used to build extremely fast traffic generators, monitors, software switches, network middleboxes, interconnect virtual machines or processes, do performance testing of high speed networking apps without the need for expensive hardware. 
- netmap uses a **select()-able file descriptor** to support blocking I/O, which makes it extremely easy to port applications using, say, raw sockets or libpcap to the netmap API.
- Other frameworks (e.g. DPDK, DNA) achieve similar speeds but lack the ease of use and portability.
- With netmap, it takes as little as 60-65 clock cycles to move one packet between the user program and the wire.
- netmap uses some well known performance-boosting techniques, such as memory-mapping the card's packet buffers, I/O batching, and modeling the send and receive queues as circular buffers to match what the hardware implements. 
- Unlike other systems, applications using netmap cannot crash the OS, because they run in user space and have no direct access to critical resources (device registers, kernel memory pointers, etc.). 
- **The programming model is extremely simple (circular rings of fixed size buffers)**, 
- applications use only standard system calls: non-blocking ioctl() to synchronize with the hardware, and poll()-able file descriptors to wait for packet receptions or transmissions on individual queues.
- netmap **implements a special device, /dev/netmap**, which is the gateway to switch one or more network cards to netmap mode, where the card's datapath is disconnected from the operating system.


https://www.freebsd.org/cgi/man.cgi?query=netmap&sektion=4
     netmap is a framework for extremely fast and efficient packet I/O for both userspace and kernel clients.	 
     It runs on FreeBSD and	Linux, and includes 
	     - VALE, a very fast	and modular in-kernel software switch/data-plane, and	
	     - netmap pipes, a	shared memory packet transport channel.	 All these are accessed interchangeably	with ithe same API.


