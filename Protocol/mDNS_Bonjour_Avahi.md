REF 
+ http://multicastdns.org/
+ https://support.apple.com/zh-cn/guide/deployment-reference-macos/apd0401947ff/1/web/1
+ https://www.cups.org/doc/network.html
+ https://binkery.com/archives/318.html
+ https://www.cnblogs.com/bonelee/p/7567029.html
+ https://www.jianshu.com/p/e66b0d400807
+ https://www.win.tue.nl/~johanl/educ/IoT-Course/mDNS-SD%20Tutorial.pdf
+ http://www.avahi.org/doxygen/v0.7/html/

# 1. mDNS
Multicast DNS is a way of using familiar DNS programming interfaces, packet formats and operating semantics, in a small network where 
no conventional DNS server has been installed.

Multicast DNS is a joint effort by participants of the IETF Zero configuration Networking (zeroconf) and DNS Extensions (dnsext)
working groups. The requirements are driveen by the zeroconf working group; the implementation details are a chartered work item for
for the DNSEXT group.

While the requirements for Zeroconf name resolution could be met by designing an entirely new protocol,it is better to provide this functionality by making minimal changes to the current standard DNS protocol. This saves application programmers from having to learn new APIs, and saves application programmers from having to write application code two different ways — one way for large configured networks and a different way for small Zeroconf networks. It means that most current applications need no changes at all to work correctly using mDNS in a Zeroconf network. It also means that engineers do not have to learn an entirely new protocol, and current network packet capture tools can already decode and display DNS packets, so they do not have to be updated to understand new packet formats.

mDNS , multicast DNS, 可以理解为局域网内部的 DNS 系统，它和 DNS 有很多相似的地方，通过它可以实现局域网内部的服务发现、查找和广播。同时它是基于组播的协议。
在局域网内，你要通过一台主机和其他主机进行通信，你需要知道对方的 ip 地址，但是有些时候，你并不知道对方的 ip 地址，因为一般使用 DHCP 动态分配 ip 地址的局域网内，各个主机的 IP 地址是由 DHCP 服务器来帮你分配 IP 地址的。所以在很多情况下，你要知道对方的 IP 地址是比较麻烦的。

首先，在 IP 协议里规定了一些保留地址，其中有一个是 224.0.0.251，对应的 IPv6 地址是 [FF02::FB]。
mDNS 协议规定了端口为 5353，而 DNS 的端口是 53。
mDNS 基于 UDP 协议。DNS 一般也是基于 UDP 协议的，但是也可以使用 TCP 协议。
如果理解了 DNS 协议，再去理解 mDNS 协议就很简单了，区别只是 mDNS 一般作用在一个局域网内的，有特定的 IP 地址，也就是 224.0.0.251,有特定的端口 5353,mDNS 的作用是实现局域网内的服务发现，查询，注册，DNS 作用是实现域名的解析，作用大概是一样的。

在客户端和服务端通信过程中（request,socket,websocket,ftp等），我们一般都需要知道对方的域名或者ip/port才能通信。
而在发送请求前，域名最终会经过一个叫DNS服务器的地方解析出相应的ip/port才能通信。
在局域网中，各个设备是没有域名的。此时我们只能通过ip/port来通信，但一般情况下各设备的ip是不固定的，它们是由DHCP分配的，在偶尔的掉线重连之后没准ip就变了，而且你也不知道要连接的设备的ip是多少。

* **RFC 6762 Multicast DNS** specifies how to perform DNS queries over IP Multicast.
# 2. DNS Service Discovery (DNS-SD)
DNS Service Discovery is a way of using standard DNS programming interfaces, servers, and packet formats to browse the network for services.

If you think the picture below looks a lot like the old Macintosh AppleTalk “Chooser”, that’s no coincidence. As we move away from AppleTalk to an all-IP world, we don’t want to have to give up the convenience and ease of use that made AppleTalk popular, and made AppleTalk continue to be popular long after it should rightfully have been retired.

