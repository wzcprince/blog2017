
[TOC]

# 用户态
## VFS Interface【至关重要】
### VFS是极为重要的接口，不要老想着那一坨API

还有这三个device file呢：！
/dev/stdin       /dev/stdout       /dev/stderr
https://github.com/nginxinc/docker-nginx/blob/14aa3b1b80341099afbf90eb0a9b9061b7145f18/mainline/stretch/Dockerfile 中： 
forward request and error logs to docker log collector
RUN ln -sf /dev/stdout /var/log/nginx/access.log \
    && ln -sf /dev/stderr /var/log/nginx/error.log
就可以把标准输出重定向到access.log。。。
然后启动主进程：  CMD ["nginx", "-g", "daemon off;"]

### /proc/self/mounts
root@ubuntu:/mnt/hgfs/learn/for_linux_vm# ll /proc/mounts 
lrwxrwxrwx 1 root root 11 Oct 27 20:25 /proc/mounts -> self/mounts 即/proc/self/mounts
会列出所有mount的文件系统，
例如：
cgroup /sys/fs/cgroup/cpu
hugetlbfs /dev/hugepages hugetlbfs rw,relatime 0 0
mqueue /dev/mqueue



## glibc其他

- mallinfo()
#include <malloc.h> struct mallinfo mi;  mi = mallinfo(); 
C语言库函数，用来输出内存分配占用情况
- test2

## pthread

POSIX 信号量可以用memory mapped file＋pthread mutex＋ pthread condition variable实现，此时pthread mutex和pthread condition variable需要pthread_process_shared属性，这个属性的处理会有哪些特别之处呢？？看一下glibc和kernel的代码！！！



## socket API
### PF_INET

#### raw socket直接操作IP层级的报文

linux raw socket 【主要讲 PF_INET raw】
http://blog.csdn.net/lizhia1221/article/details/51946592

例如 NQA 收发 ICMP报文  socket(PF_INET,SOCK_RAW,IPPROTO_ICMP)
- IP_HDRINCL可以自定义IP头
- IP_TOS IP_TTL
- 内核相关
	- raw_local_deliver(skb, protocol);
		- raw_v4_hashinfo
		- hash函数就是直接取第八位 哈希桶有256个 拉链法解冲突

### PF_PACKET socket直接操作数据链路层，操作对象是接口/device

Packet sockets are used to receive or send raw packets at the device driver (OSI Layer 2) level.  
参见 http://man7.org/linux/man-pages/man7/packet.7.html

linux Packet socket (1)简介 - CSDN博客
http://blog.csdn.net/youfuchen/article/details/29782191

使用 PF_PACKET的经典应用 libpcap，netsniﬀ-ng

#### 创建
- packet_socket = socket(AF_PACKET, int socket_type, int protocol);
	- socket_type
		- SOCK_RAW, 那么我们得到的数据包含所有的L2 header和payload
		- SOCK_DGRAM, 那么我们收到的数据会去掉L2的header，是IP header和payload
	- protocol 指定抓取的packet类型
		- ETH_P_IP ETH_P_ARP ETH_P_ALL	
- 内核对应
	- packet_create(struct net *net, struct socket *sock,  int protocol,...)
		
		- 创建packet_type与ip_packet_type arp_packet_type 平级的！！
		- 指定packet_type::func为 packet_rcv(struct sk_buff *skb, struct net_device *dev,
		      struct packet_type *pt, struct net_device *orig_dev)
		- packet_rcv时 __skb_queue_tail(&sk->sk_receive_queue, skb);
		       
	- ptype_all链表里存所有接口的protocol == ETH_P_ALL的packet raw socket
	- skb->dev->ptype_all 链表里存bind接口的protocol == ETH_P_ALL的packet raw socket
	- ptype_base[PTYPE_HASH_SIZE == 16] 存protocol == ETH_P_IP/ETH_P_ARP的
	
#### 绑定到某个接口/device
- bind()
- 结构体 sockaddr_ll
- if_nametoindex()

### PF_UNIX

参见  http://man7.org/linux/man-pages/man7/unix.7.html  
sockets for local interprocess communication

半虚拟化时，vhost和virtio之间通过Unix address family通信！


### PF_NETLINK

