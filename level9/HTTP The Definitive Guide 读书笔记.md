

# overview

**本书已经过时啦，只需要挑着读一读基本概念就好啦 **
web - How outdated is “HTTP: The Definitive Guide”? - Stack Overflow
<https://stackoverflow.com/questions/33549316/how-outdated-is-http-the-definitive-guide>



# ch01 HTTP overview

## 1.2 web client and server

## 1.3 resouces

### 1.3.1 media types

MIME (Multipurpose Internet Mail Extensions) 
从电子邮件系统移植到web系统中来的

## 1.4 Transactions

包括 请求 响应 


- 请求
	- Method
		- Get
		- Put
		- Post
		- Head
		- Delete
- 响应
	- Status Code
		- 200 OK
		- 302 redirect
		- 404 Can't find the resource

### 1.4.3 一个web page通常包含多次transaction

**一个web page包含多个资源，因此需要多次transaction **

The browser performs one transaction to fetch the HTML
“skeleton” that describes the page layout, then issues additional HTTP transactions
for each embedded image, graphics pane, Java applet, etc. These embedded
resources might even reside on different servers, as shown in Figure 1-6. Thus, a
“web page” often is a collection of resources, not a single resource

## 1.5 Message

请求响应的报文格式很相似

- start line
- header fields
- body



## 1.6 connections

### 1.6.3 telnet作为客户端与HTTP服务器交互


#### telnet本质
The Telnet utility connects your keyboard to a destination TCP port and connects the TCP port output back to your display screen. 

【本质 telnet通过tcp socket，把telnet进程的std in重定向到tcp socket的输入流，把tcp socket的输出流重定向到telnet进程的std out】


## 1.7 HTTP versions


### HTTP-NG(a.k.a. HTTP/2.0)



## 1.8 Architectual Components of the Web


### 1.8.1 Proxies


### 1.8.2 Caches 


### 1.8.3 Gateways


### 1.8.3 Tunnels


### 1.8.4 Agents





