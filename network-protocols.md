
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

## 差异点
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

