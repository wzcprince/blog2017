

# 重要书籍
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