参见 http://man7.org/linux/man-pages/man7/netlink.7.html 
communication between kernel and user space (AF_NETLINK)







# 进程管理
## scheduler
Completely Fair Scheduler 

LKD P66 Yielding Processor Time 

CPU isolation 把某个CPU核从linux scheduler中剔除
sys_sched_yield() -> fair_sched_class:: yield_task_fair

完全公平调度器 - 维基百科，自由的百科全书
https://zh.wikipedia.org/wiki/%E5%AE%8C%E5%85%A8%E5%85%AC%E5%B9%B3%E6%8E%92%E7%A8%8B%E5%99%A8
选取花费CPU执行时间最少的进程来进行调度。CFS主要由sched_entity 内含的 vruntime所决定，
不再跟踪process的sleep time，并放弃active/expire的概念, 
【哈哈，应该就是说不按时间片来了，死循环的进程不会expire】
runqueue里面所有的进程都平等对待，CFS使用“虚拟运行时”（virtual running time）来表示某个任务的时间量。

那天和佳雨讨论的，死循环的时候CPU 100%
那操作系统的CPU利用率是如何计算出来的呢？？？
windows 7四核CPU的时候单线程死循环，
CPU利用率是25%
cat /proc/stat
cpu0 19214 0 12677 6147030 846 0 322 0 0 0

## 同步互斥机制
### 自旋锁 spin lock

### RCU

linux 内核的rcu 比如 rcu_dereference 也是一种lockless技术吧

Linux Kernel RCU: What is RCU?
The basic idea behind RCU is to split updates into "removal" and "reclamation" phases.

### MCS自旋锁【好牛叉】
#### 降低普通自旋锁cache line bouncing问题
Linux同步机制--MCS自旋锁 | Just another kernel n00b
http://larmbr.com/2014/07/26/mcs-spinlock/



## 进程虚拟地址空间
### malloc()的glibc实现
malloc也有buddy scheme
参见 Linux System Programming 2nd Edition P308 Section Anonymous Memory Mappings
**学习一下malloc的glibc实现，很牛叉的哟 **

#### buddy memory allocation scheme


## zombie
僵尸进程 父进程没有wait()它创建的子进程
而父进程一直在长时间执行，

## orphan
父进程提前结束，则会被 init进程收养，init进程会循环地wait()这些orphan，所以orphan并没有什么危害
注意和zombie的差别






# cache

cache line bouncing 和 MAC flapping

## cacheline对齐
内核源代码里到处都是 ____cacheline_aligned 

## cache line bouncing

