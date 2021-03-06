

ROS在百度自动驾驶的探索和实践
<http://www.infoq.com/cn/presentations/ros-in-baidu-automatic-driving>

如何评价百度免费开放无人驾驶能力的 Apollo 计划? - 知乎
<https://www.zhihu.com/question/58778536/answer/193303141>




#百度Apollo自动驾驶超大复杂软件系统的探索和实践
<http://www.sohu.com/a/195520900_470008>

今天主要介绍 ROS 框架，以及 ROS 框架应用在自动驾驶过程中**所遇到的问题和相应的改进**，同时介绍 Apollo 框架如何下载、如何使用以及如何在本地获取最基本的版本。

为什么要用框架，
一是需要高效的开发支持。自动驾驶处于快速迭代和快速发展过程中，无论感知算法、决策算法还是整体技术开发，无论是以 2D 为主的视觉方案还是以 3D 为主的方案，都在快速迭代中，对快速地构建系统和功能验证有非常大的需求。通过使用框架开发希望算法工程师能够将更多精力放在算法功能的研发上，而诸如配置管理、部署运行、底层通信等功能由框架来统一提供，这样可以快速地构建系统原型，验证算法和功能。

二是希望框架能够让模块灵活配置。像感知、定位、决策模块，本身都是功能相对独立的模块，模块之间只有数据依赖关系，对于框架来说，需要能够在开发阶段减少各个模块之间的耦合，而在车上运行阶段能够将各个模块组合串联起来。

三是自动驾驶系统涉及大量图像、主体算法，对于各种可视化工具有非常强烈的需求，比如障碍物检测算法，需要看图像识别障碍物框得准不准，规划路径是否合理，定位算法也需要看调试时车是不是在正确位置上，所以调试过程中可视化工具的支持也是非常重要的一点。

以上三点是框架最需要满足的要求。

基于以上的问题选择了 ROS 作为现在开发和调试的框架。

基于以上的问题选择了 ROS 作为现在开发和调试的框架。做机器人和无人车相关研究的同行一般都会比较了解 ROS 框架。ROS 前身是斯坦福的人工智能实验室开发的一个机器人集成开发框架，从软件构架的角度说，它是一种**基于消息传递通信的分布式多进程框架**。ROS 很早就被机器人行业所使用，很多知名的机器人开源库，比如基于四元数的坐标转换、3D 点云处理驱动、定位算法 SLAM 等都是开源贡献者基于 ROS 开发的。截止现在为止，ROS 框架大概有 3000 多个基础库，有这么丰富的基础库的支持，我们基于 ROS 的开发可以达到很高的效率。

因为 ROS 是基于消息机制的，开发者可以根据功能把软件拆分成为各个模块，每个模块只是负责读取和分发消息，模块间通过消息关联，并完成最终的功能。当模块间真正要上车的时候，通过我们的框架可以把各个模块快速地集成到一起。

是否 ROS 就能够满足我们所有的工程需求，答案并不是。在我们实际调试过程中遇到很多 ROS 带来的问题。因为 ROS 本身的定位是基于学术研究、快速搭建原形的框架，所以在工程化考虑并不是很多，比如**大数据传输时的性能问题，ROS 基于 Master 单中心拓扑的单点问题，以及数据格式缺乏兼容性问题**，都对我们的使用造成一定影响。


Apollo对ROS 的改进
## 同一个机器上的节点间共享内存代替socket

目前同一个机器上的 ROS 节点之间通过 socket 进行进程间通信，中间存在多层协议栈以及多次用户空间和内核空间的数据拷贝，造成了很多不必要的资源占用和性能损耗。

这在普通的机器人系统数据量不大的时候并没有问题，而在数据量很大的无人车系统中，该问题就会显著地影响系统的性能。

针对这个问题，我们选择使用共享内存的方式来替代 socket 作为进程间通信的方式，通过减少不必要的内存拷贝，大大降低了系统的传输延时和资源占用。从这个图上可以看到，通过内存优化，数据拷贝、延迟和消耗都是原来的一半左右。

上面讲的是 1 对 1 的传输场景下的优化，现在我们来看下在单对多的传输场景。无人车系统中单个传感器数据经常会被多个算法或工具使用，如上图示例，对于 camera 的图像，同时会有障碍物检测、红绿灯识别、定位等等模块使用。

ROS 在底层并没有实现多播机制，在处理一对多的消息传输时，底层实现实际是多个点对点的连接，当把一份数据要发给四个节点时，相同的数据会传输四次，这造成了很大的资源浪费。

