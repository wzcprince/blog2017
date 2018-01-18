

# 重要思想总结列举
## lockless->并行
举例：
 - 多队列
 - 每个CPU或线程有独立的数据结构
 - DPDK的每个port即网卡会为每个CPU都分配一个tx queue
 - DPDK的mem pool会为每个lcore即逻辑线程都分配一个cache

省掉了
- 多CPU时的cache一致性

## batching
## 增加cache
### 快速路径和慢速路径
- linux kernel中有用，比如VFS的dentry cache
- 阿里版LVS中也提到了

高性能负载均衡设计与实现-博客-云栖社区-阿里云
<https://yq.aliyun.com/articles/218895>
在【LVS的改进】那一节中

## 软硬件充分融合
用软件充分发挥压榨硬件性能
### 特殊指令，比如SIMD
### offloading
### NUMA感知
## 先找到瓶颈在哪里
### NUMA代替SMP

## 权衡折中
### 时间和空间
**主要指CPU时间和内存**
比如
- 数据结构字段对齐，包括4字节对齐、cacheline对齐

### Latency and throughput [出处](http://blog.csdn.net/wzcprince/article/details/78810261# 提升batchinglatency-and-throughput的折中权衡)






# 重要特性列表

## CPU
###  affinity 和 isolation 和polling
让CPU core专心polling，从而避免中断以及线程切换开销

###  SIMD
SIMD单指令多数据优化内存拷贝效率

## cache 
### prefetch
### cache line 对齐
### huge page
提高TLB命中率
### Intel Data Direct I/O技术增加Last Level Cache

## NUMA感知
提升CPU、内存、外设之间的访问速度

## NAPI
**体现batching**
一次中断，多次轮询

## TSO (TCP Segmentation Offload）
利用网卡硬件分割jumbo大数据包，

## GSO(Generic Segmentation Offload)
**体现batching、延缓推迟操作**
将TSO技术一般化，更加体现batching，

## DPDK相关技术
### 用户态驱动，避免内存拷贝和系统调用的开销
### LPM库
### RING库
### Elastic Flow Distributor 












# 典型项目
## dpdk

## ZeroMQ
参见
<https://github.com/wzcprince/blog2017/blob/master/network-service-distributed-system-backend.md#zeromq>

## Firefox多核优化
Firefox是如何充分利用硬件性能恢复极速的？
https://mp.weixin.qq.com/s/upjyzPhmoF0kSrWKyJ3eFQ

细粒度 并行 多核 相通  

