
# essential

## pgrep

pgrep, pkill - look up or signal processes based on name and other attributes

       pgrep  looks  through  the  currently  running processes and lists the process IDs which match the
       selection criteria to stdout.  All the criteria have to match.  For example,

              $ pgrep -u root sshd

       will only list the processes called sshd AND owned by root.  On the other hand,

              $ pgrep -u root,daemon

       will list the processes owned by root OR daemon.

       pkill will send the specified signal (by default SIGTERM) to each process instead of listing  them
       on stdout.

用法参见 
[gdb-manually-make-coredump](#gdb-manually-make-coredump)

 








# shell

## 帖子
shell环境变量以及set,env,export的区别  http://blog.csdn.net/iitvip/article/details/11950699


## Redirection
重定向 (计算机) - 维基百科，自由的百科全书
<https://zh.wikipedia.org/wiki/重定向_(计算机)>

Redirection (computing) - Wikipedia
<https://en.wikipedia.org/wiki/Redirection_(computing)>


- 管道
- 命令tee可以将一个命令的输出重定向到几个目标


		Shell重定向＆>file、2>&1、1>&2的区别:
		http://www.360doc.cn/article/7044580_287544243.html
		0表示标准输入
		1表示标准输出
		2表示标准错误输出
		> 默认为标准输出重定向，与 1> 相同
		2>&1 意思是把 标准错误输出 重定向到 标准输出.
		&>file 意思是把 标准输出 和 标准错误输出 都重定向到文件file中
		用例子说话：
		1. grep da * 1>&2
		2. rm -f $(find / -name core) &> /dev/null
		上面两例中的 & 如何理解，&不是放到后台执行吗?
		牛解：
		1.&>file或n>&m均是一个独立的重定向符号，不要分开来理解。
		2.明确文件和文件描述符的区别。
		3.&>file表示重定向标准输出和错误到文件


## heredoc-format 

- Here document - Wikipedia
<https://en.wikipedia.org/wiki/Here_document#Unix_shells>

In computing, a here document (here-document, here-text, heredoc, hereis, here-string or here-script) is a file literal or input stream literal: it is a section of a source code file that is treated as if it were a separate file. The term is also used for a form of multiline string literals that use similar syntax, preserving line breaks and other whitespace (including indentation) in the text.
Here documents originate in the Unix shell, and are found in sh, csh,[1] ksh, bash and zsh, among others.


- linux - How does "cat << EOF" work in bash? - Stack Overflow
<https://stackoverflow.com/questions/2500436/how-does-cat-eof-work-in-bash>
From man bash:Here Documents
This type of redirection instructs the shell to read input from the current source until a line containing only word (with no trailing blanks) is seen.

### 实例1
7. Virtio_user for Container Networking — Data Plane Development Kit 18.02.0-rc0 documentation
http://www.dpdk.org/doc/guides/howto/virtio_user_for_container_networking.html
cat <<EOT >> Dockerfile
FROM ubuntu:latest
WORKDIR /usr/src/dpdk
COPY . /usr/src/dpdk
ENV PATH "$PATH:/usr/src/dpdk/x86_64-native-linuxapp-gcc/app/"
EOT









# app


## iptables

25 个常用的 Linux iptables 规则 - 文章 - 伯乐在线
<http://blog.jobbole.com/108468/>


## 磁盘管理工具

### df disk free displays the free (meaning available) storage space on the hard disk.

### du disk usage displays the storage space in use (meaning not available) on the hard disk.

### di di - disk information
  Displays usage information on mounted filesystems. 

## 应用程序安装-软件包管理

### Redhat和Fedora和SUSE用rpm包
安装：yum install <package_name> 
卸载：yum remove <package_name> 
更新：yum update <package_name>

### Ubuntu和Debian用deb包
安装：apt-get install <package_name> 
卸载：apt-get remove <package_name> 
更新：apt-get update <package_name>

### Ubuntu离线安装deb包
deb是debian发行版的软件包
ubuntu是基于debian 发行的 所以可以用

	https://docs.docker.com/engine/installation/linux/docker-ce/ubuntu/
	中的章节 Install from a package： 可以下载到 Docker CE for Ubuntu的deb安装包
	dpkg -i docker-ce_17.03.1-ce-0-ubuntu-xenial_amd64.deb
	dpkg: dependency problems prevent configuration of docker-engine:
	 docker-engine depends on libltdl7 (>= 2.4.6); however:
	  Package libltdl7 is not installed.
	在pkgs.org/搜索libltdl7 
	https://pkgs.org/download/libltdl7 

## ssh

- SSH连接超时(ssh timeout) 解决办法，参见 http://www.linuxidc.com/Linux/2013-02/79941.htm
在/etc/ssh/sshd_config中增加ClientAliveInterval 60, ClientAliveInterval指定了服务器端向客户端请求消息的时间间隔, 默认是0, 不发送.而ClientAliveInterval 60表示每分钟发送一次, 然后客户端响应, 这样就保持长连接了


## gdb

- gdb file 命令
- gdb frame命令
- core-file用来指定core dump文件
	- 需要先file指定exe，再用core-file指定core dump文件，否则无法打印调用栈

### gdb自动化

- scripting - What are the best ways to automate a GDB debugging session? - Stack Overflow
<https://stackoverflow.com/questions/10748501/what-are-the-best-ways-to-automate-a-gdb-debugging-session>
- c - How to print every executed line in GDB automatically until a given breakpoint is reached? - Stack Overflow
<https://stackoverflow.com/questions/6947389/how-to-print-every-executed-line-in-gdb-automatically-until-a-given-breakpoint-i#>



### gdb-manually-make-coredump
Core dump - ArchWiki
<https://wiki.archlinux.org/index.php/Core_dump#Making_a_core_dump>

找到目标进程

	$ pgrep -f firefox
	2071 firefox

Attach to the process:

	$ gdb -p 2071

Then at the (gdb) prompt:

	(gdb) generate-core-file
	Saved corefile core.2071
	(gdb) quit





## stace
使用 Strace 和 GDB 调试工具的乐趣
<https://www.ibm.com/developerworks/cn/aix/library/au-unix-strace.html>

- strace pwd
启动一个新进程同时strace

- strace -e trace=network -p 4009
对现在正在运行的进程进行strace



## iproutes工具包

ip link set ens38 up
ip address add 1.1.1.1/24 dev ens38

ip route add default via 192.168.11.2 dev ens38
ip route replace default via 192.168.11.2 dev ens38

ip neighbor add 192.168.11.2  lladdr  00:0c:29:0f:d8:05 nud permanent dev ens38
ip neighbor change 192.168.11.2  lladdr  00:0c:29:0f:d8:05 nud permanent dev ens38


## mount
Linux系统中自动mount需配置/etc/fstab文件，此文件是专门用来存放文件系统的静态信息的文件。Linux系统启动时会自动从这个文件读取信息，并完成其指定的文件系统挂载任务。
参见 <http://www.linuxidc.com/Linux/2012-04/59110.htm>

## chattr
change file attributes on a Linux file system









# 自己的实践

## 修改时区

　　如果要修改时区并且马上生效，可以更换/etc/localtime 文件来实现。比如修改时区为中国上海，那么就可以使用如下的命令来使得时区的更改生效。

　　cp /usr/share/zoneinfo/Asia/Shanghai /etc/localtime

　　然后最好使用下面的命令将更改写入bios。

　　hwclock

　　--------------------------------

　　具体操作：

　　[root@localhost ~]# cp /usr/share/zoneinfo/Asia/Shanghai /etc/localtime

　　cp: overwrite `/etc/localtime'? y

　　[root@localhost ~]# date

　　Sat Feb 20 16:04:43 CST 2010

　　[root@localhost ~]# hwclock

　　Sat 20 Feb 2010 04:05:12 PM CST -0.474966 seconds

## Ubuntu-setup-smbd

- ubuntu server 16.04的代号为
Ubuntu 16.04 LTS (Xenial Xerus)
切换root用户 sudo -s 或者是  sudo su

- ubuntu apt源 更改为国内的服务器，好快好快！！！
参考， http://blog.csdn.net/xysoul/article/details/43214105
Ubuntu 16.04 LTS (Xenial Xerus)的话需要把trusty替换为xenial
修改 /etc/apt/sources.list 为：
deb http://mirrors.sohu.com/ubuntu/ xenial main restricted universe multiverse
deb http://mirrors.sohu.com/ubuntu/ xenial-security main restricted universe multiverse
deb http://mirrors.sohu.com/ubuntu/ xenial-updates main restricted universe multiverse
deb http://mirrors.sohu.com/ubuntu/ xenial-proposed main restricted universe multiverse
deb http://mirrors.sohu.com/ubuntu/ xenial-backports main restricted universe multiverse
deb-src http://mirrors.sohu.com/ubuntu/ xenial main restricted universe multiverse
deb-src http://mirrors.sohu.com/ubuntu/ xenial-security main restricted universe multiverse
deb-src http://mirrors.sohu.com/ubuntu/ xenial-updates main restricted universe multiverse
deb-src http://mirrors.sohu.com/ubuntu/ xenial-proposed main restricted universe multiverse
deb-src http://mirrors.sohu.com/ubuntu/ xenial-backports main restricted universe multiverse

- 更改过/etc/apt/sources.list之后一定要执行apt-get update进行更新
- 然后就可以  apt install samba 了
- systemctl restart smbd 

## setup-VMWaretools
	
	2017-08-13 
	安装 VMWare tools，共享windows Host上的文件到linux虚拟机
	
	在VMware软件里操作了 “安装VMWare tools” 之后
	在虚拟机的linux系统中实际是在/dev/cdrom中
	
	mkdir /opt/vmwaretools 
	mount /dev/cdrom /opt/vmwaretools
	
	然后执行
	tar -xf  /opt/vmwaretools/VMwareTools-10.0.0-2977863.tar.gz
	cd /opt/vmware-tools-distrib/
	./vmware-install.pl
	然后一路Enter即可
	
	查看/mnt/hgfs/里就可以看到windows上共享给linux的文件夹了

## test-docker

![](http://p14ws25od.bkt.clouddn.com/201801052003_14.png)

# other-resources

- 最实用的 Linux 命令行使用技巧 - 文章 - 伯乐在线
<http://blog.jobbole.com/112265/>

- 最实用的 Linux 命令行使用技巧
http://mp.weixin.qq.com/s/HbP5VwpWfQkyeWISCrOD7w

- 升级内核
	- Ubuntu系统中升级Linux内核的一般步骤
<http://www.jb51.net/os/Ubuntu/378727.html>
	- Debian的linux内核可以以deb形式安装： Ubuntu肯定也可以吧
<http://blog.csdn.net/MENGHUANBEIKE/article/details/73909957>

- 技术|如何判断 Linux 服务器是否被入侵？
<https://linux.cn/article-9116-1.html>

