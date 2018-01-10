






# ch8

### 8-1-8 per-CPU page frame cache
To boost system performance, each memory zone defines a per-CPU page frame cache. Each per-CPU cache includes some pre-allocated page frames to be used for single 【page frame 】 memory requests issued by the local CPU.
Actually, there are two caches for each memory zone and for each CPU: a hot cache , which stores page frames whose contents are likely to be included in the CPU's hardware cache, and a cold cache.
准确理解hot cache哟，里面的内存page frame与CPU硬件cache已经建立关联啦！！
又想到CPU硬件cache的三种关联方法【full、direct、N-ways Associative】


### 8-2-8
linux内核slab的object descriptor、slab descriptor与实际的object占用的内存块有两种组织分配方式
与dpdk的rte_mbuf也是一个事，dpdk rte_mbuf用的是internal方式

![](http://p14ws25od.bkt.clouddn.com/201801102158_32.png)

### 8-2-11 slab per-cpu local cache


To reduce spin lock contention among processors and to make better use of the hardware caches, each cache of the slab allocator includes a per-CPU data structure consisting of a small array of pointers to freed objects called **the slab local cache**. Most allocations and releases of slab objects affect the local cache only; the slab data structures get involved only when the local cache underflows or overflows. This technique is quite similar to the one illustrated in the section "The Per-CPU Page Frame Cache" earlier in this chapter.

