

涉及众多知识，先在summary里分一下类吧，
# network-summary

## network-implementation-single-device-viewpoint
network-implementation

### control-plane

### data-plane

### V8
V8的FES是控制平面和数据平面的接口

### dpdk



### management-plane


### NFV


## network-implementation-inter-device-viewpoint
从一个网络视角或者说网络内设备间视角来看
注意 这里的网络是比较宽泛的，可能是一个互联网络，可以是一个AS自治域


### Operator-Network 
运营商网络架构 商用网络 | 分享自为知笔记
<http://76ad60e2.wiz03.com/share/s/1SHm3y3dXh7w25-M0z1ZXVvc2ROn6N0UdAdG2qA81-1A3dvd>

### Data-Center-Network


### Data-Center-Inter-connect


### SDN


## network-service
聚焦应用层，聚焦网络提供的服务







----------

----------

----------




# 三层转发二层交换


三层路由查表的时候千万不要忘记提：
路由迭代过程
非直连路由要一直查找，从原始下一跳转化为直连下一跳或者隧道
然后arp过程
要区分主控板的路由表和接口板硬件上的转发表FIB （Forwarding Information Base）！
迭代结果是TE隧道的话，下一跳是0，参见：
VRP总结 网络协议、特性、技术、业务知识#vpnb的迭代结果是一条LDP隧道和一条TE隧道

二层交换：
交换机会对广播帧、未知单播都进行广播泛洪
ARP请求就是广播帧
一个报文的路由器之旅-(9) 二层桥接转发流程
http://support.huawei.com/huaweiconnect/enterprise/thread-161157.html  

## 相同点
[#三层转发二层交换共同点](#diff-l3-l2-the-same)**都是要转发报文，都是要把报文找个接口发出去！！**
{#test1}
## 差异点
### 关心的报文里的字段不同

交换机取报文MAC地址查MAC表确定出接口，
而主机或者是路由器是查路由表【迭代】确定出接口！！时刻牢记！！！
比较特别的是逻辑三层口，比如VLANIF ，ETHTRUNK，还需要再选一次real device，可以看DPDK VLANif的实现


### 查的表不同
三层转发时，路由器里的路由表里的路由表项可以是来自其他network的IP地址，
体现了**inter**network

二层交换，交换机的MAC表只有本network的主机的二层MAC地址，








# layer2-protocols

# 2.5层 MPLS

# layer3-protocols
## VRRP
也叫浮动路由
IP协议号 112
Keepalived与VRRP协议 | 千里
https://liangshuang.name/2017/11/16/keepalived/


# layer7-protocols

## http

### GoogleSPDY对HTTP1.1的主要改进
参见HTTP/2 <https://zh.wikipedia.org/wiki/HTTP/2#HTTP/1.1与SPDY的区别>

- 实现无需先入先出的多路复用
- 为简化客户端和服务器开发的消息—帧机制
- 强制性压缩（包括HTTP头部）
- 优先级排序
- 双向通讯

### http/2
基于GoogleSPDY

- HTTP/2 <https://zh.wikipedia.org/wiki/HTTP/2#协议的制定>

- HTTP/2 简介
	-  <https://developers.google.com/web/fundamentals/performance/http2/?hl=zh-cn>
	- 分帧层 binary_framing_layer Introduction to HTTP/2 
		- <https://developers.google.com/web/fundamentals/performance/http2/?hl=en#binary_framing_layer>
	- 数据流-消息和帧 (#test-anchor)
		- <https://developers.google.com/web/fundamentals/performance/http2/?hl=zh-cn#_3>
		- 一条TCP连接
			- 所有通信都在一个 TCP 连接上完成，此连接可以承载任意数量的双向数据流。
		- 数据流
			- 已建立的连接内的双向字节流，可以承载一条或多条消息。
			- 每个数据流都有一个唯一的标识符和可选的优先级，用于承载双向消息。
		- 消息
			- 与逻辑请求或响应消息对应的完整的一系列帧
			- 每条消息都是一条逻辑 HTTP 消息（例如请求或响应），包含一个或多个帧
		- 帧
			- 帧：HTTP/2 通信的最小单位，每个帧都包含帧头，至少也会标识出当前帧所属的数据流 
			- 帧是最小的通信单位，承载着特定类型的数据，例如 HTTP 标头、消息负载，等等。 来自不同数据流的帧可以交错发送，然后再根据每个帧头的数据流标识符重新组装。
	- 客户端和服务器可以将 HTTP 消息分解为互不依赖的帧，然后交错发送，最后再在另一端把它们重新组装起来。<https://developers.google.com/web/fundamentals/performance/http2/?hl=zh-cn#_4>
	- 【自己的大白话】 一个TCP链接上可以发送若干个帧，这些帧可以属于不同的数据流，消息为数据流划定了边界


- RFC 7540 - Hypertext Transfer Protocol Version 2 (HTTP/2) <https://tools.ietf.org/html/rfc7540>

- HTTP: Brief History of HTTP - High Performance Browser Networking (O'Reilly) <https://hpbn.co/brief-history-of-http/>

#### http2争议
HTTP/2 <https://zh.wikipedia.org/wiki/HTTP/2#针对协议开发本身>
- 违背了互联网协议的分层原则[28]，例如说，将本属于TCP传输层的流控制(flow control)功能放入了协议中。

### http-pipeline

- HTTP管线化 <https://zh.wikipedia.org/wiki/HTTP管線化>
- 可能将多个 HTTP 请求填充在一个TCP数据包内，HTTP 管线化需要在网络上传输较少的 TCP 数据包，减少了网络负载
- 依赖条件
	- 通过永久连接（persistent connection）完成
	- 非幂等的方法，例如POST将不会被管线化
	- 连续的 GET 和 HEAD 请求总可以管线化的。
	- 一个连续的幂等请求，如 GET，HEAD，PUT，DELETE，是否可以被管线化取决于一连串请求是否依赖于其他的。


