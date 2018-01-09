

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

# 万维网-互联网

百度百科万维网
<http://baike.baidu.com/link?url=JJpWdlmiF42ac28C3VEWe_UA9pSEap3t3bHKsJLeN76DnBzY1HN6FOsK5RctR809lwZXMQKWup71xuJu8Jzp2DvwkxbxSekNaSN7lSjAcOa>

万维网并不等同互联网，万维网只是互联网所能提供的服务其中之一，是靠着互联网运行的一项服务。其他服务比如电子邮件、ftp等


## URL

- 为什么，有的URL中要求有WWW而有的却不需要呀::
通俗的说，domain.com 是一级域名，而在这之前的任何名称，比如 anything.domain.com 都是二级域名。因此实际上，www.domain.com 是域名 domain.com 的一个二级域名，只不过是一个比较特殊的二级域名罢了。他的特殊就在于现在的实践中，人们在解析域名的的时候，在惯例和默认的情况下，是把 www.domain.com 这个二级域名指向它的一级域名 domain.com。因此，现在的情况时，domain.com 和 www.domain.com，都是一样的，有和没有 www 一般没有关系。
但是如果在解析域名的时候，没有做这样的设定，也可能就会有区别。







# 七层协议
<https://github.com/wzcprince/blog2017/blob/master/network-protocols.md#应用层-七层协议>

## https

- HTTPS及HTTPS中间人攻击 - 51CTO.COM
<http://netsecurity.51cto.com/art/201702/531356.htm>
	- 2017年6月14日 读后总结，关键字： 
非对称加密，客户端发起请求，服务器端返回公钥给客户端
客户端生成对称加密用的随机值，并用公钥加密后返回给服务器
服务器拿私钥解密得到对称加密用的随机值，
以后的请求响应都用此随机值进行对称加密解密






# cloud-native
Cloud-Native | Pivotal
<https://pivotal.io/cloud-native>

- 再见MME…5G核心网你彻底变了！ | SDNLAB | 专注网络创新技术
<http://www.sdnlab.com/19818.html >
	- SOA
	- Cloud Native
		- 微服务
		- container
		- 敏捷
		- DevOps
	- 5G网络毫秒级时延的KPI
		- 内容下沉和分布式的部署于接入网侧（边缘数据中心），使之更接近用户，降低时延和网络回传负荷
	- 网络切片 slicing
		- 5G要像一把瑞士军刀一样，多功能满足差异化的网络服务。
			- 工业自动化要求低时延、高可靠但对数据速率要求不高
			- 高清视频无需超低时延但要求超高速率
			- 一些大规模物联网不需要切换，部分移动性管理对之而言是信令浪费等等
		- Qos不同



## cloud-native定义

Organizations require a platform

- for building and operating cloud-native applications and services 
- that automates and integrates the concepts of 
	- **DevOps, continuous delivery, microservices, and containers**

### microservices

Microservices | Pivotal
<https://pivotal.io/microservices>

Microservices refers to an architectural approach that independent teams use to prioritize the continuous delivery of single-purpose services. 
The microservices model is **the opposite of traditional monolithic software** which consists of tightly integrated modules that ship infrequently and have to scale as a single unit. 




# SOA
Service Oriented Architecture
也有叫SBA的， Service Based Architecture

SOA和cloud-native是什么关系？








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


##帖子

负载均衡原理的解析 - 源子姗
<https://my.oschina.net/u/3341316/blog/877206>






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













# 消息队列

消息队列的两种模式 - CSDN博客
<http://blog.csdn.net/heyutao007/article/details/50131089>

MQ，互联网架构解耦神器
<http://mp.weixin.qq.com/s?src=11&timestamp=1514986944&ver=614&signature=AKm8LQcHAIlxUi-rz-UzN4bFxchLaPKwl*Wa02maXwRMCMA13Ms55P0D9h5lVx8MHr1zDzM5HdANcmMjf-4FSAnyku5NOKmSXIMRwSrBNRdpgHMFz8rXdcI6dUXPcVkQ&new=1>

大型网站架构之分布式消息队列  http://blog.csdn.net/shaobingj126/article/details/50585035

