



# design-patterns

## facade

设计模式之-门面模式 - CSDN博客
<http://blog.csdn.net/lizhitao/article/details/38360351>

design patterns - Façade vs. Mediator - Stack Overflow
<https://stackoverflow.com/questions/481984/façade-vs-mediator>

wrapper-facade.dvi
<http://www.cs.wustl.edu/~schmidt/PDF/wrapper-facade.pdf>

- This paper describes the Wrapper Facade pattern. The intent
of this pattern is to encapsulate low-level functions and data
structures with object-oriented (OO) class interfaces. Common
examples of the Wrapper Facade pattern are class libraries
like MFC, ACE, and AWT that encapsulate native
OS C APIs, such as sockets, pthreads, or GUI functions.



# 重要资料


State 设计模式 一种对象行为模式， Allow an object responds differently depending on its current state.


## 熊怡-架构与模块设计
2014年9月4日 


2016年4月26日 【下面的这一段不确定是否是熊怡说的】
csdn草稿箱里的，标题是【模块 设计】
【第二次听熊怡大师关于模块的讲座？？？】

大系统的设计和小模块的设计是相通的，

●分层设计
应用场景：大型系统，大型开发团队
要解决的问题：系统内部组件之间当然有交互和组件的独立开发演进

如何做到真正的分层？小模块设计中业务逻辑层要与数据实体操作层分开，但我们容易按照操作发生的时间顺序设计编码，忽略了层次；
要以业务逻辑为中心而不是操作的时间顺序设计编码

上层调用下层接口，最好是只调用相邻下层的接口，并通过注册回调函数来解决下层需要调用上层接口的特殊情况

●各种设计模式的使用

●订阅模式

用来解除耦合的好办法！
最好的结果就是，一方只依赖于另一方提供的接口，除了接口之外其他的（包括接口的具体实现）一切都不需要去关心
【我自己理解，有接口本身就是一种耦合，问题关键在于如何把耦合限制在可控范围内，
两个模块的关联要仅限于明确定义的接口，具体结构如何实现，对于接口的使用者一定要是透明才行，】

●不是任何东西都需要框架，要分析成本、代价

●可扩展性是V8平台最重要的属性，二是可靠性



 

## 软件架构实践读书笔记总结
Software Architecture in Practice, Third Edition

### software architecture的定义
P4-P6
software architecture is the set of structures needed to reason about【推理论证】 the system,
which comprise software elements, relations among them, and poperties of both.

P5右下
architecture consists of structures and structures consist of elements and relations.

#### 1.a set of software structures

P5
**对重要关键的系统属性有用的structure才能叫architecture structure**

#### 2.an abstraction 
an abstraction that is essential to taming the complexity of a system.

an architecture is foremost an **abstraction** of a system that selects certain details and suppresses others. 
**In all modern systems**, element被partition为public and private parts
- public parts就是接口，elements interact with each other by means of interfaces.系统架构正是基于此
- private parts也就是private implementation details of elements are **NOT architectural**

We simply cannot, and do not want to deal with all of the complexity all the time.
【做合理的抽象，把整个系统**分解分割划分partition**为子系统、子模块，从而降低复杂度】

#### 3.每个软件系统都有

#### 4.include behavior【但不是全部都有行为】

- embodies体现 how elements interact with each other
- can be used to reason about the system



### architecture representation的三种view
在P9的1.2. Architectural Structures and Views 有讲解
#### static
强调系统的功能分解分割划分partition
- 每个模块的主要功能、职责
- 模块间的关系，比如
  - decomposition
  - use
  - depend on

#### runtime
强调runtime behavior、interactions，也叫component-and-connector structures
帮我们回答以下问题：
- 运行时的组件如何交互
- How does **data progress through the system**
- 等等
**crucially important about the system's runtime properties 
such as performance, security, availability, and more**

#### allocation
强调和系统外部的分配关系，比如
- 某个模块运行在哪个CPU上，
- 在development,testing,building过程中，某个模块保存在哪些文件里
- 某个模块由哪个开发团队来开发

### 本书重要术语
#### element指either a module or a component
P5
##### module强调static
partition system into implementation units

##### component强调runtime
component一般是runtime entity

#### view
P10 
a view is a representation of a structure

#### connector
P10 
interaction = connector
P11 
communication vehicles among components such as call-return, process synchronization operators, pipes



