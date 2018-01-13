

# dueros-overview

- dueros技能开放平台
- dueros-智能设备开放平台


# dueros-智能设备开放平台

## DCS协议

### dueros-DCS-消息格式

DuerOS消息格式
<https://dueros.baidu.com/didp/doc/dueros-conversational-service/message-format_markdown>

- 基于HTTP2请求响应
- 支持multipart，即一个HTTP请求响应消息中带多个Message Body
- Message Body中是JSON格式，所有的directive / event / clientContext都遵循
	- header中的namespace和name确定了这是什么指令（在本例子中这是Speak指令）
	- 确定了指令，就知道怎么解读payload里的数据了。
	- 例如

> 		"directive": {
> 		    "header": {
> 		        "namespace": "ai.dueros.device_interface.voice_input",
> 		        "name": "Speak",
> 		        "messageId": "messageId-1234"
> 		    },
> 		    "payload": {
> 		        "url": "cid:1234",
> 		        "format": "AUDIO_MPEG",
> 		        "token": "token-1234"
> 		    }
> 		}


- 设备端请求JSON分两部分：
	- client context 端状态
	- event 事件
- 服务端响应JSON
	- directive

### dueros-端能力

#### 语音输入

#### 语音输出

#### 

# brpc
## brpc-GitHub-doc

### overview.md 
<https://github.com/brpc/brpc/blob/master/docs/cn/overview.md>

