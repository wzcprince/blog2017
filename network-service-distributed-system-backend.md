

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


# RPC

## resetfull
restful是一种rpc调用方式，现在用的是http加json

# Web服务

What really happens when you navigate to a URL:
http://mp.weixin.qq.com/s?__biz=MjM5OTA1MDUyMA==&mid=201649528&idx=1&sn=003250dbd02fa161b6d076d7650c92f2&scene=2&from=timeline&isappinstalled=0#rd



# 相关资源

## SOA实践指南 SOA in practice The Art of Distributed System Design
貌似是TMG主任张旭东推荐的书，说可以少走五年弯路

SOA(Service Oriented Architecture) 

10.3.1 Request/Callback
【想到向GRESM申请标签块的时候，L2VPN会带上LLB的key作为userhandle，GRESM返回结果时带着userhandle】

10.4.2 里提到的 idempotent  [aɪ'dɛmpətənt] ，
 【想到 L2VPN给VPWS申请单个标签的时候，肯定是可以并发请求的，那并发请求如何区分呢？用的是事务号吗？应该不是，因为并发创建bfd用mcm的时候bfd会把pwindex和pwtunneltype(vpws/vpls)返回】





