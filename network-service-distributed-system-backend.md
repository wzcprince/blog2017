

关于同步异步非阻塞阻塞的终极解析 <http://blog.csdn.net/xx77009833/article/details/12590699>

异步是在强调一个任务异步完成
自己的体会，，，阻塞和非阻塞是在说线程是否等待
https://www.zhihu.com/question/19732473
服务本身有同步和异步之分，同步服务会在返回的时候同时返回结果，异步服务会用其他手段返回结果

阻塞和非阻塞是在说服务请求者自己在请求服务时的状态，如果忙别的事情去了就是非阻塞


两种高性能I/O设计模式(Reactor/Proactor)的比较 
http://blog.jobbole.com/59676/   
Reactor：  epoll + 多线程 同步IO
Proactor： epoll + 异步aio所以linux的aio还是要学习的

服务器和前端的接口订好
研发测试运维
商城要把帐对好
微服务是一种架构

动态数据也要缓存，不用查数据库

# 七层协议
<https://github.com/wzcprince/blog2017/blob/master/network-protocols.md#应用层-七层协议>

# 负载均衡

## 阿里版LVS
高性能负载均衡设计与实现-博客-云栖社区-阿里云
<https://yq.aliyun.com/articles/21889> 

## 爱奇艺DPVS

## GoogleMaglev

Google 是如何做负载均衡的？ 
http://oilbeater.com/%E5%8D%9A%E5%AE%A2/2016/11/21/google-loadbalancert.html
巨牛逼，直接改网卡驱动
Maglev: A Fast and Reliable Software Network Load Balancer 
['mæglɛv]
http://static.googleusercontent.com/media/research.google.com/en//pubs/archive/44824.pdf  

A good summary of popular kernel bypass techniques is presented in [10]. 
[10] Kernel bypass.  http://blog.cloudflare.com/kernel-bypass  . 


最后，虚拟化环境中已经采用Overlay虚拟网络了，所以TUNNEL的方式变得完全多余。而DR方式最大的缺点：需要LB和后端服务器在同一个二层网络，而这在UCloud的虚拟化网络中完全不是问题。主流的SDN方案追求的正是大二层带来的无缝迁移体验，且早已采用各种优化手段(例如ARP代理)来优化大二层虚拟网络。

##Vortex

从Maglev到Vortex，揭秘100G＋线速负载均衡的设计与实现
http://www.infoq.com/cn/articles/Maglev-Vortex





#service


##调用方式

### RPC
基于tcp/ip的

### resetfull
以资源为中心，一般都是HTTP的，

REST 指的是一组架构约束条件和原则。满足这些约束条件和原则的应用程序或设计就是 RESTful。
最重要的 REST 原则是，客户端和服务器之间的交互在请求之间是无状态的。

关于http和rpc的区别（segmentfault上的回答） - - CSDN博客
http://blog.csdn.net/u013063153/article/details/54728592

问题
最近用了谷歌的grpc，所以对rpc和http有一点疑惑，感觉这两个东西功能上是一样的，rpc某个服务监听某一个方法，客户端调用这个方法，返回相应的数据，和http监听某个方法的路由 返回相应的数据好像没有本质上的区别啊？

回答
rpc不仅仅可以用http协议实现。
http只是rpc的载体、传输协议。但是宽泛起来也可以说，是rpc的一种实现。
json（jsonrpc），xml（xmlrpc），protobuf，等都只是一种序列化方法（codec）。
http，tcp，mq等都是传输协议。
rpc中，jsonrpc和xmlrpc一般认为是使用json和xml作为序列化方法，使用http作为传输媒介的rpc协议。
grpc协议，序列化方法是protobuf，传输协议基于HTTP2。


## 消息队列

消息队列的两种模式 - CSDN博客
<http://blog.csdn.net/heyutao007/article/details/50131089>

MQ，互联网架构解耦神器
<http://mp.weixin.qq.com/s?src=11&timestamp=1514986944&ver=614&signature=AKm8LQcHAIlxUi-rz-UzN4bFxchLaPKwl*Wa02maXwRMCMA13Ms55P0D9h5lVx8MHr1zDzM5HdANcmMjf-4FSAnyku5NOKmSXIMRwSrBNRdpgHMFz8rXdcI6dUXPcVkQ&new=1>


### 两种模式
#### 点对点模式
#### 发布订阅模式




# Web服务

What really happens when you navigate to a URL:
http://mp.weixin.qq.com/s?__biz=MjM5OTA1MDUyMA==&mid=201649528&idx=1&sn=003250dbd02fa161b6d076d7650c92f2&scene=2&from=timeline&isappinstalled=0#rd


# serverless 
cloud function 无服务器云函数
云函数

【笔记】《由浅入深SCF无服务器云函数实践》 - CSDN博客
<http://blog.csdn.net/CSDN_duomaomao/article/details/78910588>

##云函数价值

1. 简化架构：函数粒度的微服务架构，使得系统的各个功能天然**解耦**，能像搭积木一样组合自有及外部服务，实现所看即所得的**后台服务**；
2. 简化开发：无需关注底层硬件配置、OS，服务启停、网络收发，故障容灾，服务扩缩容等，只需写最核心的业务逻辑，实现真正的代码即服务；
3. 简化运维：无须关注服务部署，服务器运维，安全管控，扩缩容配置等，且应用能无缝升级，实现无痛切换到DevOps模式。
4. 减少支出：无闲置成本，仅对函数资源大小，执行时间，执行次数按需计费，相对云主机平均5%~15% 的使用率，价格优势明显，实现了最彻底的按需计费。


##运行方法
Q： 代码文件是通过dockerfile打包进容器的吗？这样构建会不会有点慢，像在线执行代码这类的，感觉都很及时。
A： 通过docker file打包成镜像再下载，确实耗时很长，所以实际运行代码没打包到镜像里，而是**直接下发到母机，再将目录挂到容器里面**

##调用方法
Q： 对云函数不是太懂  云函数与函数之间调用是通过http协议吗 还是rpc或者其他方式？
A： 云函数之间调用采用http协议，这是业内cloud function的通用做法，内部模块之间使用rpc通信

Q: 如果一个函数一个容器 那一个项目函数至少几万个吧 这样岂不是要部署上万个容器？
A:  函数被真实调用时，才会去分配容器，同时存在的容器数取决于有多少个函数正在被调用，调用的并发次数是多少，这是云函数的最大价值之一：避免资源闲置

Q：云函数实际应用中，和一般写法有什么不同，有什么缺点？
A：云函数当前支持python2.7, 3.6, node.js 6.10, Java 8等运行环境，可在本地开发编写代码上传，也可在云端直接编写，对比一般程序的写法，**无须实现网络监听，故障容灾，扩容，日志监控等相关代码，极大的减少大家的代码开发量**，缺点是调试不如本地方便，比如不能直接用GDB等工具单步调试




# 相关资源

## SOA实践指南 SOA in practice The Art of Distributed System Design
貌似是TMG主任张旭东推荐的书，说可以少走五年弯路

SOA(Service Oriented Architecture) 

10.3.1 Request/Callback
【想到向GRESM申请标签块的时候，L2VPN会带上LLB的key作为userhandle，GRESM返回结果时带着userhandle】

10.4.2 里提到的 idempotent  [aɪ'dɛmpətənt] ，
 【想到 L2VPN给VPWS申请单个标签的时候，肯定是可以并发请求的，那并发请求如何区分呢？用的是事务号吗？应该不是，因为并发创建bfd用mcm的时候bfd会把pwindex和pwtunneltype(vpws/vpls)返回】







