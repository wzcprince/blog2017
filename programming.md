
# language
## C

### _Bool
C99 added a builtin _Bool data type (see Wikipedia for details), and if you #include <stdbool.h>, it provides bool as a macro to _Bool.

You asked about the Linux kernel in particular. It assumes the presence of _Bool and provides a bool typedef itself in include/linux/types.h.



### 帖子
C语言中结构体赋值的讨论  http://blog.csdn.net/hazir/article/details/9429017
字节序及位域使用 http://blog.csdn.net/wangpeihuixyz/article/details/24433655 




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


