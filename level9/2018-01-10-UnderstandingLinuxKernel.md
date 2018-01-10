


# ch8

### 8.1.8 per-CPU page frame cache
To boost system performance, each memory zone defines a per-CPU page frame cache. Each per-CPU cache includes some pre-allocated page frames to be used for single 【page frame 】 memory requests issued by the local CPU.
Actually, there are two caches for each memory zone and for each CPU: a hot cache , which stores page frames whose contents are likely to be included in the CPU's hardware cache, and a cold cache.
准确理解hot cache哟，里面的内存page frame与CPU硬件cache已经建立关联啦！！
又想到CPU硬件cache的三种关联方法【full、direct、N-ways Associative】
