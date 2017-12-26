* auto-gen TOC:
{:toc}


{:toc}


[TOC]

# 内存

# 网络
参考 2010年 Linux 下网络性能优化方法简析
https://www.ibm.com/developerworks/cn/linux/l-cn-network-pt/index.html
【比较古老了，新代码很多已经变化了】

## 收包
### NAPI-newer newer

### __napi_schedule(&adapter->napi) 注意napi代表一个device()&^$%^*+!`,./?
### __napi_schedule(&adapter->napi) 注意napi代表一个device()&^$%^*+!`,./?
### __napi_schedule(&adapter->napi) 注意napi代表一个device()&^$%^*+!`,./?
### __napi_schedule(&adapter->napi) 注意napi代表一个device()&^$%^*+!`,./?
### __napi_schedule(&adapter->napi) 注意napi代表一个device()&^$%^*+!`,./?
### __napi_schedule(&adapter->napi) 注意napi代表一个device()&^$%^*+!`,./?

核心结构体 napi_struct
**网卡多接收队列 ** 的时候每个接收队列对应一个napi_struct
``` C
void netif_napi_add(struct net_device *dev, struct napi_struct *napi,
		    int (*poll)(struct napi_struct *, int), int weight)
	list_add(&napi->dev_list, &dev->napi_list);
	napi->dev = dev;
```

#### only for test 目录
test
##### only for test 目录2
test 
###### only for test 目录3
te

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

## packet_mmap

https://www.kernel.org/doc/Documentation/networking/packet_mmap.txt