* DNS Service Discovery is compatible with, but not dependent on, Multicast DNS.
* **RFC 6763 DNS-Based Service Discovery** describes how to perform network browsing and service discovery using only standard DNS packets and record types. DNS-SD is not dependent on Multicast DNS (it works with unicast as well); DNS-SD and mDNS are complementary technologies that can be used together.

There are several freely available implementationsof mDNS/DNS-SD:<br>
1.avahi–Linux implementation (http://www.avahi.org/)<br>
2.jmDNS–Java implementation(http://jmdns.sourceforge.net/)<br>
3.Bonjour –MACOS(installed by default)<br>
4.Bonjour –Windows (https://support.apple.com/kb/DL999?locale=en_US)<br>

# 3. Bonjour
The **mDNS** protocol, together with **DNS Service Discovery** (below), forms the basis for Apple's ease-of-use initiative called Bonjour. Apple began shipping mDNS in Mac OS X 10.2 in 2002, and 
today you'll find it in a wide range of hardware products, including 
* Apple AirPort base stations, 
* Axis network cameras, 
* Roku SoundBridges, 
* TiVo PVRs, 
* and just about every network printer from just about every printer manufacturer. 
It's also in an increasing number of Linux distributions, and it's available for Windows too.
---
Bonjour 是 Apple 基于标准的网络技术，旨在帮助设备和服务在同一网络上发现彼此。例如，iOS 设备使用 Bonjour 发现兼容“隔空打印”的打印机，iOS 设备和 Mac 电脑使用 Bonjour 来发现兼容“隔空播放”的设备（如 Apple TV）。某些 App 也使用 Bonjour 进行点对点协作和共享。

Bonjour 的工作原理是，使用多址广播流量通告服务的可用状态。由于多址广播流量通常不在子网中发送，因此需要 Apple TV 设备和“隔空打印”打印机与使用它们的 iOS 设备和 Mac 电脑处于同一个 IP 子网中。对于小型网络来说，这是标准做法。

尽管 Bonjour 最常用于在小型网络发现服务和设备，但它也可以通过使用 Bonjour 网关或类似技术进行配置，用于较大型网络中。将这一功能用于“隔空播放”的网络应当配置为同时通告 _airplay._tcp 和 _raop._tcp 服务。虽然可以在企业网络中使用高级 DNS 配置来通告某些 Bonjour 服务，但“隔空播放”需要使用隔空播放介绍中所描述的方法来发现实时设备。

macOS 和 Windows 版 Bonjour 客户端还可以使用传统的单播 DNS 来发现在世界各地任何可访问的域中通告的服务。使用 DNS 发现本地网络之外的服务称为广域 Bonjour。

A printer that supports Bonjour can be found automatically using the dnssd backend. Run the lpinfo(8) command to find your printer's URI:<br>
`$ lpinfo --include-schemes dnssd -v `<br>
`network dnssd://Acme%20Laser%20Pro._ipp._tcp.local./?uuid=545253fb-1cb7-4d8d-98ed-ab6cd607cea7` <br>
`network dnssd://Bar99._printer.tcp.local./?uuid=f9efff58-9086-4c95-accb-81dee876a475` <br>
`network dnssd://Example%20EX-42._ipps._tcp.local./?uuid=4a0c67ad-2824-4ddf-9115-7d4226c5fe65` <br>
`network dnssd://Foo%20Fighter-1969._pdl-datastream._tcp.local./?uuid=4e216bea-c3de-4f65-a710-c99e11c80d2b` <br>

# 4. Avahi
Avahi is a system which facilitates service discovery on a local network via the **mDNS/DNS-SD** protocol suite. This enables you to plug your laptop or computer into a network and instantly be able to view other people who you can chat with, find printers to print to or find files being shared. Compatible technology is found in Apple MacOS X (branded "Bonjour" and sometimes "Zeroconf").

Avahi is primarily targetted at Linux systems and ships by default in most distributions. It is not ported to Windows at this stage, but will run on many other BSD-like systems. The primary API is D-Bus and is required for usage of most of Avahi, however services can be published using an XML service definition placed in /etc/avahi/services.

通过如下命令在localhost public/register一个server名：test,协议：_test._tcp，端口：1234的server<br>
`avahi-publish -s test _test._tcp 1234`<br>

通过如下命令查询协议是_test._tcp的server名<br>
`avahi-browse _test._tcp -r`

`=     lo IPv4 test                                          _test._tcp           local` <br>
`hostname = [localhost]` <br>
`address = [127.0.0.1]`  <br>
`port = [1234]`          <br>
`txt = []`               <br>

You can also use avahi-discover to find the server. <br>
man avahi-discover - Browse for mDNS/DNS-SD services using the Avahi-daemon. <br>
Show a real-time graphical browse list for mDNS/DNS-SD network services running on the local LAN using the Avahi daemon. <br>

# 5. IPP (Internet Printing Protocol)
IPP is the only protocol that CUPS supports natively and is supported by most network printers and print servers. IPP supports encryption and other security features over port 631 and uses the http (Windows), ipp, and ipps backends. Device URIs for these backends look like this:<br>
`http://ip-address-or-hostname:port-number/printers/name/.printer`<br>
`ipp://ip-address/ipp/print`<br>
`ipp://ip-address-or-hostname/printers/name`<br>
`ipps://ip-address/ipp/print`<br>
`ipps://ip-address:443/ipp/print`<br>
`ipps://ip-address-or-hostname/printers/name`<br>

# 6. Other
## DHCP(动态主机配置协议)
是一个局域网的网络协议。指的是由服务器控制一段IP地址范围，客户机登录服务器时就可以自动获得服务器分配的IP地址和子网掩码。默认情况下，DHCP作为Windows Server的一个服务组件不会被系统自动安装，还需要管理员手动安装并进行必要的配置。

# 7. 总结
* mDNS协议将主机名解析为不包含本地名称服务器的小型网络中的IP地址
* mDNS可以与DNS-SD结合使用
* mDNS由Apple Bonjour和开源软件Avahi实现
* mDNS的域名与普通DNS的域名是通过后缀.local区分开来的。
* 每个进入局域网的主机，如果开启了mDNS服务的话，都会向局域网内的所有主机组播一个消息，我是谁，和我的IP地址是多少。然后其他也有该服务的主机就会响应，也会告诉你，它是谁，它的IP地址是多少。mDNS的域名与普通DNS的域名是通过后缀.local区分开来的。如果一台终端需要访问一个mDNS域名，他就会向局域网内发送组播，询问该域名的IP是多少。
比如，A主机进入局域网，开启了 mDNS 服务，并向 mDNS 服务注册以下信息：我提供 FTP 服务，我的IP是 192.168.1.101，端口是 21。当B主机进入局域网，并向 B 主机的 mDNS 服务请求，我要找局域网内 FTP 服务器，B主机的 mDNS 就会去局域网内向其他的 mDNS 询问，并且最终告诉你，有一个IP地址为 192.168.1.101，端口号是 21 的主机，也就是 A 主机提供 FTP 服务，所以 B 主机就知道了 A 主机的 IP 地址和端口号了。
* 某台打印机设置如下：<br>
   `[IPv4设定]-[DNS设定]-[Host名]：Tesscf9d6c`<br>
   `[IPv4设定]-[mDNS设定]:ON`<br>
   `[IPv4设定]-[mDNS设定]-[mDNS名]:Tess MF7XXC`<br>
   
   客户端 
   + 运行$driverless, 输出 <br>
      `ipp://Tesscf9d6c.local:631/ipp/print`
   + 运行$lpinfo -v, 输出 <br>
      `network dnssd://Tess%20MF7XXC._ipp._tcp.local/?uuid=6d4ff0ce-6b11-11d8-8020-f4a997cf9d6c` <br>
      `network ipp://Tesscf9d6c.local:631/ipp/print` <br>
   + 通过ipp-over-usb得到的dnssd name:Tess MF7XXC
