

# network-implementation

## single-device-viewpoint
network-implementation

### control-plane

#### protocols

##### TCP

- Google TCP fast open
https://static.googleusercontent.com/media/research.google.com/zh-CN//pubs/archive/37517.pdf

### data-plane

#### V8
V8的FES是控制平面和数据平面的接口

#### dpdk

### management-plane



### NFV



## network-inter-device-viewpoint
从一个网络视角或者说网络内设备间视角来看
注意 这里的网络是比较宽泛的，可能是一个互联网络，可以是一个AS自治域


### Operator-Network 

### Data-Center-Network


### Data-Center-Inter-connect


### SDN




# network-service
聚焦应用层，聚焦网络提供的服务



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


# 二层

# 2.5层 MPLS

# 三层
## VRRP
也叫浮动路由
IP协议号 112
Keepalived与VRRP协议 | 千里
https://liangshuang.name/2017/11/16/keepalived/


# 应用层-七层协议

