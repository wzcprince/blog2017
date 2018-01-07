



What is CWND and RWND? 
https://blog.stackpath.com/glossary/cwnd-and-rwnd/

如何计算TCP吞吐量 - 智深
https://my.oschina.net/astute/blog/93132  

拥塞控制算法，两类： 基于丢包、 基于时延即delay / RTT

NewReno 依赖RTT

RTT 
路越远RTT越大；
中间路上的设备的缓存区被占满时，RTT也会变大；

+++++++++++++++++++++++++++++++
http://blog.csdn.net/zhangskd/article/details/6715751 写的比较乱 
基于丢包反馈的协议
 
近几年来，随着高带宽延时网络（High Bandwidth-Delay product network）的普及，针对提高TCP带宽利用率这一点上，又涌现出许多新的基于丢包反馈的TCP协议改进，这其中包括HSTCP、STCP、BIC-TCP、CUBIC和H-TCP。
总的来说，基于丢包反馈的协议是一种被动式的拥塞控制机制，其依据网络中的丢包事件来做网络拥塞判断。即便网络中的负载很高时，只要没有产生拥塞丢包，协议就不会主动降低自己的发送速度。这种协议可以最大程度的利用网络剩余带宽，提高吞吐量。然而，由于基于丢包反馈协议在网络近饱和状态下所表现出来的侵略性，一方面大大提高了网络的带宽利用率；但另一方面，对于基于丢包反馈的拥塞控制协议来说，大大提高网络利用率同时意味着下一次拥塞丢包事件为期不远了，所以这些协议在提高网络带宽利用率的同时也间接加大了网络的丢包率，造成整个网络的抖动性加剧。

+++++++++++++++++++++++++++++++



吞吐量:throughput ; 
带宽: bandwidth
我觉得大致可以理解为： throughput = bandwidth * RTT
TCP/IP卷一 BDP (bandwidth delay product) 

+++++++++++++++++++++++++++++++

Reno是目前应用最广泛且较为成熟的算法。该算法所包含的慢启动、拥塞避免和快速重传、快速恢复机制，是现有的众多算法的基础。 
New Reno
https://tools.ietf.org/html/rfc6582  
partial acknowledgment
This document describes a modification to the fast recovery algorithm in RFC 5681
that incorporates a response to partial acknowledgments received during fast recovery.
We call this modified fast recovery algorithm NewReno, because it is
a slight but significant variation of the behavior that has been historically referred to as Reno.

The NewReno modification applies to the fast recovery procedure that
   begins when three duplicate ACKs are received 
and ends when either a retransmission timeout occurs 
             or an ACK arrives that acknowledges all of the data 
                    up to and including the data that was outstanding 
                    when the fast recovery procedure began.


Linux TCP拥塞控制算法原理解析 
http://www.cnblogs.com/NerdWill/p/5020885.html
其中有对NewReno的详细解释


+++++++++++++++++++++++++++++++

CUBIC Overview
https://archive.is/20121212100254/http://research.csc.ncsu.edu/netsrv/

 
  
【时间T的函数，其他基本都是常量，所以与时延RTT、丢包都无关喽】



So after a window reduction, the window grows very fast, but as it gets closer to Wmax, it slows down its growth. At Wmax, its increment becomes zero. After that, the window grows slowly, accelerating its growth as it moves away from Wmax. It has the same plateau as in BIC's window curve, but its growth rate accelerates much more slowly than BIC's. This slow growth significantly contributes to the improved TCP friendliness of the protocol. Furthermore, the function extremely simplifies the window control since there are only one function to use and no multiple phases.



TCP’s congestion control implementation in the Linux kernel v 3.6.6. 
https://wiki.aalto.fi/download/attachments/69901948/TCP-CongestionControlFinal.pdf



Our main focus has been explaining the recovery state machine in the code and high level abstractions of congestion control’s algorithm implementation.
4.1 TCP Cubic in theory
TCP cubic is one of the newest modifications to the TCP
congestion control algorithm that changes the linear window
growth function of TCP to a cubic function, in order to improve
the bandwidth utilization in case of high bandwidth
delay product networks. It also achieves a better level of
fairness among flows with different round trip times. All
these attributes make the cubic the default congestion control
algorithm in Linux.

As it comes from the name of this algorithm the window
growth function is a cubic function of elapsed time since the
last packet loss. 



Linux Kernel 4.9 中的 BBR 算法与之前的 TCP 拥塞控制相比有什么优势？ - 知乎
https://www.zhihu.com/question/53559433


https://groups.google.com/forum/#!forum/bbr-dev


https://tools.ietf.org/html/draft-cardwell-iccrg-bbr-congestion-control-00

http://queue.acm.org/detail.cfm?id=3022184

合入记录
https://git.kernel.org/pub/scm/linux/kernel/git/davem/net-next.git/commit/?id=0f8782ea14974ce992618b55f0c041ef43ed0b78&context=3&ignorews=1&dt=1

 

http://www.baike.com/wiki/ZetaTCP
http://www.appexnetworks.com.cn/white-papers/ZetaTCP.pdf



可以将TCP BBR算法模块化到低版本内核取代锐速吗
http://blog.csdn.net/dog250/article/details/61384409  

依赖于精准的测量
曾经的Reno时代，TCP依靠数学模型来收敛到平衡，现在BBR依靠精准的测量来收敛到平衡，孰好孰坏？
        来做一个类比，这两者的差别不会大于推导出的模型与数据训练出的模型之间的差异。一个典型的例子就是吴军在《智能时代》里关于人工智能的阐述。在上世纪50，60年代，人们普遍相信可以通过“算法”来让计算机获得智能。然后在经历了持续的失败后，人们把目光集中在数据上。
        既然已经有了足够多的全量数据-而不是采样数据，既然这些数据都是实实在在真实的，那么这些数据表现出的模式一定就是真实的，问题是如何提炼出这些模式。在这个大数据的背景下，一开始没有什么公式，也没有什么算法，有的只有数据，前提是数据必须是真实的。----BBR和深度学习都是基于数据的！
        那么如果数据是不真实的，会怎样？后果会很严重，会把计算引入歧途，最终的模型也会与真实的情况大相径庭。
        BBR如今也不再依赖既有的“数学公式”，比如它不是从一个AIMD控制论模型开始的，而是完全基于一系列的精确测量，测量即时带宽，测量CA rtt，测量Seq rtt...然后根据一个非常简单的网络管道模型，基于“最大实测带宽”与“最小实测CA rtt”来计算“不排队时”的速率和BDP，这个过程本身就是收敛的，关键点在于“不排队”，只要不主动占用队列，连接就不会崩溃，所有的连接就能公平共享带宽，这正是TCP收敛的重要目标。





