

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

### P4

P4:真正的SDN还遥远吗？
http://www.sdnlab.com/16248.html  
P4(Programming protocol-independent packet processors)[1]是由Pat Bosshart等人提出来的高级“协议独立数据包处理编程语言”，如OpenFlow一样是一种南向协议，但是其范围要比OpenFlow要大。不仅可以指导数据流进行转发，还可以对交换机等转发设备的数据处理流程进行软件编程定义，是真正意义上的完全SDN。
。。。
与POF提出的目的类似，P4提出的目的也是为了解决OpenFlow编程能力不足以及其设计本身所带来的可拓展性差的难题
。。。
P4的设计和华为提出的POF十分相似，只不过侧重点和实现方式不同。POF通过{offset,length}来确定数据，强调协议无关，强调指令集，而P4不仅有底层的高度抽象的协议无关指令集，更侧重与控制器端的网络编程语言的构建。还有一点不同的是，同作为开创式的技术，由美国Nick教授等业界先驱推动的P4明显要比由华为提出的POF受到的关注要多，业界对P4的认同也要比POF要高。


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

## IP-protocol
## VRRP
也叫浮动路由
IP协议号 112
Keepalived与VRRP协议 | 千里
https://liangshuang.name/2017/11/16/keepalived/










# layer4-protocols

## TCP

## UDP






# layer7-protocols

## http

- HTTP: Brief History of HTTP - High Performance Browser Networking (O'Reilly) <https://hpbn.co/brief-history-of-http/>


### GoogleSPDY对HTTP1.1的主要改进
参见HTTP/2 <https://zh.wikipedia.org/wiki/HTTP/2#HTTP/1.1与SPDY的区别>

- 实现无需先入先出的多路复用
- 为简化客户端和服务器开发的消息—帧机制
- 强制性压缩（包括HTTP头部）
- 优先级排序
- 双向通讯

### http/2
基于GoogleSPDY

<a href="#foo">Foo</a>
asdf(#test-anchor) 
asdfsadf{#test-anchor}

[binary_framing_layer](#binary_framing_layer)

- HTTP/2 <https://zh.wikipedia.org/wiki/HTTP/2#协议的制定>

- RFC 7540 - Hypertext Transfer Protocol Version 2 (HTTP/2) <https://tools.ietf.org/html/rfc7540>


#### HTTP2-overview
-  <https://developers.google.com/web/fundamentals/performance/http2/?hl=zh-cn>
- 数据流-消息和帧
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
- 【自己的大白话】 
	- http的请求响应消息会被分割打包为若干个二进制帧
	- 一个TCP链接被划分为若干个逻辑数据流
	- 帧会指定逻辑数据流ID，最终还是由TCP链接承载


#### http2-binary_framing_layer
- 分帧层 binary_framing_layer <span id = "binary_framing_layer" />Introduction to HTTP/2 
	- <https://developers.google.com/web/fundamentals/performance/http2/?hl=en#binary_framing_layer>

#### http2-数据流优先级

- 参考 <https://developers.google.com/web/fundamentals/performance/http2/?hl=zh-cn#_5>

#### http2-流控制
<https://developers.google.com/web/fundamentals/performance/http2/?hl=zh-cn#_7>

#### http2服务器推送
<https://developers.google.com/web/fundamentals/performance/http2/?hl=zh-cn#_8>


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




## https

- HTTPS及HTTPS中间人攻击 - 51CTO.COM
<http://netsecurity.51cto.com/art/201702/531356.htm>
	- 2017年6月14日 读后总结，关键字： 
非对称加密，客户端发起请求，服务器端返回公钥给客户端
客户端生成对称加密用的随机值，并用公钥加密后返回给服务器
服务器拿私钥解密得到对称加密用的随机值，
以后的请求响应都用此随机值进行对称加密解密


