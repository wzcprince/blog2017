


# shell

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



# 自己的实践

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

