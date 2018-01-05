


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

## 应用程序安装-软件包管理

### Redhat和Fedora和SUSE用rpm包
安装：yum install <package_name> 
卸载：yum remove <package_name> 
更新：yum update <package_name>

### Debian Ubuntu用deb包
安装：apt-get install <package_name> 
卸载：apt-get remove <package_name> 
更新：apt-get update <package_name>

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



# other-resources

- 最实用的 Linux 命令行使用技巧 - 文章 - 伯乐在线
<http://blog.jobbole.com/112265/>

- 最实用的 Linux 命令行使用技巧
http://mp.weixin.qq.com/s/HbP5VwpWfQkyeWISCrOD7w
