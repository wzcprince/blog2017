[toc]

# 【建立联系，融入自己的知识体系中】


# 虚拟化

## libvirt

### 价值目标

blog2017/performance-optimization-summary.md at master · wzcprince/blog2017 · GitHub
<https://github.com/wzcprince/blog2017/blob/master/performance-optimization-summary.md#增加cache>

参见 <http://wiki.libvirt.org/page/FAQ#What_is_libvirt.3F>

- provides a convenient way to manage virtual machines and other virtualization functionality, such as storage and network interface management.
- to provide a single way to manage multiple different virtualization providers/hypervisors. 
	- For example, the command 'virsh list --all' can be used to list the existing virtual machines **for any supported hypervisor (KVM, Xen, VMWare ESX, etc.)** No need to learn the hypervisor specific tools! 
	- When people say they 'use libvirt', this usually means that they manage virtual machines using tools such as 'virsh', 'virt-manager', or 'virt-install', which are all built around libvirt functionality. They likely DO NOT directly use tools like 'xm' for Xen, or the qemu/qemu-kvm binary.

### 主要功能
参见 <http://wiki.libvirt.org/page/FAQ#What_is_some_of_the_major_functionality_provided_by_libvirt.3F>

1. VM management
2. Remote machine support
3. Storage management
4. Network interface management
5. Virtual NAT and Route based networking

### 应用
#### OpenStack用了libvirt


参见
- OpenStack Docs: Feature Support Matrix
https://docs.openstack.org/nova/latest/user/support-matrix.html
- https://www.libvirt.org/apps.html#iaas
- KVM 介绍（6）：Nova 通过 libvirt 管理 QEMU/KVM 虚机 [Nova Libvirt QEMU/KVM Domain] - SammyLiu - 博客园
http://www.cnblogs.com/sammyliu/p/4568188.html

- KubeVirt与libvirt不同
kubevirt/kubevirt: A virtualization API and runtime add-on for Kubernetes in order to define and manage virtual machines.
https://github.com/kubevirt/kubevirt
At its core, KubeVirt extends Kubernetes by adding additional virtualization resource types (especially the VM type) through Kubernetes's Custom Resource Definitions API. By using this mechanism, the Kubernetes API can be used to manage these VM resources alongside all other resources Kubernetes provides.



## virtIO
归类于 **半虚拟化** ★★★

Written by Rusty Russell
**Virtio is a virtualization standard for network and disk device drivers** where just the guest's device driver "knows" it is running in a virtual environment, and cooperates with the hypervisor. This enables guests to get high performance network and disk operations, and gives most of the performance benefits of paravirtualization.

Virtio - Libvirt Wiki
https://wiki.libvirt.org/page/Virtio#Virtio

(KVM连载)5.1.1 Virtio概述和基本原理（KVM半虚拟化驱动） – 笑遍世界
http://smilejay.com/2012/11/virtio-overview/


Virtio - KVM
http://www.linux-kvm.org/page/Virtio

http://www.linux-kvm.org/images/d/dd/KvmForum2007%24kvm_pv_drv.pdf

### virtIO结合DPDK和容器

