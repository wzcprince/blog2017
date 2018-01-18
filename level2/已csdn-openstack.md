
总目录


# OpenStack设计与实现-读书笔记

## 学习方法-先记拓扑-脉络-skeleton-纲要-整体拓扑

前言
前言里的学习方法：
努力在脑海中形成他的拓扑，并不断地细化
就好似我们头脑里形成的有关城市的地图，它有哪个区，区里又有哪些标志建筑以及街道

前四章，形成对OpenStack整体的拓扑，


## 1.3-OpenStack体系结构
云计算中所谓的云可以简单地理解为任何可以通过互联网访问的服务

云计算三种落地方式：
IaaS
裸机（bare metal） 或者虚拟机

PaaS
用户可以申请到比如一个安装了操作系统以及一些运行库等软件的物理机或者虚拟机，然后在上面安装其他应用程序

SaaS


P11 OpenStack的核心功能：
管理海量的物理机，给用户提供虚拟机、虚拟网络服务

P14 
OpenStack是处于用户和海量物理机之间的中间层！！！
与物理节点上的hypervisor交互，实现对硬件资源的管理和控制；
为用户提供满足要求的虚拟机


P15 Nova  ['novə] 新星
组件
nova-api
nova-schedule 接受创建虚拟机的请求，并决定在哪台物理主机上启动该虚拟机


nova-compute 安装到每个物理主机上的服务进程，它接受并处理与虚拟机相关的操作请求，
需要调用底层的hypervisor API，
比如支持XenServer/XCP的XenAPI；
支持KVM和QEMU【key moo】的libvirt
支持VMware的VMware API
#openstack nova-compute和QEMU、KVM的关系
openstack nova-compute和QEMU、KVM的关系

nova-conductor 位于nova-Compute和nova-db中间，转达的作用

nova-db 一大堆数据库表，记录虚机状态，虚机与物理机的对应关系，租户信息等等

P17 neutron  ['nju:trɑn] 中子

P28 OPNFV 即Open Platform Network Function Virtualization

P45 阅读源代码的一个技巧

P54 小黄鸭调试法

P76 分层
分层的好处之一就是给下层为上层创造“虚拟世界”提供了便利条件
【想到软件架构那本书里提到的分层模式，有此便利的前提是禁止跨层调用】
把物理机虚拟化为多台虚机，通过网络将这些虚机互联互通，从而形成云计算系统

Virtual Machine Monitor 即 VMM 也叫 Hypervisor  [,haipə'vaizə]


第七章  网络

P290 Neutron 最核心的工作就是对二层网络的抽象与管理

P291 vNIC vSwitch
linux的TAP TUN 
vEth总是成对出现
linux Bridge可以 enslave 从设备 变为 Bridge的一个端口，
当这些从设备接收到数据包时，会提交给Bridge，然后根据MAC地址与端口的映射关系转发

7.1.3 Neutron ['nju:trɑn] 架构 P295
neutron只有一个主要的服务进程neutron-server，运行在网络控制节点上，
提供restfull API作为访问neutron的入口，
neutron-server接收到的用户HTTP请求最终由遍布于计算节点和网络节点上的各种agent来完成。

核心资源：二层network subnet port 
其中，subnet是指虚机可用的IP地址范围，包括IPv4 IPv6
扩展资源：router、firewall、dhcp等等

neutron以plugin的方式组织代码，每个plugin支持一组API操作，
这些操作最终由plugin通过RPC调用相应的agent来完成。
agent一般专属于某个功能，