大型网站架构系列：分布式消息队列（一） - ITFLY8架构师之家 - 博客园
http://www.cnblogs.com/itfly8/p/5155983.html
大型网站架构系列：消息队列（二） - ITFLY8架构师之家 - 博客园
http://www.cnblogs.com/itfly8/p/5156155.html

### 两种模式
#### 点对点模式
#### 发布订阅模式


### 典型项目

#### ZeroMQ

大型网站架构之分布式消息队列 5.3 ZeroMQ
<http://blog.csdn.net/shaobingj126/article/details/50585035#t18>

ZMQ并不像是一个传统意义上的消息队列服务器，事实上，它也根本不是一个服务器，更像一个底层的网络通讯库，在Socket API之上做了一层封装，将网络通讯、进程通讯和线程通讯抽象为统一的API接口。支持“Request-Reply “，”Publisher-Subscriber“，”Parallel Pipeline”三种基本模型和扩展模型。















# Web服务

What really happens when you navigate to a URL:
http://mp.weixin.qq.com/s?__biz=MjM5OTA1MDUyMA==&mid=201649528&idx=1&sn=003250dbd02fa161b6d076d7650c92f2&scene=2&from=timeline&isappinstalled=0#rd

Web server调研分析 - 百度技术博客 - 51CTO技术博客
<http://baidutech.blog.51cto.com/4114344/743732>

Web 前后端分离的意义大吗？ - 知乎
<https://www.zhihu.com/question/28207685

## Nginx
Nginx（发音同 engine x）
<http://nginx.org/en/docs/beginners_guide.html>


- nginx源码分析 http://www.360doc.com/content/10/1115/18/61151_69615382.shtml 
	- 不过各个部分之间耦合的比较厉害，很难把其中某个部分的实现拆出来使用。对于这样一个中大型的复杂系统源码进行分析，是有一定的难度的，刚开始也很难找到下手的入口，所以做这样的事情就必须首先明确目标和计划。
	- 看了几天的源码，进度很慢，过于关注代码实现的细节了，反而很难看清整体结构。于是问诸google寻找方法。大体上分析源代码都要经历三遍过程，第一遍是浏览，通过阅读源码的文档和注释，阅读接口，先弄清楚每个模块是干什么的而不关心它是怎么做的，画出架构草图；第二遍是精读，根据架构草图把系统分为小部分，每个部分从源码实现自底向上的阅读，更深入细致的理解每个模块的实现方式以及与模块外部的接口方式等，弄明白模块是怎么做的，为什么这样做，有没有更好的方式，自己会如何实现等等问题；第三遍是总结回顾，完善架构图，把架构图中那些模糊的或者空着的模块重新补充完善，把一些可复用的实现放入自己的代码库中。


## libev
libev 设计分析 - CNode技术社区
<https://cnodejs.org/topic/4f16442ccae1f4aa270010a3


## IO模型

linux AIO （异步IO） 那点事儿 - CNode技术社区
<https://cnodejs.org/topic/4f16442ccae1f4aa270010a7




# container

区分docker和容器哟，docker只是容器的一种而已，Rocket也是容器

容器的好处 <https://kubernetes.io/docs/concepts/overview/what-is-kubernetes/#why-containers>

### container核心理念价值-解耦

container 是 new model of deployment
kubernetes之所以能 “automates the distribution and scheduling of application containers **across a cluster** in a more efficient way”，就是因为**Containerized applications** are packaged and **decoupled from individual host**
参见 <https://kubernetes.io/docs/tutorials/kubernetes-basics/cluster-intro/>



## docker

十分钟万台服务器部署能力，探秘阿里双十一弹性扩容背后的技术故事
<https://mp.weixin.qq.com/s/55PNpRXS8dgHNs5XiNHAKA>

### docker用namespace
<https://docs.docker.com/engine/docker-overview/#namespaces>



## rocket


## pouch
阿里 ali-pouch [paʊtʃ]
D:\!learn\code\from_github\hangzhouYunQi2017ppt\容器技术专场\E-2-5+11.00AM+容器技术专场+No.4+孙宏亮.pdf
2016年双十一就开始用了，容器实例数达到几十万个

## 技术趋势