### MCS
参见 [#mcs自旋锁好牛叉](#mcs自旋锁好牛叉)

### slab_coloring
ULK 8.2.10 slab coloring机制用来解决cache line bouncing问题
Objects that have the same offset within different slabs will, with a relatively high
probability, end up mapped in the same cache line. The cache hardware might therefore waste
memory cycles transferring two objects from **the same cache line back and forth to different RAM
locations, while other cache lines go underutilized**. The slab allocator tries to reduce this unpleasant
cache behavior by a policy called slab coloring : different arbitrary values called colors are assigned
to the slabs.

Coloring essentially leads to moving some of the free area of the slab from the end to the beginning.
![](http://p14ws25od.bkt.clouddn.com/201712291648_167.png)

在glibc中也有类似机制，可以搜索glibc代码 COLORING_INCREMENT 或者 allocate_stack(...)

# 内存

## mmap【太重要了】
### 用于共享内存
mmap和POSIX SystemVSystemV共享内存的区别描述符的获取手段

### 用于packet_mmap
[teste](#packet_mmap接口机制)
https://github.com/wzcprince/blog2017/blob/master/linux-kernel-userspace-summary.md#packet_mmap接口机制

### hugepage

## barrier

内存屏障和锁机制对比

内存屏障的作用：barrier() - CSDN博客
http://blog.csdn.net/cyx1231st/article/details/9262893  
内存屏障主要解决了两个问题：单处理器下的乱序问题和多处理器下的内存同步问题。

LINUX内核内存屏障 翻译 Documentation/memory-barriers.txt
http://blog.chinaunix.net/uid-9918720-id-1640912.html 

http://blog.csdn.net/wzcprince/article/details/78835595#准备工作-l2504-l2507  

## NUMA
Linux 的 NUMA 技术
https://www.ibm.com/developerworks/cn/linux/l-numa/index.html


## sys_sendfile和sys_splice核心实现

- sys_sendfile是借助pipe_inode_info对象来实现，
	- 先从in_fd中读数据splice拼接到pipe
	- 再从pipe splice到out_fd

- sys_splice是从文件splice到pipe


两个系统调用的实现过程中，在读文件的时候如果不用page cache，则会用 default_file_splice_read
![](http://p14ws25od.bkt.clouddn.com/201712290851_58.png)

Efficient data transfer through zero copy
<https://www.ibm.com/developerworks/linux/library/j-zerocopy/>


## 内存其他相关专题


/proc/meminfo的实现： 函数 meminfo_proc_show 其他的proc见proc_create 和proc_create_data


与dpdk中的memory pool类似，linux kernel中与之对应的是slab
linux内核中也有memory pool，但一般都是紧急情况下或者给某个子系统专用的，一般情况下并不会用，分两种：
ULK 8.1.4 The Pool of Reserved Page Frames

However, some kernel control paths cannot be blocked while requesting memory, for instance, when handling an interrupt or when executing code inside a critical region. In these cases, a kernel control path should issue atomic memory allocation requests (using the **GFP_ATOMIC** flag; see the later section "The Zoned Page Frame Allocator"). An atomic request never blocks: if there are not enough free pages, the allocation simply fails. Although there is no way to ensure that an atomic memory allocation request never fails, the kernel tries hard to minimize the likelihood of this unfortunate event. In order to do this, the kernel reserves a pool of page frames for atomic memory allocation requests to be used only on low-on memory conditions.

...page frames can be used only to satisfy atomic
memory allocation requests issued by interrupt handlers or inside critical regions.

ULK 8.2.15 Memory Pools
reserve of dynamic memory that can be used only by a specific kernel component,
namely the "owner" of the pool. The owner does not normally use the reserve;
。。。 Generally speaking, however, a memory pool can be used to allocate every kind of dynamic memory, from whole page frames to small memory areas allocated with kmalloc(). Therefore, we will generically refer to the memory units handled by a memory pool as "memory elements."





# VFS The Common File Model

VFS mount 和 superblock的数据结构关系？？？
mount的文件系统挂载点本身也是树形结构！！
struct mount的成员
- list_head mnt_mounts  // list of children, anchored here.
- list_head mnt_child

函数__attach_mnt(mount* , )






# 网络


linux内核networking网络文档目录：
https://www.kernel.org/doc/Documentation/networking/00-INDEX  

RSS: Receive Side Scaling 网卡硬件实现
RPS: Receive Packet Steering Google软件
RFS: Receive Flow Steering
Accelerated Receive Flow Steering
XPS: Transmit Packet Steering

参见 
https://www.kernel.org/doc/Documentation/networking/scaling.txt  
D:\!learn\code\linux-4.4.82\full\Documentation\networking\scaling.txt

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

### RPS和RFS（Google补丁）
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

### queue discipline 
linux内核如何做Qos也叫Traffic Control的呢？？
LNI里叫 《the Traffic Control queuing disciplines》
ch11 Frame Transmission -》 dev_queue_xmit Func -》 Queueful devices：
When it exists, the queuing discipline of the device is accessible through dev->qdisc.
The input frame is queued with the enqueue virtual function, and one frame is then dequeued and transmitted via qdisc_run, described in detail in the section “Queuing Discipline Interface.”


●queue discipline参见函数 __dev_queue_xmit(struct sk_buff *skb, void *accel_priv)
txq = netdev_pick_tx(dev, skb, accel_priv);
从net_device::_tx[]中选择一个netdev_queue
然后用netdev_queue->qdisc->enqueue(skb, qdisc)
然后 __qdisc_run(q);它会 skb = qdisc->dequeue并持续 weight_p == 64个报文
多余的报文就要等到 raise_softirq_irqoff(NET_TX_SOFTIRQ); 了

__qdisc_run(struct Qdisc *q)是个很重要的函数，他的两个调用者也很重要！！！


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





# 块设备


18.2 Ext2 Disk Data structure的图
以及 ext2_inode 和 ext2_inode_info P717 P724
ext2_superblock 和 ext2_sb_info  P715 
gendisk即整个磁盘有superblock吗？
----回答，整个磁盘有MBR 主引导记录 里面有partition table和BootLoader
fdisk工具可以修改partition table中的记录的active flag










# 重点专题

## 多线程

### Thread Control Block


### Thread Local Storage 

#### 静态TLS
2017年10月19日 GCC支持静态TLS变量： 
D:\!learn\code\glibc\glibc-2.23\csu\errno.c中 __thread int errno;
#### 动态TLS
pthread_key_create (&thread_key1, NULL); 创建的是动态TLB


### CPU affinity
#### 线程的CPU affinity 线程绑核
Linux下的绑核命令——taskset - 时间轨迹
http://time-track.cn/taskset-command.html  

Linux 线程绑核 - dzqabc - 博客园
http://www.cnblogs.com/dongzhiquan/archive/2012/02/15/2353215.html
【注意啊，每个CPU都有 runqueue 哟 】

CPU isolation 把某个CPU核从linux scheduler中剔除

#### 中断的CPU affinity

### 试验
#### 测试TCB和TLS

gcc test_thread_tcb_tls.c -g -lpthread -o test_thread_tcb_tls 
[test_thread_tcb_tls.c](./res/test_thread_tcb_tls.c)


pthread_create(3) - Linux manual page
<http://man7.org/linux/man-pages/man3/pthread_create.3.html>
pthread_join(3) - Linux manual page
<http://man7.org/linux/man-pages/man3/pthread_join.3.html>

#### 僵尸线程
和僵尸进程类似，也有僵尸线程
gcc  test_thread_zombie.c -g -lpthread -o test_thread_zombie
[test_thread_zombie.c](./res/test_thread_zombie.c)
ps -aux | grep  test_thread_zombie | grep -v grep | awk '{print $2}' | xargs pmap

stage 2 main thread sleeping的时候
pmap命令行的结果是大量的线程占用了进程大量的虚拟地址空间

而stage 4 main thread end pthread_join and sleep again的时候
pmap命令行的结果就是很干净了，内存就都被释放啦
	
	printf ("stage 1 main thread create slave threads \n");
	for (int i = 0; i<thread_count; i++)
	{
	    pthread_create(arr_thread + i, NULL, new_thread_routine, NULL);
	}
	
	printf ("stage 2 main thread sleeping\n");
	sleep_second(15);
	
	printf ("stage 3 main thread start pthread_join\n");
	
	for (int i = 0; i<thread_count; i++)
	{
	    pthread_join(arr_thread[i], &result);
	}
	
	printf ("stage 4 main thread end pthread_join and sleep again\n");
	sleep_second(15); 

#### pthread_create

注意，线程有两个栈，内核线程栈和用户态线程栈

- __pthread_create_2_1 
	- 线程的用户态栈allocate_stack 
		- case 1 pthread_attr::flags & ATTR_FLAG_STACKADDR 调用者已经分配好了
		- case 2 用 list_head stack_cache 中的
		- case 3 mmap MAP_PRIVATE | MAP_ANONYMOUS | MAP_STACK
			- 注意 COLORING_INCREMENT 宏，在[#slab_coloring](#slab_coloring)中有类似机制


## 虚拟化专题

### libvert
libvirt: libvirt Application Development Guides
https://libvirt.org/devguide.html

libvert 的位置！！！！！
原文链接 https://wenku.baidu.com/view/28f710240242a8956aece4bd.html    
![](http://p14ws25od.bkt.clouddn.com/201712281649_609.png)

### 半虚拟化
半虚拟化 virtio 和 vhost 在linux内核里实现貌似不复杂：
![](http://p14ws25od.bkt.clouddn.com/201712281651_830.png)
![](http://p14ws25od.bkt.clouddn.com/201712281651_91.png)








## 性能专题

Linux 系统性能分析工具图解读(一) 
http://oilbeater.com/linux/2014/09/08/linux-performance-tools.html

Linux Performance 
http://www.brendangregg.com/linuxperf.html

### 很好玩的试验
The precise meaning of I/O wait time in Linux
https://veithen.github.io/2013/11/18/iowait-linux.html
其中的这个试验很好玩呀！！！：：：
taskset 1 dd if=/dev/sda of=/dev/null bs=1MB
taskset 1 sh -c "while true; do true; done"

## sendfile和splice

splice系统调用实现的TCP代理 - Netfilter,iptables/OpenVPN/TCP guard:-( - CSDN博客
http://blog.csdn.net/dog250/article/details/17061537
正如Linus所说，splice实际上是内核空间的read/write，而tee则是内核空间的memcpy，至于sendfile，它只是一种特定的优化，该优化对于可以使用page cache的文件系统有效。


## CLI技巧

最实用的 Linux 命令行使用技巧
http://mp.weixin.qq.com/s/HbP5VwpWfQkyeWISCrOD7w

### shell

#### heredoc-format 

- Here document - Wikipedia
<https://en.wikipedia.org/wiki/Here_document#Unix_shells>

In computing, a here document (here-document, here-text, heredoc, hereis, here-string or here-script) is a file literal or input stream literal: it is a section of a source code file that is treated as if it were a separate file. The term is also used for a form of multiline string literals that use similar syntax, preserving line breaks and other whitespace (including indentation) in the text.
Here documents originate in the Unix shell, and are found in sh, csh,[1] ksh, bash and zsh, among others.


- linux - How does "cat << EOF" work in bash? - Stack Overflow
<https://stackoverflow.com/questions/2500436/how-does-cat-eof-work-in-bash>
From man bash:Here Documents
This type of redirection instructs the shell to read input from the current source until a line containing only word (with no trailing blanks) is seen.

##### 实例1
7. Virtio_user for Container Networking — Data Plane Development Kit 18.02.0-rc0 documentation
http://www.dpdk.org/doc/guides/howto/virtio_user_for_container_networking.html
cat <<EOT >> Dockerfile
FROM ubuntu:latest
WORKDIR /usr/src/dpdk
COPY . /usr/src/dpdk
ENV PATH "$PATH:/usr/src/dpdk/x86_64-native-linuxapp-gcc/app/"
EOT


### systemd

systemd System and Service Manager
和init一样PID=1
注意哟，**systemd也是linux系统启动过程中重要的一部分**

源代码： <https://github.com/systemd/systemd>
官方wiki <https://www.freedesktop.org/wiki/Software/systemd/>

浅析 Linux 初始化 init 系统，第 3 部分: Systemd
<https://www.ibm.com/developerworks/cn/linux/1407_liuming_init3/index.html>

The Story Behind 'init' and 'systemd': Why 'init' Needed to be Replaced with 'systemd' in Linux
<https://www.tecmint.com/systemd-replaces-init-in-linux/>



#### systemd关键点
- PID=1
- 强调spelling必须是 systemd
- aggressive parallelization capabilities**并行化大大加速了linux系统启动过程**
- 使用control groups即cgroup实现进程追踪和生命周期管理
	- CGroup 提供了类似文件系统的接口，使用方便。当进程创建子进程时，子进程会继承父进程的 CGroup。因此无论服务如何启动新的子进程，所有的这些相关进程都会属于同一个 CGroup，systemd 只需要简单地遍历指定的 CGroup 即可正确地找到所有的相关进程，将它们一一停止即可。
- 如果所有的 Linux 发行版都采纳了 systemd，那么系统管理任务便可以很大程度上实现标准化。
- 未完待续


#### systemctl





### 日志log
http://man7.org/linux/man-pages/man1/journalctl.1.html

http://man7.org/linux/man-pages/man3/syslog.3.html

技术|用系统日志了解你的 Linux 系统
https://linux.cn/article-9150-1.html

#### 后台进程-daemon-二进制格式-journalctl
#### var-log-plain-text-format

### gdb

gdb file 命令
gdb frame命令


### iproutes工具包

ip link set ens38 up
ip address add 1.1.1.1/24 dev ens38

ip route add default via 192.168.11.2 dev ens38
ip route replace default via 192.168.11.2 dev ens38

ip neighbor add 192.168.11.2  lladdr  00:0c:29:0f:d8:05 nud permanent dev ens38
ip neighbor change 192.168.11.2  lladdr  00:0c:29:0f:d8:05 nud permanent dev ens38