### brpc-IO-full-picture
<https://github.com/brpc/brpc/blob/master/docs/cn/io.md#the-full-picture>
![](https://github.com/brpc/brpc/raw/master/docs/images/rpc_flow.png)

[brpc-client端基本流程](https://github.com/brpc/brpc/blob/master/docs/cn/client.md#附client端基本流程)


### bvar
brpc/bvar.md at master · brpc/brpc
<https://github.com/brpc/brpc/blob/master/docs/cn/bvar.md>

- 利用了thread local存储
- 权衡折中的又一活生生的例子
- 读的速度慢一点，让写快一点
	- 当很多线程都在累加一个计数器时，每个线程只累加私有的变量而不参与全局竞争，在读取时累加所有线程的私有变量。虽然读比之前慢多了，但由于这类计数器的读多为低频的记录和展现，慢点无所谓。而写就快多了，极小的开销使得用户可以无顾虑地使用bvar监控系统，这便是我们设计bvar的目的。


## 帖子1
### 百度正式开源其RPC框架brpc-2017年9月20日
<http://www.infoq.com/cn/news/2017/09/brpc>

- 基于protobuf接口的RPC框架
- 囊括了百度内部所有RPC协议，并支持多种第三方协议
	- 对协议的抽象更一般化，并统一了全百度的通信架构。bprc能容纳非常多的协议，基于Protobuf的，基于HTTP的，百度内的nshead/mcpack，开源的Redis/Memcached，甚至RTMP/FLV/HLS直播协议，brpc能逐渐地嵌入现有系统，而不需要彻底重构
- 负载均衡
	- brpc默认提供round-robin、随机、一致性哈希，Locality-aware（局部性感知）四种算法
- 经受了高并发高负载的生产环境验证，并支撑了百度内部大约75万个同时在线的实例，超过500种服务（去年的统计，现在已不统计这类数据）。Hadoop、Table、Mola（另一种广泛使用的存储）、高性能计算、模型训练、大量的在线检索服务都使用了brpc。

- 为什么百度当时要研发brpc
	- 关键点是能不能真正地提高用户的效率：开发、调试、维护都要考虑到
	- 创建brpc的初衷是解决百度业务所面临的实际挑战，同时也希望成为百度同学最喜爱的工具
	- 希望在提供了一个好用框架的同时，也展现了一种工作方法：注释怎么写，日志怎么打，ChangeLog怎么写，版本怎么发布，文档怎么组织，甚至对未来不在百度的同学的工作也有帮助



- brpc的优势
	- brpc主打的是深度和易用性
	- **gRPC**（包括更早的Thrift）的深度和易用性并不够
	- 看示例程序，文档非常牛逼，但实战中可能就是另一回事了，为什么各个公司都要造自己的轮子，一个隐藏原因就是表面高大上的东西在一些细节上让你无法忍受。
- RPC真正的痛点是什么？是可靠性、易用性和定位问题的便利性。
	- 可靠性
		- 为brpc团队设立很高的招聘门槛，以及在团队中深入的技术讨论
		- 长尾问题，bprc中的bthread模块是一个M:N线程库，就是为了更好地提高并发避免阻塞
		- brpc中的读和写都是wait-free的，这是最高程度的并发
	- 易用性
		- 有种设计是什么选择都做成选项丢给用户，号称功能都有
			- 一旦出问题，则是用户“配置错了”。而且这样用户还非常依赖开发团队
		- brpc对于增加选项非常谨慎，框架能自己做判断的绝不扔给用户，所有用户选项都有最合理的默认值，不设也能用。
	- 可定位性，定位问题的便利性
		- 痛点矛盾突出
			- 要拉RPC同学一起排查
			- RPC框架对用户是个黑盒，用户根本不知道里面发生了什么
			- 人手必然不够。时间长了用户就觉得你这个框架各种问题，人还拽的不行很少回他们消息
		- 解决痛点矛盾，大部分问题用户可以自助解决
			- 给server内加入各种HTTP接口的内置服务，通过这些服务，用户可以很快看到server的延时、错误、连接、跟踪某个RPC、CPU热点、内存分配、锁竞争等信息
			- 还可以使用bvar来自定义各类统计信息，并在百度的运维平台NOAH上汇总

	- 多线程质量更好
	- 完备的调试和运维支持。解决这个问题的本质还在可扩展性
		- 让用户参与进来定制他们感兴趣的指标，为此我们设计了bvar，让用户能用比原子变量代价还小的方式自由地定制各种指标，用户能在浏览器上看到指标的变化曲线，或在运维平台NOAH看到汇总的监控数据
		- 大量内置服务方便用户调试程序，查看连接，在线修改gflags，追踪RPC，分析CPU热点，内存分配，锁竞争等一应俱全
	- 高性能
		- 性能是我们非常看中的一点，它和用户体验也是紧密联系的。好用但性能不行，或不好用但性能很牛，用户会很难受，我们不希望用户纠结。
		- 在推广初期，我们要说服产品线用brpc靠什么？最直观的就是性能提升。而且这儿的性能不能停留在benchmark的图片上，而是能在真实应用中体现出来。

- brpc整体架构
	- 技术栈无外乎是从传输层垒到应用层，就略过不讲了
	- brpc在架构上强调“在不牺牲易用性的前提下增强可扩展性”
		- 比如brpc支持非常多的协议，在百度内部一个brpc server同端口可以支持二十几种协议，这对于服务的平滑迁移就非常好用。
		- Client端的协议也非常多，用户用brpc和bthread用得很爽，所以希望我们最好能统一所有的客户端
			- 像对Redis和Memcached的客户端支持也是在这个背景下做的，这两个客户端比官方Client好用多了，感兴趣的读者可以去尝试一下。但这么多协议的配置非常简单，填个字符串就行了，比如HTTP就是把ChannelOptions.protocol设为“http”，Redis就是“redis”。Server端甚至不用设，它会自动判断每个client的协议，brpc/new_protocol.md at master · brpc/brpc <https://github.com/brpc/brpc/blob/master/docs/cn/new_protocol.md#server端多协议>

- 为什么要将brpc开源？
	- 为其它开源项目铺路
		- 会开源基于brpc的RAFT库，搭建高可用分布式系统非常方便


## 帖子2-体系化认识RPC
<http://www.infoq.com/cn/articles/get-to-know-rpc?utm_source=infoq&utm_medium=related_content_link&utm_campaign=relatedContent_news_clk>

文章写得不咋地，但这句话说得非常对：

- RPC（Remote Procedure Call），即远程过程调用，是一个**分布式系统**间通信的必备技术，本文体系性地介绍了 RPC 包含的核心概念和技术，希望读者读完文章，**一提到 RPC，脑中不是零碎的知识，而是具体的一个脑图般的体系**。本文并不会深入到每一个主题剖析，只做提纲挈领的介绍。

- RPC 最核心要解决的问题就是在分布式系统间，如何执行另外一个地址空间上的函数、方法，就仿佛在本地调用一样