1.2017是容器之年？不，也许2018年才是！
<https://mp.weixin.qq.com/s/kbKnVCegGSLME2N_B60flQ>
Linux基金会 开放容器标准（OCI） OCI标准


> 因为相比一个非常复杂的OpenStack环境，它确实更容易在裸金属环境中创建。
> 本月初（2017年12月份）亚马逊声称裸金属将作为一个服务，也就有了很明确的原因，他说：“我们知道亚马逊是最听客户话的。”

**也就是说让docker直接跑在 bare metal上，整个系统看起来会更简单，要避免OpenStack，它太复杂了**


2.


# kubernetes

Kubernetes Documentation | Kubernetes
<https://kubernetes.io/docs/home/>


十分钟带你理解Kubernetes核心概念 - DockOne.io
<http://dockone.io/article/932>

## kubernetes是什么
源自希腊语 飞行员或者船舵手的意思，简称K8S

<https://kubernetes.io/docs/concepts/overview/what-is-kubernetes>
Kubernetes is an open-source platform designed to automate deploying, scaling, and operating application containers.
我理解就是在cluster上玩转容器，
cluster就是一组Node，每个Node可以是物理机或者虚拟机
container 可以是 docker 也可以是 Rocket 

What Kubernetes is not
- **Does not provide middleware (e.g., message buses), data-processing frameworks (for example, Spark), databases (e.g., mysql), nor cluster storage systems (e.g., Ceph) as built-in services. Such applications run on Kubernetes**.


## kubernetes核心要素
从大到小
### cluster
Node组成的集群

### Master Node
#### API server
REST端点

Kubernetes API
<https://kubernetes.io/docs/reference/glossary/?fundamental=true#term-kubernetes-api>
The API allows configuration to be managed in a declarative way. Users can interact with the Kubernetes API directly, or via tools like kubectl. 

#### Replication Controller

#### Service
<https://kubernetes.io/docs/reference/glossary/?fundamental=true#term-service>

An API object that describes how to access applications, such as a set of Pods, and can describe ports and load-balancers.
The access point can be internal or external to the cluster.



### Minion
参见Standardized Glossary | Kubernetes
<https://kubernetes.io/docs/reference/glossary/?fundamental=true#term-node>
['mɪnɪən] n. 宠儿；宠臣；部下；奴才 n. 小黄人（卡通角色）
Kubernetes worker Node 

#### Pod
The smallest and simplest Kubernetes object. A Pod represents a set of running containers on your cluster.

#### Label




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


## JSON
参见 <http://www.w3school.com.cn/json/>
可以对比 protobuf 二进制的**对象序列化**方法

JSON：JavaScript 对象表示法（JavaScript Object Notation）。
JSON 是存储和交换文本信息的语法。类似 XML。
JSON 比 XML 更小、更快，更易解析。
JSON 指的是 JavaScript 对象表示法（JavaScript Object Notation）
JSON 是轻量级的文本数据交换格式
JSON 独立于语言 *
JSON 具有自我描述性，更易理解
* JSON 使用 JavaScript 语法来描述数据对象，但是 JSON 仍然独立于语言和平台。JSON 解析器和 JSON 库支持许多不同的编程语言。
JSON - 转换为 JavaScript 对象
JSON 文本格式在语法上与创建 JavaScript 对象的代码相同。
由于这种相似性，无需解析器，JavaScript 程序能够使用内建的 eval() 函数，用 JSON 数据来生成原生的 JavaScript 对象。


## protobuf





## 日订单峰值破40万！58速运订单调度系统架构大解密
<https://mp.weixin.qq.com/s?src=11&timestamp=1515374663&ver=623&signature=6KGHQcsBueu2NzlzyECSoYhesFRZfXbadjzMsGmgu5o*F-QxVtOG7TvrjXTa1C38fipJ39ipJdi0LgsJKD*8x8*duvnzlg9HHCISJrhMzlm2TBk8JB8amJPWuYqw9tuw&new=1>

- 学习一下他的逐步演进过程
- 有提到分库分表的技巧
- 有提到消息追踪系统，也叫调用跟踪系统


## 大型网站系统架构的演化 - 飘扬的红领巾 - 博客园
<http://www.cnblogs.com/leefreeman/p/3993449.html>


