
# language



## 通用思想


- 编程语言，大致分为两类：
面向机器的系统级语言
面向业务的业务语言
c+是特例



- 防御式编程 defensive programming 保证系统健壮性
契约式编程 design by contract  适用于模块内部，不要每个函数都TMD对指针判空



- 和python一样，java里的lambda表达式，
其实就是匿名函数，消除了return语句 
http://zh.lucida.me/blog/java-8-lambdas-insideout-language-features/
随着回调模式和函数式编程风格的日益流行，
我们需要在Java中提供一种尽可能轻量级的将代码封装为数据（Model code as data）的方法。 

- fd = fileno(fp);
fp = fdopen(fd);

- 什么是函数式编程思维？ 
https://www.zhihu.com/question/28292740  
函数式编程关心数据的映射，命令式编程关心解决问题的步骤
这里的映射就是数学上「函数」的概念——一种东西和另一种东西之间的对应关系。
这也是为什么「函数式编程」叫做「函数」式编程。

- 变量命名，宏命名，L2VPN_AFI和AFI_L2VPN可以同时命名呀！！！不要一根筋！！

- _PAGE_BIT_GLOBAL 如果是比特位标记，就带上BIT吧




## C

### _Bool
C99 added a builtin _Bool data type (see Wikipedia for details), and if you #include <stdbool.h>, it provides bool as a macro to _Bool.

You asked about the Linux kernel in particular. It assumes the presence of _Bool and provides a bool typedef itself in include/linux/types.h.


### Byte-Order-Bit-Order

Byte and Bit Order Dissection | Linux Journal
<https://www.linuxjournal.com/article/6788>

MAC address - Wikipedia
<https://en.wikipedia.org/wiki/MAC_address#Bit-reversed_notation>

字节序(byte order)和位序(bit order) - liuxingen的专栏 - CSDN博客
<http://blog.csdn.net/liuxingen/article/details/45420455>

### structure-bitfield
位域
再谈C语言位域 | Tony Bai
<http://tonybai.com/2013/05/21/talk-about-bitfield-in-c-again/>


### define-enum-member-in-struct

参见 linux kernel

	struct net_device {
	...

	enum { NETREG_UNINITIALIZED=0,
	       NETREG_REGISTERED,	/* completed register_netdevice */
	       NETREG_UNREGISTERING,	/* called unregister_netdevice */
	       NETREG_UNREGISTERED,	/* completed unregister todo */
	       NETREG_RELEASED,		/* called free_netdev */
	       NETREG_DUMMY,		/* dummy device for NAPI poll */
	} reg_state:8;
	...
	
	}

	static inline const char *netdev_reg_state(const struct net_device *dev)
	{
		switch (dev->reg_state) {

			case NETREG_UNINITIALIZED: return " (uninitialized)";
			case NETREG_REGISTERED: return "";
			case NETREG_UNREGISTERING: return " (unregistering)";
			case NETREG_UNREGISTERED: return " (unregistered)";
			case NETREG_RELEASED: return " (released)";
			case NETREG_DUMMY: return " (dummy)";
		}
	
		WARN_ONCE(1, "%s: unknown reg_state %d\n", dev->name, dev->reg_state);
		return " (unknown)";
	}

### linux-dst_entry 

	
	struct dst_entry {
	...
		unsigned short		flags;
	#define DST_HOST		0x0001
	#define DST_NOXFRM		0x0002
	#define DST_NOPOLICY		0x0004
	#define DST_NOHASH		0x0008

### linux-rb_node

	struct rb_node {
	    unsigned long  __rb_parent_color;
	    struct rb_node *rb_right;
	    struct rb_node *rb_left;
	} __attribute__((aligned(sizeof(long))));
	#define __rb_parent(pc)    ((struct rb_node *)(pc & ~3))
	#define __rb_color(pc)    ((pc) & 1)

### linux-naming


哈哈，linux kernel里也有很水的名字哟： 
ip_finish_output
ip_finish_output2


### 帖子
C语言中结构体赋值的讨论  <http://blog.csdn.net/hazir/article/details/9429017>
字节序及位域使用 <http://blog.csdn.net/wangpeihuixyz/article/details/24433655> 






## C++

C++ Core Guidelines
<https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md>

Google C++ Style Guide
<https://google.github.io/styleguide/cppguide.html>

### 隐藏-覆盖-动态绑定


只要基类在定义成员函数时已经声明了virtual关键字，在派生类实现的时候覆盖该函数时，virtual关键字可加可不加，不影响多态的实现。
容易与隐藏混淆：
隐藏是指派生类的函数屏蔽了与其同名的基类函数，规则如下：
 
1) 如果派生类的函数与基类的函数同名，但是参数不同。此时，不论有无virtual关键字，基类的函数将被隐藏（注意别与重载混淆）。
 
2) 如果派生类的函数与基类的函数同名，并且参数也相同，但是基类函数没有virtual关键字。此时，基类的函数被隐藏（注意别与覆盖混淆）。

To trigger dynamic binding, two conditions must be met:
First, only member functions that are specified as a virtual can be dynamically bound. 
By default, member functions are not virtual; non-virtual functions are not dynamically bound.
Second, the call must be made through a reference or a pointer to a base-class type[没必要是derived type，那就不需要动态绑定喽].



## python




### 帖子

#### __file__
python __file__ 和sys.argv[0]的区别
http://andylin02.iteye.com/blog/933237  

用 os.path.basename(__file__)

#### 帖子2
【笔记】《由浅入深SCF无服务器云函数实践》 - CSDN博客
http://blog.csdn.net/csdn_duomaomao/article/details/78910588
三. 使用云函数快速嵌入图片类型识别功能
base64和json都用到啦

#### 帖子3
Useful Python Functions and Features You Need to Know
<http://www.oschina.net/translate/python-functions?cmp>


####
为什么有人说 Python 的多线程是鸡肋呢？ - 知乎
<https://www.zhihu.com/question/23474039>

- multiprocessing库，这个库是基于multi process实现了类multi thread的API接口，并且用pickle部分地实现了变量共享。







# shell
全部放在： 
<https://github.com/wzcprince/blog2017/blob/master/level2/linux-command-line-interface-skill.md#shell>





# programming specification
编程规范


## naming

may_mknod linux内核代码中好多以may_开头的函数，表示是否可以。。。

likely很可能的

work_done 完成的工作量
budget 预算
if (unlikely(work_done >= budget))