基于共享内存传输方式，共享内存本身的特性天然能够支持一次写入、多次读取功能，对于一对多的传输场景，相同的数据包只需要写入一次即可，成倍地提高了传输的效率。

【共享内存的实际效果：减少占用的计算资源和存储资源：】
共享内存传输延迟基本会比原生 socket 节省 50%，现在系统整个传输延迟需要 100 毫秒，共享内存能节省 50 毫秒。当车行驶速度 70 公里时，1 秒走 50 米左右，50 毫秒就是 1 米多，对整个系统有很大帮助。

共享内存 CPU 资源占用也要比 socket 减少很多，车载计算硬件不可能无限扩容，在车上硬件资源的分配是非常重要的。如果能在传输过程中减少更多资源消耗，把更多计算资源留给算法，一定能够提升算法能力。
![](http://p14ws25od.bkt.clouddn.com/201801121720_404.png)

## 去中心化代替Master
ROS 是以 Master 为中心构建的 Hybrid p2p 拓扑网络，有比较强的容错性，当某个算法出现异常导致崩溃的时候，不会引起整个系统的异常，为局部异常处理提供了便利。

ROS 系统并不是一个完整的 P2P 拓扑网络。ROS 拓扑网络完全基于中心节点，各个节点都需要通过 Master 注册，并且通过 Master 获得网络的拓扑状态。上图左边是 ROS 节点连接的过程示例，一个发布者启动时会发布数据，当订阅者启动时，会向 Master 注册要接收的信息，Master 对所有结点注册信息进行统一整理之后，会通知订阅者所订阅消息的发布情况，并且把发布者通信地址传给订阅者，订阅者会通过地址与发布者建立连接，建立连接之后，发布者和订阅者通过点对点传输方式进行真实的消息传播。真实的数据传播都是在发送者和接收者之间的点对点传输，数据不需要通过 Master，能减少数据的传播和 Master 的负载。但是也存在一个致命弱点，整个系统非常依赖 Master 这个单点，一旦 Master 崩溃，所有节点都不能发现其他节点，这样整个系统就不能正常工作。

虽然 Master 使用频率不是很高，但是通过加监控程序监控 Master 状态，如果挂掉立刻重启也不能解决这个问题。因为 ROS 并没有 Master 的异常恢复机制，Master 里所有节点的注册信息，只存在 Master 内存中，并没有持久化或其他存储方式，所以当 Master 崩溃后，Master 里所有消息随之消失，即使重启 Master，也无法使其恢复。所以 Master 这个单点在现有结构上是很难解决的。

Master 单点的问题在多机的方案中更加明显。一般自动驾驶系统中是多机方案，当一套自动驾驶系统由两台机器构成时，一般用于冗余备份，但由于 ROS Master 的存在，两台机器并不是对等的。

![](http://p14ws25od.bkt.clouddn.com/201801121720_159.png)


如上图所示，如果 Master 部署在 A 机上，当 CompuerA 出现宕机后，ComputerB 中的节点无法再访问 Master 获取拓扑信息，虽然已经建立过的点对点连接可以继续使用，但新加入的节点或者拓扑变化将不再能更新，系统处于一个功能不完整的状态，失去了冗余系统的意义。

为了解决这个问题，我们在 ROS 在里面加入了基于 RTPS 协议的服务发现功能。

![](http://p14ws25od.bkt.clouddn.com/201801121727_847.png)


整个网络拓扑不再以 master 为中心构建，而是通过域的概念进行划分。所有节点加入域中，会通过 RTPS 协议相互广播和其他节点建立点对点连接，建立连接后再通过单播进行订阅、发布话题等消息交换，以替代 Master 作为中央信息交换的功能。

节点发现之后，所有节点间会两两建立 unicast 连接，并且基于这个连接做消息交换。比如节点需要发布或订阅一个消息，作为消息的交换。
网络中一个新节点加入时，会通过广播通知域内的所有节点，广播内容包括 NODE 的名字，以及 NODE 的通信地址。广播是基于不可抗协议的周期性心跳信息，每隔几秒钟会向所有的节点发送通信方式，保证消息不会被丢弃。
节点发现之后，所有节点间会两两建立 unicast 连接，并且基于这个连接做消息交换。比如节点需要发布或订阅一个消息，作为消息的交换。
基于消息交换的通道，已有节点会对新加入节点发送历史拓扑消息。比如系统发布一个消息，此时订阅者还没有加入网络，过了一段时间后订阅者加入网络，遗失了之前的拓扑信息，因此需要已有节点向新加入节点发布所有历史拓扑信息，这样就不会有历史消息丢失的问题。订阅者收到信息，会与对应发布者建立点对点连接，之后这两个节点就可以直接进行点对点通信。

通过这种方式，能够使 ROS 网络的拓扑发现不再依赖 Master 单点，完全实现网络拓扑。对于多机拓扑、冗余备份和仿真都有很大帮助。而且这个修改是完全基于 ROS 底层的修改，对上层应用完全透明，原有的 ROS 程序使用这套协议不需要对代码做任何修改就可以直接适配。

## 使用ProtoBuf消息数据兼容性
【接口兼容性，使用 protobuf 来替代 ROSmessage】

ROS 通信通过 message，message 是 ROS 中描述软件组件接口的一种语言。当两个节点之间需要建立连接时，通常需要满足两个条件，一是接收和发送的 Topic 属于同一个话题，而且两个模块定义的模式是完全一致的。就像打电话一样，Topic 是对方电话号码，message 是说话语言，如果使用不同语言，双方还是无法通信，所以 message 是组件的接口语言。

ROS 系统为了保证收发双方的消息格式一致，会对 message 做 MD5 校验。只有 messageMD5 值完全一样的节点可以通信。这种严格的校验导致了节点的兼容性问题。比如一个接口增加了一个新的可有可无的字段，但是因为它的增加导致 MD5 变化，系统就识别为一种新的消息，当需要与其他模块进行通信时，就会遇到 MD5 mismatch 的问题。甚至只调整两三个字段的顺序都会有 MD5 的变化，会有兼容性的问题。在项目规模比较小时影响不大，但是对无人自动驾驶这样庞大的项目就有很大影响。当某一个模块接口升级了，需要把所有相关模块升级到最新版本之后，才能一起进行基础功能的联调。同时在线下仿真时，经常需要把某一个模块回溯到历史版本验证或定位某一个问题，这时候接口之间出现升级，就会出现不兼容问题，导致系统完全跑不起来。
接口兼容性问题会对历史数据使用造成更大影响，无人车系统中历史数据是非常宝贵和重要的资源，可以做离线训练。由于 ROS 系统对于 message 严格的校验机制，导致不同版本的数据只能用于对应版本的程序，进行运行和仿真，老版本数据不能用于新版本系统进行回归测试，新版本的数据也不能用于老版本的系统，这样对于历史数据的价值和使用造成非常大影响。

对于这种问题，虽然可以通过离线批量转换或运行时 adapter 来解决，但对于无人车这样每年产生的数据以 T，甚至以 P 计算的庞大系统，如果经常做数据转换迁移，无论在技术上还是效率上都是难度很大，很难实现的。

基于这个问题，我们决定使用 protobuf 来替代 ROSmessage。protobuf 是现在比较流行的接口语言，最大好处是丰富的类型系统，包括常规类型，可以完全覆盖 message 本身包含的类型，有利于把既有的 ROSmessage 迁移到 protobuf 格式下。此外 protobuf 最重要的一点是有非常良好的兼容性支持，我们只需要在使用的时候谨慎的使用 required 字段，就能带来非常好的前向兼容性和后向兼容性。

在使用 protobuf 过程中也会遇到一些问题，由于 ROS 本身并不原生支持 Protobuf 的消息，在开源社区对此的使用一般是先将 Protobuf 消息序列化为 String，再使用 ROS 的 String 方式进行传输。

但这种方案本身无论在使用的成本还是实际效果上，都存在一定的问题，而且由于消息本身都是以序列化后的 String 方式使用，在调试工具中无法支持，会出现乱码等问题。

基于这种情况，ApolloROS 做了一整套对 protobuf 的支持，做了相应的定制和修改，对于开发者来说可以完全沿用 ros message 的使用方式，比如在可以编译的时候，完整地编译出文件。在工程中不需要做任何其他转换，同时在使用的时候能够正确地解析出 protobuf 消息。这样既能够很好地解决兼容性问题，也不会有额外的学习成本和使用成本。

以上是我们在 ApolloROS 版本中做的更新和优化，但是是否 ROS 加上这些优化就可以胜任无人车的计算方案，最后做工程化和产品化落地，答案是否定的。在实际使用中，由于 ROS 的价格问题，缺乏实时性的支持和确定性保障，以及缺少统一的全局调度和资源管理，而且如果产品化发布，我们希望自动驾驶系统能够有更高的集成性和更强的鲁棒性，这些 ROS 系统很难实现和支持。对此，我们在内部也使用了新一代纯自然的计算框架，系统解决相关问题，目前在内部测试和使用中。后续如果比较稳定会随后面的 Apollo 计划开放出来给大家使用。


## 后续计划