7. Virtio_user for Container Networking — Data Plane Development Kit 18.02.0-rc0 documentation
http://www.dpdk.org/doc/guides/howto/virtio_user_for_container_networking.html#figure-virtio-user-for-container-networking
注意此图
![](http://www.dpdk.org/doc/guides/_images/use_models_for_running_dpdk_in_containers.svg)
#### slicing model
slicing model切片模型其实就是Intel VT-d技术，VMDq技术
在一个物理网卡上虚拟出多个Virtual Function来。
#### aggregation model
This page will only cover aggregation model.

## 半虚拟化
IO半虚拟化：虚拟设备队列VMDq技术解析-IT168 虚拟化专区
http://virtual.it168.com/a2010/0126/843/000000843481_all.shtml

virtIO vring工作机制分析 | OenHan
http://oenhan.com/virtio-vring

**半虚拟化和docker结合 好玩 ！！ **
7. Virtio_user for Container Networking — Data Plane Development Kit 18.02.0-rc0 documentation
http://dpdk.org/doc/guides/howto/virtio_user_for_container_networking.html

## QEMU 发音Key-Moo

https://en.wikipedia.org/wiki/Talk:QEMU#How_do_you_pronounce_it.3F  
In the OpenStack cloud Nova team meetings I hear it pronounced 3 weeks: Key-Moo, Q.E.M.U., and Kwee-Moo. 2017-09-14 — Preceding unsigned comment added by Medberry (talk • contribs) 19:37, 14 September 2017 (UTC)

## Intel VT-d

https://software.intel.com/en-us/blogs/2009/06/25/understanding-vt-d-intel-virtualization-technology-for-directed-io
"VT-d" stands for "Intel Virtualization Technology for Directed I/O".  

VT-d, at the time of this writing, includes four key capabilities

1. I/O device assignment. This feature allows an administrator to assign I/O devices to VMs in any desired configuration.

2. DMA remapping. Supports address translations for device DMA data transfers.

3. Interrupt remapping. Provides VM routing and isolation of device interrupts.

4. Reliability features. Reports and records system software DMA and interrupt erros that may otherwise corrupt memory of impact VM isolation.

参考：
https://www-ssl.intel.com/content/www/us/en/virtualization/virtualization-technology/intel-virtualization-technology.html?iid=tech_vt+tech  
https://www.intel.com/content/dam/www/public/us/en/documents/product-specifications/vt-directed-io-spec.pdf  






# Hypervisor
## Openstack

Kubernetes和OpenStack到底是什么关系？ - 知乎
https://www.zhihu.com/question/26895729
简单的说，kubernetes是管理container的工具，openstack是管理VM的工具。container可以运行在物理机上，也可以运行在VM上。所以kubernetes不是需要openstack的支持。但对于云计算来说，很多IasS都通过openstack来管理虚拟机。然后用户可以在这些虚拟机上运行docker，可以通过kubernetes进行管理。



### OpenStack虚机网卡的创建过程
<http://www.sdnlab.com/20286.html>





# 网络

## 虚拟网络
### VxLan

VXLAN技术研究 - CSDN博客
http://blog.csdn.net/sinat_31828101/article/details/50504656
【很好很详细】
OpenFlow与VxLAN在云网络的应用_AlibabaInfrastructure_新浪博客
http://blog.sina.com.cn/s/blog_e59371cc0102vl9r.html  

overlay最重要的一点就是虚拟网络和底层物理网络的解耦！！！！！
加层的重要性


## 大二层

vxlan 的 BUM问题，怎么解决？？？

[#纯l3的overlay转发规避大二层的bum问题](#纯l3的overlay转发规避大二层的bum问题)

还可以参见
http://blog.csdn.net/sinat_31828101/article/details/50504656  
问题2：大二层网络下，需要维护一个非常庞大的mac和arp表项，尤其是TOR交换机的mac地址表大小可能会影响整个fabric的规模。
如何解决：由于overlay组网中，网络设备互联多采用三层互联的方式，这样arp表就无需泛洪到全网，所以每个tor交换机仅仅需要维护一张本地的mac地址表即可。


## 带宽

### 出口带宽
如今40G端口已经成为数据中心的标配，**作为数据中心的出口**，40G 的光模块出货量基本和10G持平，很快可以超越10G。

### 服务器网卡带宽






## 数据中心互联技术DCI Data Center Inter-connect

参见 中国电信产品导购
http://sh.189.cn/biz/application/sjzx/17332.html

关于DCI中传输网络的一些探讨-SDN-华为开发者论坛
http://developer.huawei.com/ict/forum/thread-14113-1-1.html

### 最原始的时代 internet直接互联
- 速度慢啊
- 流量乱窜，安全性没有保证啊！！
- 所以要专线、VPN、光纤上啦

### MPLS VPN

中国电信MPLS-VPN（英文名称Virtual Private Network，虚拟专网）业务**依托于中国电信宽带骨干网169和CN2**，采用MPLS（多协议标记交换）协议，结合服务等级、流量控制等技术，为用户在公共MPLS网络上构建企业的虚拟专网，满足其不同城市（国际、国内）分支机构间安全、快速、可靠的通信需求，并能够支持数据、语音、图像等高质量、高可靠性要求的多媒体业务。目前，通过中国电信宽带骨干网向客户提供的MPLS－VPN业务，支持**以太网、帧中继、DDN、ATM、宽带等多种接入方式**，能够为集团客户提供速率为**N*64K-2.5G**、端到端的MPLS VPN业务，并且用户可以随时根据需要扩展网络（增加端口、提高速率等）  

云计算网络的应用场景-云计算-华为企业互动社区
http://support.huawei.com/huaweiconnect/enterprise/thread-367469-1-1.html  
【vpls用于DCI网络，即DC互联网络】



#### MSTP（以太网专线）

- 支持n×64K～2.5G TDM专线
- 多业务传送平台（Multi-Service Transport Platform）
- 以SDH平台为基础，同时实现TDM、ATM、 以太网等业务的接入、处理和传送的技术
- 支持Ethernet专线
- 支持ATM专线


#### 数字电路SDH
速率高，可达10Gbit/s



## DCI网络重构-新建DCI骨干网

### 必要性
参见  云将至，网先行——DCI网络重构是大势所趋 - 华为 — C114(中国通信网)
http://www.c114.com.cn/news/126/a950011.html

云DC的位置与传统IP骨干网核心节点位置往往是不重合
由于网络流量中心位置变化，很难重用现有骨干网，因此需要新建DCI（DC互联）网络。

### 产品推荐
华为NE5000E集群路由器提供了业界最高100G端口密度，单机可提供256个100GE端口，同时支持由400G向1T、2T平台演进，并支持多框集群在线平滑扩展，满足5年以上业务发展诉求。

### SDN技术应用到DCI
DC间流量具有突发性和不均衡性，需要采用SDN技术进行实时流量调优。DC间虚拟机随机迁移引起流量的不确定性。此外，例如“阿里巴巴11.11” 等互联网热点业务也具有突发性，这些都会造成流量不均衡，局部链路拥塞，而整网链路平均利用率不高。传统流量工程基于对网络流量情况预判，无法解决突发拥塞问题。

SDN流量调优技术对整网流量监控并实时调整，实现链路间的负载均衡。除带宽利用率外，还能够基于时延等因素进行流量调整，保障用户体验。此外，SDN还可以实现IP和光层协同，包括跨层资源统一管理与链路规划、自动业务部署等，业务发放时间大大缩短，并且整网资源利用率得到大幅提升。华为**SDN RR+/PCE+流量调优技术**以及SDN IP+光技术都已率先实现商用。

### 在DCI领域，华为与运营商联合创新，推动网络转型

华为在2016年CeBIT期间，率先发布了**SDN BaaS（Bandwidth as a Service）**解决方案，用户可通过web 页面自主定制带宽需求，SDN将需求自动转化为从企业接入到数据中心各层**网络QoS保障策略及VPN策略**，实现专线端到端自动开通，业务部署时间由数周缩短至几分钟，极大提升用户体验的同时为运营商提供了新的收入来源。

更重要的是，在DC深刻影响着未来骨干网络发展方向的今天，华为已携手**中国电信等运营商共同建设DCI专有网络**，实现面向云时代DCI网络重构的探索实践和商用部署。

构建面向未来的智慧DCI网络，实现云网协同，已成为云时代的必然趋势。










# 文章、帖子收集

##腾讯DCI上线基于集中控制的SR-TE方案
<https://mp.weixin.qq.com/s/Z9rz17q4B6jDZEFKlbGFBg>

## 数据中心SDN技术发展应用之MP-BGP
<https://mp.weixin.qq.com/s/cKoTi9hJD_QHWhS6d2koVA>
EVPN Vxlan SDN技术用来构建DataCenter网络 


##  从25G到100G-阿里数据中心网络架构设计分享
阿里巴巴技术保障部高级网络专家曹捷
原文地址：
https://www.sohu.com/a/207565881_582307
http://www.idckx.com/shujuzhongxin/13416.html

#### 阿里网络架构演进过程
先说一下演进结果：
其中我们尝试过各种各样的数据中心解决方案，一个坑一个坑踩过来之后，现在决定<font color = "0xDD000000" size = "3" >**把网络做到最简单，简单到什么呢?简单到一个网络里面只有一个路由协议，而且这个BGP路由协议没有任何扩展的协议族。我的网络在接入交换机就在最后的端口上，提供给服务器接入  **</font>【BUM问题，BUM(Broadcast&Unknown-unicast&Multicast)报文】。

- 2016年 阿里云对网络是重度依赖，重度耦合
解决方法：当时我们的策略是解耦、简单化，我们干脆提出来所有的东西都阿里云自己做，所以阿里云**在组织架构上做了调整**，有了专门的虚拟网络团队和物理网络团队，我们在虚拟网络之下成立了物理网络团队，**我是物理网络团队的**。上面也有专职构建虚拟网络。

#### 展望未来

##### 可视化
###### 目的是要解决三个问题：
- 看不见，比如延时、转发路径、buffer和drop
- 找不到，通过随包的检测和拓扑的维护，快速定位问题所在的位置
- 第三个是抹不准，今天我们做网络的设计和交换机选型的时候，你抹得准是多少的交换机吗?是48+8、48+6还是48+10，这些都抹不准，很多情况下是猜的，或者供应商告诉你这已经是世界上最好的交换机就买了

###### 实现方式
- 物理网络上erspan做数据平面的关键信息的捕获
- 控制平面上会用gRPC

	物理网络上我们会用erspan做数据平面的关键信息的捕获，然后在控制平面上会用gRPC，交换机当中今天很多存在但是看不到的信息拉出来，比如说buffer的使用情况，比如出现芯片级的异常或者出现SDK的异常，这些在交换本身是有认证或者是有维护的，但是通过传统监控手段看不到，今天我们通过一个更高效的手段，我为什么不选择让供应商做一个新的SSP的ODI呢?是因为传统网络的监控协议太重，gRPC是轻量的模式，可以定义非常好的数据结构，但是gRPC是非常轻的，量非常好。
	有了gRPC也有一个问题就是，这时候需要用INT，INT是芯片级别的能力支持，它和软件没有什么太大关系，在将来我们会看到下一代所有交换芯片商几乎都会支持INT，FaceBook也好、微软也好都在跟进，阿利耶在努力。其实世界上主要由两个交换芯片供应商，两大交换芯片供应商我们都和他们合作，定义阿里所需要的INT能力。

	这是我们对于整个可视化意义的判断。**未来的数据中心必然是一个整体，DC as a computer，我们认为网络是computer的I/O**，要达到这样的目的，现有的网络设计是封闭的，所以没有办法对外开放，它是阻碍前进的东西。可能的方法，说我可不可以自己做交换机，自己做交换机的OS，完全自研白盒交换机。**可视化是利用现有网络技术最快速的能够将网络信息开放出来的方法**，有了这种方法之后其实不一定非要去自研一台交换机或者自OS就完全可以去调配和管控物理网络资源。所以我们得出的结论，可视化将会在未来3-5年之内是阿里巴巴重点全力投入的数据中心网络技术，他会帮助我们在没有办法实现完全自研支持最大可能的掌握数据交配。
	
###### erspan Encapsulated Remote Switched Port ANalyzer 
封装远端交换端口分析，用到了GRE隧道
	Information About ERSPAN
	encapsulated remote switched port analyzer 
https://www.cisco.com/c/en/us/td/docs/switches/datacenter/sw/5_x/nx-os/system_management/configuration/guide/sm_nx_os_cg/sm_erspan.html#15525
ERSPAN transports mirrored traffic over an IP network.

###### gRPC https://grpc.io/
- high performance
- using Protocol Buffers, a powerful binary serialization toolset and language
- http/2 based transport
- Simple service definition
- Works across languages and platforms

## 数据中心间网络SDN解决思路探讨 - 鹅厂网事
数据中心间网络SDN解决思路探讨 ( 上集 )-腾讯大讲堂
http://djt.qq.com/article/view/1236
数据中心间网络SDN解决思路探讨 ( 下集 ) -腾讯大讲堂
http://djt.qq.com/article/view/1243

### 提出问题
#### 数据中心间网络链路带宽资源有限，扩容慢
业务部门通常抱怨基础架构侧行动缓慢、缺乏灵活性、响应速度慢；
#### 1：1的可靠性备份导致链路利用率低于50%

#### 设备数量大，网络管理困难

（例如CN2，800多台设备；Google backbone， 600多台设备）

### 鹅厂对SDN的理解：Network as a Router
#### Google TE结合SDN提高链路利用率到90%
据统计，在2011年Google为数据中心之间建设DWDM高达15T。正因为贯彻了采用TE技术结合SDN的理念，面对数量庞大的设备和链路，Google才能做到从容不迫，链路利用率达到90%。

### 鹅厂主要思路
#### 基础设施，物理设备保障
#### 使用TE技术预留带宽，类比Bus Rapid Transit，快速公交系统
##### 不同优先级别的TE，可以为不同的业务类型保障承诺不同等级的服务

![](http://p14ws25od.bkt.clouddn.com/201712271645_418.png)

#### SDN集中的控制面可以从网络全局做更智能的流量调度

## 鹅厂如何构建大型基础网络平台 - 鹅厂网事 | 十条
http://www.10tiao.com/html/721/201702/2649021339/1.html

### 基础网络平台的整体架构图
![鹅厂基础网络平台的整体架构图](http://p14ws25od.bkt.clouddn.com/201712191921_814.png)

### 网络架构目标是不断构建和优化的两个能力：连接服务与服务的能力 与 连接服务与用户的能力

### 整体基础网络平台分为三大块
#### Data Center网络 【采用 多级CLOS方案  ECMP技术】
聚焦于“连接服务与服务的能力”

#### Edge
边缘网络，用于对接用户（ISP）的边界网络。
边缘网络（Edge）聚焦于“连接服务与用户的能力”，其主要任务就是能将鹅厂的服务以最短的路径、最好的质量送到全球各地用户的手上。国内的边缘网络普遍以静态对接ISP的形式存在，海外则以BGP对接为主，本章节主要对鹅厂海外的边缘网络架构进行介绍。


#### DCI
数据中心互联广域网络，负责将散落在全球的这些Data Center与Edge连接起来。
DCI广域网络同时负责构建“连接服务与服务的能力”及“连接服务与用户的能力”，即是将鹅厂全球所有Data Center连接起来的网络，是整个基础网络平台的重中之重

![](http://p14ws25od.bkt.clouddn.com/201712191928_913.png)


##### DCI for Elastic Services 【使用TE技术来提高利用率和流量调度能力】
大流量广域网，承载了鹅厂90%以上的广域流量，为大多数鹅厂成熟平台级业务服务，是一张新技术快速迭代与扩容频率较高的网络，部分链路利用率有时会到达80%以上。
构建思路：
- 将“路由控制系统”和“路径控制系统”解耦，路由跟业务有关，只能决定目的地在哪里，路径跟流量走向有关，可以决定源和目的之间可以走哪条链路。路由系统算出目的地之后，就交给路径系统去找到最佳路径，并准确送到目的地。
- 路由控制系统由于只需要知道目的地，不关心怎么去往目的地，整体逻辑非常简单，所以我们使用传统的BGP来传递路由，这一块不是SDN的，稳定且高效。
- 路径控制系统也需要“上帝视角”，需要对全局的拓扑、链路负载、时延、甚至链路成本进行统一考虑，并经过合理的计算得出最终的结果，所以这一块就要借助SDN的思路来解决问题了。鹅厂的做法是路径集中控制，**控制器将全网需要的信息全部上收，并进行集中计算**，最终得出一定数量的点到点Tunnel供路由控制系统使用，并且**控制器要实时感知网络故障和流量变化的情况来进行全网最佳路径优化**，保证所有的访问流量都可以实时获得最好的网络质量。
- 传统的RSVP-TE也是类似的解决方案，不过稍显重载和复杂，包括跨硬件平台互通性问题、网元设备复杂度高成本高、Tunnel数量太多导致RSVP消息量的压力与风险，这些都给大规模的TE部署带来了一些挑战，但最大的问题是，所有路径都是头端节点计算，不同需求互相抢占资源，达不到全网整体最优，即没有“上帝视角”。
- 除此之外，在这张广域网上还部署了**差异化服务，即流量分级【Qos】**，不同等级的流量享受不同级别的服务，在严重故障发生时，高级别流量优先保障最好的网络质量，低级别流量可能会被抢占带宽而进行绕行甚至丢包。这也是广域网的核心技术之一，保障重点流量的同时，可以将整体资源利用率提升至很高的水平，形成可靠性和利用率之间的较好平衡。

##### DCI for Interactive Services
精品广域网，服务互联网金融等对网络质量依赖很强的业务，使用通用、成熟、稳定的技术构建，链路利用率控制在40%以下，无新技术迭代，扩容变更频率也非常低。


## 拥抱SDN\/NFV - 构建腾讯黑石物理云 2017-04-28 潘志新
http://www.10tiao.com/html/721/201704/2649021346/1.html

数据中心内部，我们的网络采用了SDN Overlay解决方案来支撑黑石业务系统。leaf-spine-border三层架构，underlay层面由动态路由协议构建，**overlay的数据平面我们采用了RFC标准的vxlan封装格式。控制平面采用了bgp evpn协议**，同时对其进行性能和资源开销上进行协议层面的优化，如提升tcam表项利用率，优化leaf节点的广播报文处理机制等，最大程度提高网络可用性。Bgp evpn的控制平面为业务vpc架构提供了很好的基础环境，黑石内部用户逻辑隔离的VPC网络，可自定义网段和路由策略，均得益于此。很好地满足业务的弹性灵活部署需求


## 腾讯黑石私有云/5.0V—基于SDN的腾讯次世代数据中心网络架构 - 2017-02-17 陈磊
http://www.10tiao.com/html/721/201702/2649021335/1.html

### 硬件ovlerlay转发：overlay转发节点为交换机
怎么搞？？嘛意思？？应该是在服务器上的网卡用半虚拟化 VMDQ 技术来实现呀！！这里竟然说是交换机
### NFV
计算要求高，**交换机无法满足的L4-7层服务节点和网络增值业务节点（例如防火墙，LB，VPN接入等）【也就是说NFV一般是四层或者是七层的应用啦】**，不再使用传统的昂贵且不易统一管理运维的硬件设备，而是改为部署在标准X86服务器上的NFV软件，实现灵活的功能部署和横向扩展。用户需要哪些NFV服务，只需要在标准的X86服务器上安装部署即可，随用随装，按需扩容。

### 弹性部署
#### 用户网络自定义：满足多样的用户网络需求。

#### 网络部署自动化：大量节省网络交付时间。

#### 丰富的互联能力：Internet出口，与用户自有机房通过专线互联/通过IPsec VPN互联、跨地域的云间互联。

#### 丰富的增值服务能力：防火墙，LB等L4-L7的网络服务，云数据库、云存储、docker等云服务。

### container技术和serverless架构

### BGP-EVPN
### IBGP RR
### 纯L3的overlay转发，规避大二层的BUM问题 


### 5.0V已经成功的在腾讯云黑石项目投入运营，并逐渐走向成熟，她以Infrastructure As Code的方式整合了腾讯所有IDC网络节点，并为上层的网络服务搭建了一个弹性敏捷的网络支撑平台。将腾讯的数据中心网络架构正式带入了SDN的时代。


## 青岛联通新建滨海数据中心 阿里已预订2/3 - C114中国通信网
http://m.c114.net/w119-907242.html
据C114了解，当前青岛联通数据中心拥有5个机房、5000多个机柜和10万台服务器，出口带宽达1480G、流量峰值达1100G，是北方最大的数据中心集群之一。

青岛是中国北方**国际海缆的唯一登陆点，拥有中美跨太平洋直达海缆（TPE）和东亚环球海缆（EAC）两个海缆**系统级3条海底光缆，是中国“八纵八横”骨干网络的重要节点。

## 类似阿里巴巴、百度、腾讯，他们的IDC机房现在都在哪里呢？一般是自己建的还是租用的？ - 知乎
https://www.zhihu.com/question/24993531



## 华为云数据中心
参见 为知笔记 华为-云数据中心解决方案
http://e.huawei.com/cn/solutions/business-needs/data-center/datacenter
