
参考 
linux 网络虚拟化： network namespace 简介 – Cizixs Writes Here
<http://cizixs.com/2017/02/10/network-virtualization-network-namespace>

	
	2017年9月18日  自己的试验： 
	
	ip-link - network device configuration
	
	ip netns add ns1
	ip netns add ns2
	
	ip link add veth_ns1_to_ns2 type veth peer name veth_ns2_to_ns1
	
	
	# 注意改了veth的名字空间之后，接口配置会全部清空，所以需要重新配置ip地址、设置up
	ip link set veth_ns1_to_ns2 netns ns1
	ip netns exec ns1 ip link set veth_ns1_to_ns2 up
	ip netns exec ns1 ip addr add 10.0.12.1/24 dev veth_ns1_to_ns2
	ip netns exec ns1 ip route
	
	# 注意改了veth的名字空间之后，接口配置会全部清空，所以需要重新配置ip地址、设置up
	ip link set veth_ns2_to_ns1 netns ns2
	ip netns exec ns2 ip link set veth_ns2_to_ns1 up
	ip netns exec ns2 ip addr add 10.0.12.2/24 dev veth_ns2_to_ns1
	ip netns exec ns2 ip route
	
	# 创建ns1 和 虚拟bridge 互联的veth对
	ip link add veth_b_to_ns1 type veth peer name veth_ns1_to_b
	
	# 创建ns2 和 虚拟bridge 互联的veth对
	ip link add veth_b_to_ns2 type veth peer name veth_ns2_to_b
	
	# 创建虚拟bridge
	# Some devices are not allowed to change network namespace: loopback, bridge, ppp, wireless.
	# 也就是说bridge只能在根命名空间中
	ip link add bridgeA  type bridge
	ip link set bridgeA up
	ip link
	
	# 把veth放到bridgeA上
	ip link set veth_b_to_ns1 master bridgeA
	# 和更改veth的名字空间一样，改device也要重新设置UP
	ip link set veth_b_to_ns1 up 
	ip addr add 10.12.12.1 dev veth_b_to_ns1  
	ip link set veth_b_to_ns2 master bridgeA
	# 和更改veth的名字空间一样，改device也要重新设置UP
	ip link set veth_b_to_ns2 up 
	ip addr add 10.12.12.2 dev veth_b_to_ns2  
	
	# 把veth放入ns1、ns2
	ip link set veth_ns1_to_b netns ns1
	ip link set veth_ns2_to_b netns ns2
	
	
	ip netns exec ns1 ip link set veth_ns1_to_b up
	ip netns exec ns1 ip addr add 10.0.0.1/24 dev veth_ns1_to_b
	ip netns exec ns1 ip addr
	ip netns exec ns1 ip route
	
	ip netns exec ns2 ip link set veth_ns2_to_b up
	ip netns exec ns2 ip addr add 10.0.0.2/24 dev veth_ns2_to_b
	ip netns exec ns2 ping 10.0.0.1
	ip netns exec ns2 ip addr
	ip netns exec ns2 ip route
	
	
