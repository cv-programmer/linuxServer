# 网络基础

## 说明

本部分笔记及源码出自`slide/04Linux网络编程/01 网络基础`

## 网络结构模式

### C/S结构

#### 简介

- 服务器 - 客户机，即 `Client - Server（C/S）`结构。C/S 结构通常采取两层结构。服务器负责数据的管理，客户机负责完成与用户的交互任务。客户机是因特网上访问别人信息的机器，服务器则是提供信息供人访问的计算机。

- 客户机通过局域网与服务器相连，接受用户的请求，并通过网络向服务器提出请求，对数据库进行操作。服务器接受客户机的请求，将数据提交给客户机，客户机将数据进行计算并将结果呈现给用户。服务器还要提供完善安全保护及对数据完整性的处理等操作，并允许多个客户机同时访问服务器，这就对服务器的硬件处理数据能力提出了很高的要求。

- 在C/S结构中，应用程序分为两部分：服务器部分和客户机部分。服务器部分是多个用户共享的信息与功能，执行后台服务，如控制共享数据库的操作等；客户机部分为用户所专有，负责执行前台功能，在出错提示、在线帮助等方面都有强大的功能，并且可以在子程序间自由切换。

#### 优点

- 能充分发挥客户端 PC 的处理能力，很多工作可以在客户端处理后再提交给服务器，所以 C/S 结构客户端响应速度快
- 操作界面漂亮、形式多样，可以充分满足客户自身的个性化要求
- C/S 结构的管理信息系统具有较强的事务处理能力，能实现复杂的业务流程
- 安全性较高，C/S 一般面向相对固定的用户群，程序更加注重流程，它可以对权限进行多层次校验，提供了更安全的存取模式，对信息安全的控制能力很强，一般高度机密的信息系统采用 C/S 结构适宜

#### 缺点

- 客户端需要安装专用的客户端软件。首先涉及到安装的工作量，其次任何一台电脑出问题，如病毒、硬件损坏，都需要进行安装或维护。系统软件升级时，每一台客户机需要重新安装，其维护和升级成本非常高
- 对客户端的操作系统一般也会有限制，不能够跨平台

### B/S结构

#### 简介

- `B/S 结构（Browser/Server，浏览器/服务器模式）`，是 WEB 兴起后的一种网络结构模式，WEB浏览器是客户端最主要的应用软件。这种模式统一了客户端，将系统功能实现的核心部分集中到服务器上，简化了系统的开发、维护和使用。

- 客户机上只要安装一个浏览器，如 Firefox 或 InternetExplorer，服务器安装 SQL Server、Oracle、MySQL 等数据库。浏览器通过 Web Server 同数据库进行数据交互

#### 优点

- B/S 架构最大的优点是总体拥有成本低、维护方便、 分布性强、开发简单，可以不用安装任何专门的软件就能实现在任何地方进行操作，客户端零维护，系统的扩展非常容易，只要有一台能上网的电脑就能使用

#### 缺点

- 通信开销大、系统和数据的安全性较难保障
- 个性特点明显降低，无法实现具有个性化的功能要求
- 协议一般是固定的：http/https
- 客户端服务器端的交互是请求-响应模式，通常动态刷新页面，响应速度明显降低

## MAC地址

### 网卡

- `网卡`是一块被设计用来允许计算机在计算机网络上进行通讯的计算机硬件，又称为`网络适配器`或`网络接口卡NIC`。其拥有 MAC 地址，属于 `OSI` 模型的第 2 层，它使得用户可以通过电缆或无线相互连接。

- 每一个网卡都有一个被称为 MAC 地址的独一无二的 **48 位串行号**

- 网卡的主要功能：1.数据的封装与解封装、2.链路管理、3.数据编码与译码

![image-20211027130051135](04Linux网络编程/image-20211027130051135.png)

### MAC地址

- `MAC 地址（Media Access Control Address）`，直译为媒体存取控制位址，也称为局域网地址、以太网地址、物理地址或硬件地址，它是一个用来确认网络设备位置的位址，由网络设备制造商生产时烧录在网卡中

- 在 `OSI` 模型中，**第三层网络层负责 IP 地址**，**第二层数据链路层则负责 MAC位址** 

- MAC 地址用于在网络中唯一标识一个网卡，一台设备若有一或多个网卡，则每个网卡都需要并会有一个唯一的 MAC 地址

## IP地址

### 简介

- `IP 协议`是为计算机网络相互连接进行通信而设计的协议。在因特网中，它是**能使连接到网上的所有计算机网络实现相互通信的一套规则，规定了计算机在因特网上进行通信时应当遵守的规则**。任何厂家生产的计算机系统，只要遵守 `IP 协议`就可以与因特网互连互通。各个厂家生产的网络系统和设备，如以太网、分组交换网等，它们相互之间不能互通，**不能互通的主要原因是因为它们所传送数据的基本单元（技术上称之为“帧”）的格式不同**

- `IP 协议`实际上是一套由软件程序组成的协议软件，它把各种不同“帧”统一转换成`IP 数据报`格式，这种转换是因特网的一个最重要的特点，使所有各种计算机都能在因特网上实现互通，即具有“开放性”的特点。正是因为有了 IP 协议，因特网才得以迅速发展成为世界上最大的、开放的计算机通信网络。因此，IP 协议也可以叫做“因特网协议”

- IP 地址（Internet Protocol Address）是指互联网协议地址，又译为网际协议地址。

- IP 地址是 IP协议提供的一种统一的地址格式，它为互联网上的每一个网络和每一台主机分配一个逻辑地址，以此来屏蔽物理地址的差异

- **IP 地址是一个 32 位的二进制数，通常被分割为 4 个“ 8 位二进制数”（也就是 4 个字节）**

- IP 地址通常用`点分十进制`表示成（`a.b.c.d`）的形式，其中，a,b,c,d都是 0~255 之间的十进制整数。例：点分十进IP地址（100.4.5.6），实际上是 32 位二进制数（01100100.00000100.00000101.00000110）

### **IP** 地址编址方式

- 最初设计互联网络时，**为了便于寻址以及层次化构造网络，每个 IP 地址包括两个标识码（ID）**，即`网络ID` 和`主机 ID`。同一个物理网络上的所有主机都使用同一个网络 ID，网络上的一个主机（包括网络上工作站，服务器和路由器等）有一个主机 ID 与其对应
- Internet 委员会定义了 5 种 IP 地址类型以适合不同容量的网络，即 A 类~ E 类

- 其中 A、B、C 3类（如下表格）由 InternetNIC 在全球范围内统一分配，D、E 类为特殊地址
  - A类最高位不能为1，所以是$2^7$
  - 主机数要减去2是因为去掉`x.x.x.0`和`x.x.x.255`这两个特殊的地址

| 类别 |    最大网络数     |        IP地址范围         |  单个网段最大主机数  |       私有IP地址范围        |
| :--: | :---------------: | :-----------------------: | :------------------: | :-------------------------: |
|  A   |   126($2^7-1$)    |  1.0.0.1~126.255.255.254  | 16777214($2^{24}-2$) |   10.0.0.0~10.255.255.255   |
|  B   |  16384($2^{14}$)  | 128.0.0.1~191.255.255.254 |  65534($2^{16}-2$)   |  172.16.0.0~172.31.255.255  |
|  C   | 2097152($2^{21}$) | 192.0.0.1~223.255.255.254 |     254($2^8-2$)     | 192.168.0.0~192.168.255.255 |

### A类IP地址

- 一个 A 类 IP 地址是指， 在 IP 地址的四段号码中，**第一段号码为网络号码，剩下的三段号码为本地计算机的号码**
- 如果用二进制表示 IP 地址的话，A 类 IP 地址就由 1 字节的网络地址和 3 字节主机地址组成，**网络地址的最高位必须是`0`**
- A 类 IP 地址中网络的标识长度为 8 位，主机标识的长度为 24 位，A类网络地址数量较少，有 126 个网络，每个网络可以容纳主机数达 1600 多万台

- A 类 IP 地址 地址范围 `1.0.0.1 - 126.255.255.254`（二进制表示为：`00000001 00000000 00000000 00000001 - 01111111 11111111 11111111 11111110`），最后一个是广播地址
- A 类 IP 地址的子网掩码为 255.0.0.0，每个网络支持的最大主机数为$2^{24}-2$

### B类IP地址

- 一个 B 类 IP 地址是指，在 IP 地址的四段号码中，**前两段号码为网络号码，剩下的两段号码为本地计算机的号码**
- 如果用二进制表示 IP 地址的话，B 类 IP 地址就由 2 字节的网络地址和 2 字节主机地址组成，**网络地址的最高位必须是`10`**
- B 类 IP地址中网络的标识长度为 16 位，主机标识的长度为 16 位，B 类网络地址适用于中等规模的网络，有16384 个网络，每个网络所能容纳的计算机数为 6 万多台
- B 类 IP 地址地址范围 `128.0.0.1 - 191.255.255.254` （二进制表示为：`10000000 00000000 00000000 00000001 - 10111111 11111111 11111111 11111110`）， 最后一个是广播地址
- B 类 IP 地址的子网掩码为 255.255.0.0，每个网络支持的最大主机数为$2^{16}-2$

### C类IP地址

- 一个 C 类 IP 地址是指，在 IP 地址的四段号码中，**前三段号码为网络号码，剩下的一段号码为本地计算机的号码**
- 如果用二进制表示 IP 地址的话，C 类 IP 地址就由 3 字节的网络地址和 1 字节主机地址组成，**网络地址的最高位必须是`110`**
- C 类 IP 地址中网络的标识长度为 24 位，主机标识的长度为 8 位，C 类网络地址数量较多，有 209 万余个网络。适用于小规模的局域网络，每个网络最多只能包含254台计算机
- C 类 IP 地址范围 `192.0.0.1-223.255.255.254` （二进制表示为: `11000000 00000000 00000000 00000001 - 11011111 11111111 11111111 11111110`），最后一个是广播地址
- C类IP地址的子网掩码为 255.255.255.0，每个网络支持的最大主机数为$2^8-2$

### D类IP地址

- D 类 IP 地址在历史上被叫做`多播地址（multicast address）`，即`组播地址`
- 在以太网中，多播地址命名了一组应该在这个网络中应用接收到一个分组的站点。多播地址的最高位必须是 `1110`，范围从`224.0.0.0 - 239.255.255.255`

### 特殊的网址

- 每一个字节都为 0 的地址（ `0.0.0.0` ）对应于**当前主机**
- IP 地址中的每一个字节都为 1 的 IP 地址（ `255.255.255.255` ）是**当前子网的广播地址**

- IP 地址中凡是以 `11110` 开头的 E 类 IP 地址都保留用于将来和实验使用
- IP地址中**不能以十进制 `127` 作为开头**，该类地址中数字 `127.0.0.1 ~ 127.255.255.255` 用于回路测试，如：`127.0.0.1`可以代表**本机IP地址**

### 子网掩码

- `子网掩码（subnet mask）`又叫网络掩码、地址掩码、子网络遮罩，它是一种用来指明一个 IP 地址的哪些位标识的是主机所在的子网，以及哪些位标识的是主机的位掩码
- 子网掩码不能单独存在，它必须结合 IP 地址一起使用
- 子网掩码只有一个作用，就是将某个 IP 地址划分成`网络地址`和`主机地址`两部分
- 子网掩码是一个 **32 位地址**，用于屏蔽 IP 地址的一部分以区别网络标识和主机标识，并说明该 IP地址是在局域网上，还是在广域网上

> 子网掩码是在 IPv4 地址资源紧缺的背景下为了解决 lP 地址分配而产生的虚拟 lP 技术，通过子网掩码将A、B、C 三类地址划分为若干子网，从而显著提高了 IP 地址的分配效率，有效解决了 IP 地址资源紧张的局面。另一方面，在企业内网中为了更好地管理网络，网管人员也利用子网掩码的作用，人为地将一个较大的企业内部网络划分为更多个小规模的子网，再利用三层交换机的路由功能实现子网互联，从而有效解决了网络广播风暴和网络病毒等诸多网络管理方面的问题
>
> 在大多数的网络教科书中，一般都将子网掩码的作用描述为通过逻辑运算，将 IP 地址划分为网络标识(Net.ID) 和主机标识(Host.ID)，只有网络标识相同的两台主机在无路由的情况下才能相互通信
>
> 根据 RFC950 定义，子网掩码是一个 32 位的 2 进制数， 其对应网络地址的所有位都置为 1，对应于主机地址的所有位置都为 0。子网掩码告知路由器，地址的哪一部分是网络地址，哪一部分是主机地址，使路由器正确判断任意 IP 地址是否是本网段的，从而正确地进行路由。网络上，数据从一个地方传到另外一个地方，是依靠 IP 寻址。从逻辑上来讲，是两步的。第一步，从 IP 中找到所属的网络，好比是去找这个人是哪个小区的；第二步，再从 IP 中找到主机在这个网络中的位置，好比是在小区里面找到这个人
>
> 子网掩码的设定必须遵循一定的规则。与二进制 IP 地址相同，子网掩码由 1 和 0 组成，且 1 和 0 分别连续。子网掩码的长度也是 32 位，左边是网络位，用二进制数字 “1” 表示，1 的数目等于网络位的长度；右边是主机位，用二进制数字 “0” 表示，0 的数目等于主机位的长度。这样做的目的是为了让掩码与 IP 地址做按位与运算时用 0 遮住原主机数，而不改变原网络段数字，而且很容易通过 0 的位数确定子网的主机数（ 2 的主机位数次方 - 2，因为主机号全为 1 时表示该网络广播地址，全为 0 时表示该网络的网络号，这是两个特殊地址）。通过子网掩码，才能表明一台主机所在的子网与其他子网的关系，使网络正常工作

## 端口

### 简介

- `端口` 是英文 port 的意译，可以认为是设备与外界通讯交流的出口
- 端口可分为`虚拟端口`和`物理端口`
  - 虚拟端口指计算机内部或交换机路由器内的端口，不可见，是特指TCP/IP协议中的端口，是逻辑意义上的端口，例如计算机中的 80 端口、21 端口、23 端口等
  - 物理端口又称为接口，是可见端口，计算机背板的 RJ45 网口，交换机路由器集线器等 RJ45 端口。电话使用 RJ11 插口也属于物理端口的范畴

- 端口是通过端口号来标记的，端口号只有整数，范围是从 0 到65535（$2^{16}$）

### 端口类型

#### 周知端口（Well Known Ports）

- 周知端口是众所周知的端口号，也叫知名端口、公认端口或者常用端口，**范围从 0 到 1023**，它们紧密绑定于一些特定的服务，例如 80 端口分配给 WWW 服务，21 端口分配给 FTP 服务，23 端口分配给Telnet服务等等

- 我们在 IE 的地址栏里输入一个网址的时候是不必指定端口号的，因为在默认情况下WWW 服务的端口是 “80”
- 网络服务是可以使用其他端口号的，如果不是默认的端口号则应该在地址栏上指定端口号，方法是**在地址后面加上冒号“:”（半角），再加上端口号**。比如使用 “8080” 作为 WWW服务的端口，则需要在地址栏里输入`网址:8080`
- 有些系统协议使用固定的端口号，它是不能被改变的，比如 139 端口专门用于 NetBIOS 与 TCP/IP 之间的通信，不能手动改变

#### 注册端口（Registered Ports）

- **端口号从 1024 到 49151**，它们松散地绑定于一些服务，分配给用户进程或应用程序，这些进程主要是用户选择安装的一些应用程序，而不是已经分配好了公认端口的常用程序。这些端口在没有被服务器资源占用的时候，可以用用户端动态选用为源端口

#### 动态端口 / 私有端口（Dynamic Ports / Private Ports）

- 动态端口的范围是从 **49152 到 65535**，之所以称为动态端口，是因为它一般不固定分配某种服务，而是动态分配

## 网络模型

### OSI七层参考模型

- 七层模型，亦称 `OSI（Open System Interconnection）参考模型`，即`开放式系统互联`。参考模型是国际标准化组织（ISO）制定的一个用于计算机或通信系统间互联的标准体系，一般称为 OSI 参考模型或七层模型
- 它是一个七层的、抽象的模型体，不仅包括一系列抽象的术语或概念，也包括具体的协议

![image-20211113162413475](04Linux网络编程/image-20211113162413475.png)

- **物理层**：主要定义物理设备标准，如网线的接口类型、光纤的接口类型、各种传输介质的传输速率等。它的**主要作用是传输比特流（就是由1、0转化为电流强弱来进行传输，到达目的地后再转化为1、0，也就是我们常说的数模转换与模数转换）**。这一层的数据叫做**比特**
- **数据链路层**：建立**逻辑连接**、进行**硬件地址寻址**、**差错校验**等功能。定义了如何让格式化数据**以帧为单位**进行传输，以及如何让控制对物理介质的访问。**将比特组合成字节进而组合成帧，用MAC地址访问介质**
- **网络层**：进行**逻辑地址寻址**，在位于不同地理位置的网络中的两个主机系统之间提供连接和路径选择。Internet的发展使得从世界各站点访问信息的用户数大大增加，而网络层正是管理这种连接的层
- **传输层**：**定义了一些传输数据的协议和端口号**（ WWW 端口 80 等），如：**TCP**（传输控制协议，传输效率低，可靠性强，用于传输可靠性要求高，数据量大的数据），**UDP**（用户数据报协议，与TCP 特性恰恰相反，用于传输可靠性要求不高，数据量小的数据，如 QQ 聊天数据就是通过这种方式传输的）。 主要是将从下层接收的数据进行分段和传输，到达目的地址后再进行重组。常常把这一层数据叫做段
- **会话层**：通过传输层（端口号：传输端口与接收端口）建立数据传输的通路。主要在你的系统之间发起会话或者接受会话请求
- **表示层**：数据的表示、安全、压缩。主要是**进行对接收的数据进行解释、加密与解密、压缩与解压缩**等（也就是把计算机能够识别的东西转换成人能够能识别的东西（如图片、声音等）
- **应用层**：网络服务与最终用户的一个接口。这一层为用户的应用程序（例如电子邮件、文件传输和终端仿真）提供网络服务

### TCP/IP四层模型

#### 简介（==图可能有错误==）

- 现在 Internet（因特网）使用的主流协议族是 **TCP/IP 协议族**，它是一个分层、多协议的通信体系。TCP/IP协议族是一个四层协议系统，自底而上分别是`数据链路层`、`网络层`、`传输层`和`应用层`。每一层完成不同的功能，且通过若干协议来实现，上层协议使用下层协议提供的服务

![image-20211113170131416](04Linux网络编程/image-20211113170131416.png)

#### OSI七层与TCP/IP四层

![image-20211113170257066](04Linux网络编程/image-20211113170257066.png)

#### 四层介绍

- `应用层`：应用层是 TCP/IP 协议的第一层，是直接为应用进程提供服务的
  - 对不同种类的应用程序它们会根据自己的需要来使用应用层的不同协议，邮件传输应用使用了 SMTP 协议、万维网应用使用了 HTTP 协议、远程登录服务应用使用了有 TELNET 协议
  - 应用层还能加密、解密、格式化数据
  - 应用层可以建立或解除与其他节点的联系，这样可以充分节省网络资源
- `传输层`：作为 TCP/IP 协议的第二层，运输层在整个 TCP/IP 协议中起到了中流砥柱的作用。且在运输层中， TCP 和 UDP 也同样起到了中流砥柱的作用
- `网络层`：网络层在 TCP/IP 协议中的位于第三层。在 TCP/IP 协议中网络层可以进行网络连接的建立和终止以及 IP 地址的寻找等功能
- `网络接口层`：在 TCP/IP 协议中，网络接口层位于第四层。由于网络接口层兼并了物理层和数据链路层所以，网络接口层既是传输数据的物理媒介，也可以为网络层提供一条准确无误的线路

## 协议

### 简介

- 协议，网络协议的简称，网络协议是通信计算机双方必须共同遵从的一组约定。如怎么样建立连接、怎么样互相识别等。只有遵守这个约定，计算机之间才能相互通信交流。它的三要素是：`语法`、`语义`、`时序`

- 为了使数据在网络上从源到达目的，网络通信的参与方必须遵循相同的规则，这套规则称为`协议（protocol）`，它最终体现为在网络上传输的数据包的格式

- 协议往往分成几个层次进行定义，分层定义是为了使某一层协议的改变不影响其他层次的协议

### 常见协议

- 应用层协议
  - FTP协议（File Transfer Protocol 文件传输协议）
  - HTTP协议（Hyper Text Transfer Protocol 超文本传输协议）
  - NFS（Network File System 网络文件系统）
- 传输层协议
  - TCP协议（Transmission Control Protocol 传输控制协议）
  - UDP协议（User Datagram Protocol 用户数据报协议）
- 网络层协议
  - IP 协议（Internet Protocol 因特网互联协议）
  - ICMP 协议（Internet Control Message Protocol 因特网控制报文协议）
  - IGMP 协议（Internet Group Management Protocol 因特网组管理协议）。
- 网络接口层协议
  - ARP协议（Address Resolution Protocol 地址解析协议）
  - RARP协议（Reverse Address Resolution Protocol 反向地址解析协议）

### UDP协议

![image-20211113201253530](04Linux网络编程/image-20211113201253530.png)

- 源端口号：发送方端口号
- 目的端口号：接收方端口号
- 长度：UDP用户数据报的长度，最小值是8（仅有首部）
- 校验和：检测UDP用户数据报在传输中是否有错，有错就丢弃

### TCP协议

![image-20211113201404105](04Linux网络编程/image-20211113201404105.png)

- 源端口号：发送方端口号
- 目的端口号：接收方端口号
- 序号：本报文段的数据的第一个字节的序号
- 确认号：期望收到对方下一个报文段的第一个数据字节的序号
- 头部长度（数据偏移）：TCP 报文段的数据起始处距离 TCP 报文段的起始处有多远，即首部长度。==单位：32位，即以 4 字节为计算单位==？？？
- 保留：占 6 位，保留为今后使用，目前应置为 0
- 紧急 `URG` ：此位置 1 ，表明紧急指针字段有效，它告诉系统此报文段中有紧急数据，应尽快传送
- 确认 `ACK`：仅当 ACK=1 时确认号字段才有效，TCP 规定，在连接建立后所有传达的报文段都必须把 ACK 置1
- 推送 `PSH`：当两个应用进程进行交互式的通信时，有时在一端的应用进程希望在键入一个命令后立即就能够收到对方的响应。在这种情况下，TCP 就可以使用推送（push）操作，这时，发送方TCP 把 PSH 置 1，并立即创建一个报文段发送出去，接收方收到 PSH = 1 的报文段，就尽快地（即“推送”向前）交付给接收应用进程，而不再等到整个缓存都填满后再向上交付
- 复位 `RST`：用于复位相应的 TCP 连接
- 同步 `SYN`：仅在三次握手建立 TCP 连接时有效。当 SYN = 1 而 ACK = 0 时，表明这是一个连接请求报文段，对方若同意建立连接，则应在相应的报文段中使用 SYN = 1 和 ACK = 1。因此，SYN 置1 就表示这是一个连接请求或连接接受报文
- 终止 `FIN`：用来释放一个连接。当 FIN = 1 时，表明此报文段的发送方的数据已经发送完毕，并要求释放运输连接
- 窗口：指发送本报文段的一方的接收窗口（而不是自己的发送窗口）
- 校验和：校验和字段检验的范围包括首部和数据两部分，在计算校验和时需要加上 12 字节的伪头部
- 紧急指针：仅在 URG = 1 时才有意义，它指出本报文段中的紧急数据的字节数（紧急数据结束后就是普通数据），即指出了紧急数据的末尾在报文中的位置，注意：即使窗口为零时也可发送紧急数据
- 选项：长度可变，最长可达 40 字节，当没有使用选项时，TCP 首部长度是 20 字节

### IP协议

![image-20211113205020978](04Linux网络编程/image-20211113205020978.png)

- 版本号：IP 协议的版本。通信双方使用过的 IP 协议的版本必须一致，目前最广泛使用的 IP 协议版本号为 4（即IPv4)
- 头部长度：单位是 32 位（4 字节）
- 服务类型：一般不适用，取值为 0
- 总长度：指首部加上数据的总长度，单位为字节
- 标识（identification）：IP 软件在存储器中维持一个计数器，每产生一个数据报，计数器就加 1，并将此值赋给标识字段
- 标志（flag）：目前只有两位有意义
  - 标志字段中的最低位记为 MF。MF = 1 即表示后面“还有分片”的数据报。MF = 0 表示这已是若干数据报片中的最后一个
  - 标志字段中间的一位记为 DF，意思是“不能分片”，只有当 DF = 0 时才允许分片
- 片偏移：指出较长的分组在分片后，某片在源分组中的相对位置，也就是说，相对于用户数据段的起点，该片从何处开始。片偏移以 8 字节为偏移单位
- 生存时间：TTL，表明是数据报在网络中的寿命，即为`跳数限制`，由发出数据报的源点设置这个字段。路由器在转发数据之前就把 TTL 值减一，当 TTL 值减为零时，就丢弃这个数据报，常见为**64和128**
- 协议：指出此数据报携带的数据时使用何种协议，以便使目的主机的 IP 层知道应将数据部分上交给哪个处理过程，常用的 ICMP(1)，IGMP(2)，TCP(6)，UDP(17)，IPv6（41）
- 首部校验和：只校验数据报的首部，不包括数据部分
- 源地址：发送方 IP 地址
- 目的地址：接收方 IP 地址

### 以太网帧协议

![image-20211116222906658](04Linux网络编程/image-20211116222906658.png)

- 类型
  - 0x800表示 IP
  - 0x806表示 ARP
  - 0x835表示 RARP

### ARP协议

![image-20211116222942537](04Linux网络编程/image-20211116222942537.png)

- 硬件类型：1 表示 MAC 地址
- 协议类型：0x800 表示 IP 地址
- 硬件地址长度：6
- 协议地址长度：4 
- 操作
  - 1 表示 ARP 请求
  - 2 表示 ARP 应答
  - 3 表示 RARP 请求
  - 4 表示 RARP 应答

## 网络通信流程

### 封装与分用

- **发送端**通过TCP/IP中每一层时需要将消息`封装`对应信息，然后**接收端**通过过TCP/IP中每一层时需要将消息`分用（解封装）`对应信息

  ![image-20211117123435389](04Linux网络编程/image-20211117123435389.png)

- 封装

  > 上层协议是如何使用下层协议提供的服务的呢？其实这是通过封装（encapsulation）实现的。应用程序数据在发送到物理网络上之前，将沿着协议栈从上往下依次传递。每层协议都将在上层数据的基础上加上自己的头部信息（有时还包括尾部信息），以实现该层的功能，这个过程就称为封装

  ![image-20211117123350798](04Linux网络编程/image-20211117123350798.png)

- 分用

  > 当帧到达目的主机时，将沿着协议栈自底向上依次传递。各层协议依次处理帧中本层负责的头部数据，以获取所需的信息，并最终将处理后的帧交给目标应用程序。这个过程称为分用（demultiplexing）。分用是依靠头部信息中的类型字段实现的

  ![image-20211117123420044](04Linux网络编程/image-20211117123420044.png)

### 实例：QQ发送消息简易流程

- 存在的问题：在数据链路层封装以太网帧时，怎么知道目标机器的MAC地址？=>通过`arp协议`

![image-20211117123812988](04Linux网络编程/image-20211117123812988.png)

### ARP协议

- arp协议通过IP地址找到MAC地址，通过**广播arp请求找到**，局域网内根据信息解析得到`arp应答`
- rarp协议通过MAC地址找IP地址

![image-20211117125629434](04Linux网络编程/image-20211117125629434.png)

# socket通信

## 说明

本部分笔记及源码出自`slide/04Linux网络编程/02 socket通信`

## socket介绍

- `socket（套接字）`，就是对网络中**不同主机**上的应用进程之间进行**双向通信**的端点的抽象

  > 一个套接字就是网络上进程通信的一端，提供了应用层进程利用网络协议交换数据的机制。从所处的地位来讲，套接字上联应用进程，下联网络协议栈，是应用程序通过网络协议进行通信的接口，是应用程序与网络协议根进行交互的接口

- socket 可以看成是两个网络应用程序进行通信时，各自通信连接中的端点，这是一个逻辑上的概念

  > 它是网络环境中进程间通信的 API，也是可以被命名和寻址的通信端点，使用中的每一个套接字都有其类型和一个与之相连进程。通信时其中一个网络应用程序将要传输的一段信息写入它所在主机的 socket 中，该 socket 通过与网络接口卡（NIC）相连的传输介质将这段信息送到另外一台主机的 socket 中，使对方能够接收到这段信息。socket 是由 IP 地址和端口结合的，提供向应用层进程传送数据包的机制

- socket 本身有“插座”的意思，在 Linux 环境下，用于表示进程间网络通信的特殊文件类型。**本质为内核借助缓冲区形成的伪文件**

  > 既然是文件，那么理所当然的，我们可以使用文件描述符引用套接字。与管道类似的，Linux 系统将其封装成文件的目的是为了统一接口，使得读写套接字和读写文件的操作一致。区别是管道主要应用于本地进程间通信，而套接字多应用于网络进程间数据的传递

- 套接字通信分两部分
  - 服务器端：被动接受连接，一般不会主动发起连接 
  - 客户端：主动向服务器发起连接
- socket是一套通信的接口，Linux 和 Windows 都有，但是有一些细微的差别

![image-20211117194644130](04Linux网络编程/image-20211117194644130.png)

## 字节序

### 简介

- `字节序`，顾名思义字节的顺序，就是**大于一个字节类型的数据在内存中的存放顺序**(一个字节的数据当然就无需谈顺序的问题了)
- 字节序分为`大端字节序（Big-Endian）` 和`小端字节序（Little-Endian）`
  - **大端字节序**：指一个整数的最高位字节（23 ~ 31 bit）存储在内存的低地址处，低位字节（0 ~ 7 bit）存储在内存的高地址处
  - **小端字节序**：指整数的高位字节存储在内存的高地址处，而低位字节则存储在内存的低地址处

> 现代 CPU 的累加器一次都能装载（至少）4 字节（这里考虑 32 位机），即一个整数。那么这 4字节在内存中排列的顺序将影响它被累加器装载成的整数的值，这就是字节序问题
>
> 在各种计算机体系结构中，对于字节、字等的存储机制有所不同，因而引发了计算机通信领域中一个很重要的问题，即通信双方交流的信息单元（比特、字节、字、双字等等）应该以什么样的顺序进行传送。如果不达成一致的规则，通信双方将无法进行正确的编码/译码从而导致通信失败

### 字节序举例

- 大端字节序

  ![image-20211117200601434](04Linux网络编程/image-20211117200601434.png)

- 小端字节序

  ![image-20211117200550220](04Linux网络编程/image-20211117200550220.png)

### 查看机器字节序

```c
#include <stdio.h>

int main()
{
    union{
        short value;                // 两字节
        char bytes[sizeof(short)];  // 两字节
    }test;
    
    test.value = 0x0102;
    if (test.bytes[0] == 1 && test.bytes[1] == 2) {
        printf("大端机器\n");
    } else if (test.bytes[0] == 2 && test.bytes[1] == 1) {
        printf("小端机器\n");
    } else {
        printf("未知\n");
    }

    return 0;
}
```

![image-20211117201645270](04Linux网络编程/image-20211117201645270.png)

### 字节序转换函数

- 当格式化的数据在两台使用不同字节序的主机之间直接传递时，接收端必然错误的解释之。解决问题的方法是：**发送端总是把要发送的数据转换成大端字节序数据后再发送**，而接收端知道对方传送过来的数据总是采用大端字节序，所以接收端可以根据自身采用的字节序决定是否对接收到的数据进行转换（小端机转换，大端机不转换）

- **网络字节顺序**是 TCP/IP 中规定好的一种数据表示格式，它与具体的 CPU 类型、操作系统等无关，从而可以保证数据在不同主机之间传输时能够被正确解释，网络字节顺序采用大端排序方式

- BSD Socket提供了封装好的转换接口，方便程序员使用

  - 从主机字节序到网络字节序的转换函数：`htons`、`htonl`
  - 从网络字节序到主机字节序的转换函数：`ntohs`、`ntohl`

  ```c
  h  - host 主机，主机字节序 
  to - 转换成什么 
  n  - network 网络字节序 
  s  - short unsigned short 
  l  - long unsigned int
      
  #include <arpa/inet.h> 
  // 转换端口 
  uint16_t htons(uint16_t hostshort); // 主机字节序 => 网络字节序 
  uint16_t ntohs(uint16_t netshort); // 主机字节序 => 网络字节序 
  // 转IP 
  uint32_t htonl(uint32_t hostlong); // 主机字节序 => 网络字节序 
  uint32_t ntohl(uint32_t netlong); // 主机字节序 => 网络字节序
  ```

- 实例：模拟主机与网络IP及端口转换（本机为小端机器）

  ```c
  #include <stdio.h>
  #include <arpa/inet.h>
  
  int main()
  {
      // 主机字节序转网络字节序
      // IP转换
      char ip1[4] = {192, 168, 1, 1};
      int num1 = *(int*)ip1;
      int convet1 = htonl(num1);
      unsigned char *p1 = (char*)&convet1;
      for (int i = 0; i < 4; i++) {
          printf("%d ", *(p1 + i));
      }
      printf("\n");
  
      // 端口转换
      unsigned short port1 = 0x0102;
      unsigned short conv_port1 = htons(port1);
      printf("port1: %x\n", port1);
      printf("conv_port1: %x\n", conv_port1);
      printf("====================\n");
      // 网络字节序转主机字节序
      // IP转换
      char ip2[4] = {2, 1, 168, 192};
      int num2 = *(int*)ip2;
      int convet2 = ntohl(num2);
      unsigned char *p2 = (char*)&convet2;
      for (int i = 0; i < 4; i++) {
          printf("%d ", *(p2 + i));
      }
      printf("\n");
  
      // 端口转换
      unsigned short port2 = 0x0201;
      unsigned short conv_port2 = htons(port2);
      printf("port2: %x\n", port2);
      printf("conv_port2: %x\n", conv_port2);
      return 0;
  }
  ```

  ![image-20211117210302318](04Linux网络编程/image-20211117210302318.png)

## socket地址

### 简介

- socket地址其实是一个`结构体`，**封装端口号和IP等信息**
- 后面的socket相关的api中需要使用到这个 socket地址

### **通用** **socket** 地址

- socket 网络编程接口中表示 socket 地址的是结构体 `sockaddr`，其定义如下

  ```c
  #include <bits/socket.h> 
  struct sockaddr { 
      sa_family_t sa_family; 
      char sa_data[14]; 
  };
  
  typedef unsigned short int sa_family_t;
  ```

- `sa_family`

  - `sa_family` 成员是地址族类型（`sa_family_t`）的变量
  - `地址族类型`通常与`协议族类型`对应
  - 宏 `PF_*` 和 `AF_*` 都定义在 `bits/socket.h` 头文件中，且后者与前者有完全相同的值，所以二者通常混用

  |  协议族  |  地址族  |       描述       |
  | :------: | :------: | :--------------: |
  | PF_UNIX  | AF_UNIX  | UNIX本地域协议族 |
  | PF_INET  | AF_INET  |  TCP/IPv4协议族  |
  | PF_INET6 | AF_INET6 |  TCP/IPv6协议族  |

- `sa_data`

  - `sa_data` 成员用于存放 socket 地址值，不同的协议族的地址值具有不同的含义和长度

  |  协议族  |                       地址值含义和长度                       |
  | :------: | :----------------------------------------------------------: |
  | PF_UNIX  |               文件的路径名，长度可达到108字节                |
  | PF_INET  |         16 bit 端口号和 32 bit IPv4 地址，共 6 字节          |
  | PF_INET6 | 16 bit 端口号，32 bit 流标识，128 bit IPv6 地址，32 bit 范围 ID，共 26 字节 |

  - 由上表可知，14 字节的 sa_data 根本无法容纳多数协议族的地址值。因此，Linux 定义了下面这个新的通用的 socket 地址结构体，这个结构体不仅提供了足够大的空间用于存放地址值，而且是内存对齐的

    ```c
    #include <bits/socket.h> 
    struct sockaddr_storage { 
        sa_family_t sa_family; 
        unsigned long int __ss_align; 
        char __ss_padding[ 128 - sizeof(__ss_align) ]; 
    };
    
    typedef unsigned short int sa_family_t;
    ```

### 专用socket地址

#### 简介

- 很多网络编程函数诞生早于 IPv4 协议，那时候都使用的是 `struct sockaddr` 结构体，为了向前兼容，现在`sockaddr` 退化成了（void *）的作用，传递一个地址给函数，至于这个函数是 `sockaddr_in` 还是`sockaddr_in6`，由地址族确定，然后函数内部再强制类型转化为所需的地址类型

- 不同socket地址对比图

  ![image-20211117213426327](04Linux网络编程/image-20211117213426327.png)

- 所有专用 socket 地址（以及 sockaddr_storage）类型的变量在实际使用时都需要转化为通用 socket 地址类型 sockaddr（强制转化即可），因为所有 socket 编程接口使用的地址参数类型都是 sockaddr

#### UNIX 本地域协议族

```c
#include <sys/un.h> 
struct sockaddr_un { 
    sa_family_t sin_family; 
    char sun_path[108]; 
};
```

#### TCP/IP协议族

```c
// IPV4
#include <netinet/in.h> 
struct sockaddr_in { 
    sa_family_t sin_family; /* __SOCKADDR_COMMON(sin_) */ 
    in_port_t sin_port; /* Port number. */ 
    struct in_addr sin_addr; /* Internet address. */ 
    /* Pad to size of `struct sockaddr'. */ 
    unsigned char sin_zero[sizeof (struct sockaddr) - __SOCKADDR_COMMON_SIZE - sizeof (in_port_t) - sizeof (struct in_addr)]; 
};

struct in_addr { 
    in_addr_t s_addr; 
};

// IPV6
struct sockaddr_in6 { 
    sa_family_t sin6_family; 
    in_port_t sin6_port; /* Transport layer port # */ 
    uint32_t sin6_flowinfo; /* IPv6 flow information */ 
    struct in6_addr sin6_addr; /* IPv6 address */ 
    uint32_t sin6_scope_id; /* IPv6 scope-id */ 
};

// 相关定义
typedef unsigned short uint16_t; 
typedef unsigned int uint32_t; 
typedef uint16_t in_port_t; 
typedef uint32_t in_addr_t; 
#define __SOCKADDR_COMMON_SIZE (sizeof (unsigned short int))
```

## IP地址转换

- `点分十进制`IP地址与`网络字节序整数`IP地址相互转换

  > 通常，人们习惯用可读性好的字符串来表示 IP 地址，比如用点分十进制字符串表示 IPv4 地址，以及用十六进制字符串表示 IPv6 地址。但编程中我们需要先把它们转化为整数（二进制数）方能使用。而记录日志时则相反，我们要把整数表示的 IP 地址转化为可读的字符串

- 旧版（已弃用）：只适用于IPV4间的转换

  ```c
  #include <arpa/inet.h> 
  in_addr_t inet_addr(const char *cp); 
  int inet_aton(const char *cp, struct in_addr *inp); 
  char *inet_ntoa(struct in_addr in);
  ```

- 新版：同时适用于IPV4和IPV6

  - 字母含义
    - `p`：点分十进制的IP字符串
    - `n`：表示network，网络字节序的整数 
  - `int inet_pton(int af, const char *src, void *dst); `
    - 使用`man inet_pton`查看帮助
    - 功能：将点分十进制的IP地址字符串，转换成网络字节序的整数
    - 参数
      - `af`：地址族
        - IPV4：`AF_INET`
        - IPV6：`AF_INET6(IPV6)` 
      - `src`：需要转换的点分十进制的IP字符串 
      - `dst`：转换后的结果保存在这个里面 
    - 返回值
      - 1：成功
      - 0：源IP地址有误
      - -1：地址族包含不可用的地址协议
  - `const char *inet_ntop(int af, const void *src, char *dst, socklen_t size);`
    - 使用`man inet_ntop`查看帮助
    - 功能：将网络字节序的整数，转换成点分十进制的IP地址字符串
    - 参数
      - `af`：地址族
        - IPV4：`AF_INET`
        - IPV6：`AF_INET6(IPV6)` 
      - `src`：要转换的ip的整数的地址 
      - `dst`：转换成IP地址字符串保存的地方 
      - `size`：第三个参数的大小（数组的大小） 
    - 返回值：返回转换后的数据的地址（字符串），和 dst 是一样的 

  ```c
  #include <stdio.h>
  #include <arpa/inet.h>
  
  int main() {
  
      // 创建一个ip字符串,点分十进制的IP地址字符串
      char buf[] = "192.168.1.4";
      unsigned int num = 0;
  
      // 将点分十进制的IP字符串转换成网络字节序的整数
      inet_pton(AF_INET, buf, &num);
      unsigned char * p = (unsigned char *)&num;
      printf("%d %d %d %d\n", *p, *(p+1), *(p+2), *(p+3));
  
  
      // 将网络字节序的IP整数转换成点分十进制的IP字符串
      char ip[16] = "";
      const char * str =  inet_ntop(AF_INET, &num, ip, 16);
      printf("str : %s\n", str);
      printf("ip : %s\n", ip);
  
      return 0;
  }
  ```

  ![image-20211117221901175](04Linux网络编程/image-20211117221901175.png)

## TCP与UDP区别

### 简介

- `UDP`：用户数据报协议，面向无连接，可以单播，多播，广播， 面向数据报，不可靠 
- `TCP`：传输控制协议，面向连接的，可靠的，基于字节流，仅支持单播传输 

### 对比

|                |              UDP               |            TCP             |
| :------------: | :----------------------------: | :------------------------: |
|  是否创建连接  |             无连接             |          面向连接          |
|    是否可靠    |             不可靠             |           可靠的           |
| 连接的对象个数 | 一对一、一对多、多对一、多对多 |        仅支持一对一        |
|   传输的方式   |           面向数据报           |         面向字节流         |
|    首部开销    |            8个字节             |        最少20个字节        |
|    适用场景    |   实时应用（视频会议，直播）   | 可靠性高的应用（文件传输） |

## TCP通信流程

### 流程图

![image-20211121104748003](04Linux网络编程/image-20211121104748003.png)

### 服务器端（被动接收连接）

1. 创建一个用于监听的套接字
   - 监听：监听有客户端的连接
   - 套接字：这个套接字其实就是一个文件描述符 
2. 将这个`监听文件描述符`和**本地的IP和端口绑定**（IP和端口就是服务器的地址信息）
   - 客户端连接服务器的时候使用的就是这个IP和端口
3. 设置监听，`监听的fd`开始工作 
4. 阻塞等待，当有客户端发起连接，解除阻塞，接受客户端的连接，会得到一个`和客户端通信的套接字(fd)`
5. 通信
   - 接收数据
   - 发送数据
6. 通信结束，断开连接

### 客户端

1. 创建一个用于通信的套接字(fd)
2. 连接服务器，需要指定连接的服务器的 IP 和 端口 
3. 连接成功了，客户端可以直接和服务器通信 
   - 接收数据
   - 发送数据
4. 通信结束，断开连接

## 套接字函数

- 包含在下列头文件中

  ```c
  #include <sys/types.h> 
  #include <sys/socket.h> 
  #include <arpa/inet.h> // 包含了这个头文件，上面两个就可以省略(因为已经包含上面两个)
  ```

- 函数一览

  ```c
  int socket(int domain, int type, int protocol);
  int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
  int listen(int sockfd, int backlog);
  int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
  int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
  ```

- `int socket(int domain, int type, int protocol);`

  - 功能：创建一个套接字
  - 参数：
    - `domain`：协议族(常用如下)
      - `AF_INET` ：`ipv4`
      -  `AF_INET`6 ：`ipv6`
      - `AF_UNIX`, `AF_LOCAL`：本地套接字通信（进程间通信） 
    - `type`：通信过程中使用的协议类型 
      - `SOCK_STREAM` : 流式协议
      - `SOCK_DGRAM` : 报式协议 
    - `protocol`：具体的一个协议，一般写0，用于指定type参数的默认协议类型
      - `SOCK_STREAM` : 流式协议默认使用 TCP 
      - `SOCK_DGRAM` : 报式协议默认使用 UDP 
  - 返回值
    - 成功：返回文件描述符，操作的就是内核缓冲区
    - 失败：-1 

- `int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen); `

  - 功能：绑定，将fd 和本地的IP和端口进行绑定 
  - 参数：
    - `sockfd`：通过socket函数得到的文件描述符 
    - `addr`：需要绑定的socket地址，这个地址封装了**本地的ip和端口号的信息**
    - `addrlen`：第二个参数结构体占的内存大小 
  - 返回值：成功：0，失败：-1

- `int listen(int sockfd, int backlog);`

  - 功能：监听这个socket上的连接

  - 参数：

    - `sockfd`：通过socket()函数得到的文件描述符

    - `backlog`：未连接的和已经连接的和的最大值，可用`cat /proc/sys/net/core/somaxconn`查看Linux设置值，==一般指定5就可以（视频说的，是否正确待验证）==

      ![image-20211121111847282](04Linux网络编程/image-20211121111847282.png)

  - 返回值：成功：0，失败：-1

- `int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen); `

  - 功能：接收客户端连接，默认是一个阻塞的函数，阻塞等待客户端连接
  - 参数：
    - `sockfd` : 用于监听的文件描述符 
    - `addr` : 传出参数，记录了连接成功后**客户端的地址信息**（ip，port） 
    - `addrlen` : 指定第二个参数的对应的内存大小
  - 返回值：
    - 成功：用于通信的文件描述符 
    - 失败：-1

- `int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);`

  - 功能： 客户端连接服务器 
  - 参数：
    - `sockfd` : 用于**通信的文件描述符 **
    - `addr` : 客户端要连接的服务器的地址信息
    - `addrlen` : 指定第二个参数的对应的内存大小
  - 返回值：成功 0， 失败 -1 

- 其他读写函数：

  ```c
  ssize_t write(int fd, const void *buf, size_t count); // 写数据 
  ssize_t read(int fd, void *buf, size_t count); // 读数据
  ```

## 实例：TCP通信

### 服务器端

```c
#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define SERVERIP "127.0.0.1"
#define PORT 6789

int main()
{
    // 1. 创建socket（用于监听的套接字）
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd == -1) {
        perror("socket");
        exit(-1);
    }

    // 2. 绑定
    struct sockaddr_in server_addr;
    server_addr.sin_family = PF_INET;
    // 点分十进制转换为网络字节序
    inet_pton(AF_INET, SERVERIP, &server_addr.sin_addr.s_addr);
    // 服务端也可以绑定0.0.0.0即任意地址
    // server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);
    int ret = bind(listenfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if (ret == -1) {
        perror("bind");
        exit(-1);
    }

    // 3. 监听
    ret = listen(listenfd, 8);
        if (ret == -1) {
        perror("listen");
        exit(-1);
    }

    // 4. 接收客户端连接
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    int connfd = accept(listenfd, (struct sockaddr*)&client_addr, &client_addr_len);
    if (connfd == -1) {
        perror("accept");
        exit(-1);
    }
    // 输出客户端信息，IP组成至少16个字符（包含结束符）
    char client_ip[16] = {0};
    inet_ntop(AF_INET, &client_addr.sin_addr.s_addr, client_ip, sizeof(client_ip));
    unsigned short client_port = ntohs(client_addr.sin_port);
    printf("ip:%s, port:%d\n", client_ip, client_port);


    // 5. 开始通信
    // 服务端先接收客户端信息，再向客户端发送数据
    // 接收数据
    char recv_buf[1024] = {0};
    while (1) {
        ret = read(connfd, recv_buf, sizeof(recv_buf));
        if (ret == -1) {
            perror("read");
            exit(-1);
        } else if (ret > 0) {
            printf("recv client data : %s\n", recv_buf);
        } else {
            // 表示客户端断开连接
            printf("client closed...\n");
            break;
        }
        // 发送数据
        char *send_buf = "hello, i am server";
        // 粗心写成sizeof，那么就会导致遇到空格终止
        write(connfd, send_buf, strlen(send_buf));
    }

    // 关闭文件描述符
    close(connfd);
    close(listenfd);
    return 0;
}
```

### 客户端

```c
#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define SERVERIP "127.0.0.1"
#define PORT 6789

int main()
{
    // 1. 创建socket（用于通信的套接字）
    int connfd = socket(AF_INET, SOCK_STREAM, 0);
    if (connfd == -1) {
        perror("socket");
        exit(-1);
    }
    // 2. 连接服务器端
    struct sockaddr_in server_addr;
    server_addr.sin_family = PF_INET;
    inet_pton(AF_INET, SERVERIP, &server_addr.sin_addr.s_addr);
    server_addr.sin_port = htons(PORT);
    int ret = connect(connfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if (ret == -1) {
        perror("connect");
        exit(-1);
    }
    // 3. 通信
            char recv_buf[1024] = {0};
    while (1) {
        // 发送数据
        char *send_buf = "client message";
        // 粗心写成sizeof，那么就会导致遇到空格终止
        write(connfd, send_buf, strlen(send_buf));
        sleep(1);
        // 接收数据
        ret = read(connfd, recv_buf, sizeof(recv_buf));
        if (ret == -1) {
            perror("read");
            exit(-1);
        } else if (ret > 0) {
            printf("recv client data : %s\n", recv_buf);
        } else {
            // 表示服务端断开连接
            printf("server closed...\n");
            break;
        }
    }
    // 关闭连接
    close(connfd);
    return 0;
}
```

### 通信效果

![image-20211121133101783](04Linux网络编程/image-20211121133101783.png)

## TCP三次握手——建立连接

- 此节需要结合`网络基础->协议->TCP协议`一起看

### 简易图示

![image-20211121144550714](04Linux网络编程/image-20211121144550714.png)

### 握手流程

![image-20211121145128707](04Linux网络编程/image-20211121145128707.png)

#### 第一次握手

- 客户端将SYN标志位置为1 
- 生成一个随机的32位的序号seq=J ， 这个序号后边是可以携带数据（数据的大小）

#### 第二次握手

- 服务器端接收客户端的连接： ACK=1
- 服务器会回发一个确认序号： ack=客户端的序号 + 数据长度 + SYN/FIN(按一个字节算)
- 服务器端会向客户端发起连接请求： SYN=1 
- 服务器会生成一个随机序号：seq = K 

#### 第三次握手

- 客户端应答服务器的连接请求：ACK=1
- 客户端回复收到了服务器端的数据：ack=服务端的序号 + 数据长度 + SYN/FIN(按一个字节算)

### 示例：携带数据通信流程

- 括号内数字代表携带数据大小

![image-20211121151016137](04Linux网络编程/image-20211121151016137.png)

## TCP滑动窗口——流量控制

### 简介

- `滑动窗口`是 TCP 中实现诸如 ACK 确认、流量控制、拥塞控制的承载结构
- TCP 中采用滑动窗口来进行传输控制，滑动窗口的大小意味着**接收方还有多大的缓冲区可以用于接收数据**。**发送方可以通过滑动窗口的大小来确定应该发送多少字节的数据**。当滑动窗口为 0时，发送方一般不能再发送数据报

> 滑动窗口（Sliding window）是一种流量控制技术。早期的网络通信中，通信双方不会考虑网络的拥挤情况直接发送数据。由于大家不知道网络拥塞状况，同时发送数据，导致中间节点阻塞掉包，谁也发不了数据，所以就有了滑动窗口机制来解决此问题
>
> 滑动窗口协议是用来改善吞吐量的一种技术，即容许发送方在接收任何应答之前传送附加的包。接收方告诉发送方在某一时刻能送多少包（称窗口尺寸）

### 滑动窗口与缓冲区

- **滑动窗口可以理解为缓冲区的大小**

- 滑动窗口的大小会随着发送数据和接收数据而变化，通信的双方都有发送缓冲区和接收数据的缓冲区

- 图示说明：单向发送数据（发送端->接收端）

  ![image-20211121153104245](04Linux网络编程/image-20211121153104245.png)

  - 发送方的缓冲区
    - 白色格子：空闲的空间
    - 灰色格子：数据已经被发送出去了，但是还没有被接收
    - 紫色格子：还没有发送出去的数据 
  - 接收方的缓冲区
    - 白色格子：空闲的空间 
    - 紫色格子：已经接收到的数据

## TCP四次挥手——断开连接

### 简易图示

![image-20211121154555977](04Linux网络编程/image-20211121154555977.png)

### 挥手流程

- 四次挥手发生在断开连接的时候，在程序中当调用了`close()`会使用TCP协议进行四次挥手
- 客户端和服务器端都可以主动发起断开连接，谁先调用`close()`谁就是发起方
- 因为在TCP连接的时候，采用三次握手建立的的连接是双向的，在断开的时候需要双向断开

![image-20211121154857445](04Linux网络编程/image-20211121154857445.png)

## 实例：完整的TCP通信

![image-20211121155042845](04Linux网络编程/image-20211121155042845.png)

### 注解

- 图中`MSS`表示Maximum Segment Size(一条数据的最大的数据量) 

- `win`表示滑动窗口大小

- 图中部分`ACK`应为确认号`ack`，而非标志位`ACK`

### 流程说明

1. 第1次，**第一次握手**，客户端向服务器发起连接，客户端的滑动窗口大小是4096，一次发送的最大数据量是1460 

2. 第2次，**第二次握手**，服务器接收连接情况，告诉客户端服务器的窗口大小是6144，一次发送的最大数据量是1024 

3. 第3次，**第三次握手**

4. 第4-9次，客户端连续给服务器发送了6k的数据，每次发送1k 

5. 第10次，服务器告诉客户端：发送的6k数据以及接收到，存储在缓冲区中，缓冲区数据已经处理了2k，窗口大小是2k(还剩4k未处理，后面同理，不再做单独说明)

6. 第11次，服务器告诉客户端：发送的6k数据以及接收到，存储在缓冲区中，缓冲区数据已经处理了4k，窗口大小是4k 

7. 第12次，客户端给服务器发送了1k的数据 

8. 第13次，**第一次挥手**，客户端主动请求和服务器断开连接，并且给服务器发送了1k的数据 

9. 第14-16次，**第二次挥手**，服务器回复ACK 8194(包含FIN标记，所以结果上多加了1)，表示**同意断开连接的请求**，并通知客户端依次已经处理了2k，4k，6k数据，滑动窗口大小依次为2k，4k，6k
10. 第17次，**第三次挥手**，服务器端给客户端发送FIN，请求断开连接 
11. 第18次，**第四次回收**，客户端同意了服务器端的断开请求

## TCP通信并发

### 注解

- 要实现TCP通信服务器处理并发的任务，使用多进程或者多线程来解决

### 实例：多进程实现TCP并发通信

#### 思路

- 服务端使用一个父进程，多个子进程 

  - 父进程负责等待并接受客户端的连接 

  - 子进程：完成通信，接受一个客户端连接，就创建一个子进程用于通信

- 客户端不需要改变（同一对一通信）

#### 遇到问题及解决

- 断开连接后，服务器端如何处理子进程，回收资源？
  - 使用信号处理
- 使用信号捕捉回收子进程资源后，出现服务端`accept: Interrupted system call`，且不能有新客户端连接，如何解决？
  - 产生`EINTR`信号，具体说明通过`man 2 accept`查看
  - 在`accept`返回值处进行判断处理，不输出错误即可
- 当停止所有的客户端连接后，出现`read: Connection reset by peer`，如何解决？
  - 产生的原因：连接断开后的读和写操作引起的
  - 简单修改：将客户端中休眠语句的位置进行更改
  - 方法：[[261]Connection reset by peer的常见原因及解决办法](https://blog.csdn.net/xc_zhou/article/details/80950753)
- 解决上一个问题后，服务端出现两次`client closed...`，如何解决？
  - 是因为在关闭连接后，应该退出循环，所以在该`printf`语句后，添加`break`即可

#### 服务端

```c
#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>

#define SERVERIP "127.0.0.1"
#define PORT 6789

void recycleChild(int arg) {
    // 写while是为了处理多个信号
    while (1) {
        int ret = waitpid(-1, NULL, WNOHANG);
        if (ret == -1) {
            // 所有子进程都回收了
            break;
        } else if (ret == 0) {
            // 还有子进程活着
            break;
        } else {
            // 回收子进程
            printf("子进程 %d 被回收了\n", ret);
        }
    }
}

int main()
{
    // 注册信号捕捉
    struct sigaction act;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    act.sa_handler = recycleChild;
    sigaction(SIGCHLD, &act, NULL);

    // 1. 创建socket（用于监听的套接字）
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd == -1) {
        perror("socket");
        exit(-1);
    }

    // 2. 绑定
    struct sockaddr_in server_addr;
    server_addr.sin_family = PF_INET;
    // 点分十进制转换为网络字节序
    inet_pton(AF_INET, SERVERIP, &server_addr.sin_addr.s_addr);
    // 服务端也可以绑定0.0.0.0即任意地址
    // server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);
    int ret = bind(listenfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if (ret == -1) {
        perror("bind");
        exit(-1);
    }

    // 3. 监听
    ret = listen(listenfd, 8);
        if (ret == -1) {
        perror("listen");
        exit(-1);
    }
    // 不断循环等待客户端连接
    while (1) {
        // 4. 接收客户端连接
        struct sockaddr_in client_addr;
        socklen_t client_addr_len = sizeof(client_addr);
        int connfd = accept(listenfd, (struct sockaddr*)&client_addr, &client_addr_len);
        if (connfd == -1) {
            // 用于处理信号捕捉导致的accept: Interrupted system call
            if (errno == EINTR) {
                continue;
            }
            perror("accept");
            exit(-1);
        }
        pid_t pid = fork();
        if (pid == 0) {
            // 子进程
            // 输出客户端信息，IP组成至少16个字符（包含结束符）
            char client_ip[16] = {0};
            inet_ntop(AF_INET, &client_addr.sin_addr.s_addr, client_ip, sizeof(client_ip));
            unsigned short client_port = ntohs(client_addr.sin_port);
            printf("ip:%s, port:%d\n", client_ip, client_port);

            // 5. 开始通信
            // 服务端先接收客户端信息，再向客户端发送数据
            // 接收数据
            char recv_buf[1024] = {0};
            while (1) {
                ret = read(connfd, recv_buf, sizeof(recv_buf));
                if (ret == -1) {
                    perror("read");
                    exit(-1);
                } else if (ret > 0) {
                    printf("recv client data : %s\n", recv_buf);
                } else {
                    // 表示客户端断开连接
                    printf("client closed...\n");
                    // 退出循环，用来解决出现两次client closed...
                    break;
                }
                // 发送数据
                char *send_buf = "hello, i am server";
                // 粗心写成sizeof，那么就会导致遇到空格终止
                write(connfd, send_buf, strlen(send_buf));
            }
            // 关闭文件描述符
            close(connfd);
        }
    }

    close(listenfd);
    return 0;
}
```

#### 客户端

```c
#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define SERVERIP "127.0.0.1"
#define PORT 6789

int main()
{
    // 1. 创建socket（用于通信的套接字）
    int connfd = socket(AF_INET, SOCK_STREAM, 0);
    if (connfd == -1) {
        perror("socket");
        exit(-1);
    }
    // 2. 连接服务器端
    struct sockaddr_in server_addr;
    server_addr.sin_family = PF_INET;
    inet_pton(AF_INET, SERVERIP, &server_addr.sin_addr.s_addr);
    server_addr.sin_port = htons(PORT);
    int ret = connect(connfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if (ret == -1) {
        perror("connect");
        exit(-1);
    }
    // 3. 通信
            char recv_buf[1024] = {0};
    while (1) {
        // 发送数据
        char *send_buf = "client message";
        // 粗心写成sizeof，那么就会导致遇到空格终止
        write(connfd, send_buf, strlen(send_buf));
        // 休眠的目的是为了更好的观察，此处使用sleep语句会导致read: Connection reset by peer
        // sleep(1);
        // 接收数据
        ret = read(connfd, recv_buf, sizeof(recv_buf));
        if (ret == -1) {
            perror("read");
            exit(-1);
        } else if (ret > 0) {
            printf("recv server data : %s\n", recv_buf);
        } else {
            // 表示客户端断开连接
            printf("client closed...\n");
        }
        // 休眠的目的是为了更好的观察，放在此处可以解决read: Connection reset by peer问题
        sleep(1);
    }
    // 关闭连接
    close(connfd);
    return 0;
}
```

#### 通信效果

![image-20211121162229827](04Linux网络编程/image-20211121162229827.png)

### 实例：多线程实现TCP并发通信

#### 思路

- 服务端使用一个主线程，多个子线程 

  - 主线程负责等待并接受客户端的连接 

  - 子线程：完成通信，接受一个客户端连接，就创建一个子进程用于通信

- 客户端不需要改变（同一对一通信）

#### 服务端

```c
#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#define SERVERIP "127.0.0.1"
#define PORT 6789

struct sockInfo{
    int fd;                             // 通信文件描述符
    pthread_t tid;                      // 线程号
    struct sockaddr_in addr;            // 客户端信息
};

struct sockInfo sockinfos[128];     // 表示最大有128个客户端连接

void* working(void *arg) {
    // 子线程与客户端通信
    struct sockInfo *pinfo = (struct sockInfo*)arg;

    // 输出客户端信息，IP组成至少16个字符（包含结束符）
    char client_ip[16] = {0};
    inet_ntop(AF_INET, &pinfo->addr.sin_addr.s_addr, client_ip, sizeof(client_ip));
    unsigned short client_port = ntohs(pinfo->addr.sin_port);
    printf("ip:%s, port:%d\n", client_ip, client_port);

    // 5. 开始通信
    // 服务端先接收客户端信息，再向客户端发送数据
    // 接收数据
    char recv_buf[1024] = {0};
    while (1) {
        int ret = read(pinfo->fd, recv_buf, sizeof(recv_buf));
        if (ret == -1) {
            perror("read");
            exit(-1);
        } else if (ret > 0) {
            printf("recv client data : %s\n", recv_buf);
        } else {
            // 表示客户端断开连接
            printf("client closed...\n");
            break;
        }
        // 发送数据
        char *send_buf = "hello, i am server";
        // 粗心写成sizeof，那么就会导致遇到空格终止
        write(pinfo->fd, send_buf, strlen(send_buf));
    }
    // 关闭文件描述符
    close(pinfo->fd);
}

int main()
{
    // 初始化线程结构体数据
    int sockinfo_maxLen = sizeof(sockinfos) / sizeof(sockinfos[0]);
    for (int i = 0; i < sockinfo_maxLen; i++) {
        bzero(&sockinfos[i], sizeof(sockinfos[i]));
        sockinfos[i].fd = -1;
        sockinfos[i].tid = -1;
    }

    // 1. 创建socket（用于监听的套接字）
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd == -1) {
        perror("socket");
        exit(-1);
    }

    // 2. 绑定
    struct sockaddr_in server_addr;
    server_addr.sin_family = PF_INET;
    // 点分十进制转换为网络字节序
    inet_pton(AF_INET, SERVERIP, &server_addr.sin_addr.s_addr);
    // 服务端也可以绑定0.0.0.0即任意地址
    // server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);
    int ret = bind(listenfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if (ret == -1) {
        perror("bind");
        exit(-1);
    }

    // 3. 监听
    ret = listen(listenfd, 8);
        if (ret == -1) {
        perror("listen");
        exit(-1);
    }
    // 不断循环等待客户端连接
    while (1) {
        // 4. 接收客户端连接
        struct sockaddr_in client_addr;
        socklen_t client_addr_len = sizeof(client_addr);
        int connfd = accept(listenfd, (struct sockaddr*)&client_addr, &client_addr_len);
        if (connfd == -1) {
            perror("accept");
            exit(-1);
        }
        // 创建子线程
        struct sockInfo *pinfo;
        // 从线程数组中找到一个可用的元素进行赋值
        for (int i = 0; i < sockinfo_maxLen; i++) {
            if (sockinfos[i].tid == -1) {
                pinfo = &sockinfos[i];
                break;
            }
            // 当遍历到最后还没有找到，那么休眠一秒后，从头开始找
            if (i == sockinfo_maxLen - 1) {
                sleep(1);
                i = -1;
            }
        }
        // 结构体赋值
        pinfo->fd = connfd;
        memcpy(&pinfo->addr, &client_addr, client_addr_len);
        pthread_create(&pinfo->tid, NULL, working, pinfo);
        // 释放资源
        pthread_detach(pinfo->tid);
    }

    close(listenfd);
    return 0;
}
```

#### 客户端

```c
#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define SERVERIP "127.0.0.1"
#define PORT 6789

int main()
{
    // 1. 创建socket（用于通信的套接字）
    int connfd = socket(AF_INET, SOCK_STREAM, 0);
    if (connfd == -1) {
        perror("socket");
        exit(-1);
    }
    // 2. 连接服务器端
    struct sockaddr_in server_addr;
    server_addr.sin_family = PF_INET;
    inet_pton(AF_INET, SERVERIP, &server_addr.sin_addr.s_addr);
    server_addr.sin_port = htons(PORT);
    int ret = connect(connfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if (ret == -1) {
        perror("connect");
        exit(-1);
    }
    // 3. 通信
            char recv_buf[1024] = {0};
    while (1) {
        // 发送数据
        char *send_buf = "client message";
        // 粗心写成sizeof，那么就会导致遇到空格终止
        write(connfd, send_buf, strlen(send_buf));
        // 休眠的目的是为了更好的观察，此处使用sleep语句会导致read: Connection reset by peer
        // sleep(1);
        // 接收数据
        ret = read(connfd, recv_buf, sizeof(recv_buf));
        if (ret == -1) {
            perror("read");
            exit(-1);
        } else if (ret > 0) {
            printf("recv server data : %s\n", recv_buf);
        } else {
            // 表示客户端断开连接
            printf("client closed...\n");
        }
        // 休眠的目的是为了更好的观察，放在此处可以解决read: Connection reset by peer问题
        sleep(1);
    }
    // 关闭连接
    close(connfd);
    return 0;
}
```

#### 通信效果

![image-20211121172701543](04Linux网络编程/image-20211121172701543.png)

## TCP状态转换

### 通信过程状态转换图1

![image-20211123124438914](04Linux网络编程/image-20211123124438914.png)

### 通信过程状态转换图2

- 红色实线代表客户端（主动发起连接）
- 绿色虚线代表服务端（被动接收连接）
- 黑色实现代表特殊情况
- 数字代表三次握手流程

![image-20211123124611335](04Linux网络编程/image-20211123124611335.png)

### MSL与半关闭

- 主动断开连接的一方，最后会进入一个 `TIME_WAIT`状态，这个状态会持续`2msl`

- `msl`：官方建议2分钟，实际是30s，**主要是为了防止挥手信息丢失**

  > 当 TCP 连接主动关闭方接收到被动关闭方发送的 FIN 和最终的 ACK 后，连接的主动关闭方必须处于TIME_WAIT 状态并持续 2MSL 时间
  >
  > 这样就能够让 TCP 连接的主动关闭方在它发送的 ACK 丢失的情况下重新发送最终的 ACK
  >
  > 主动关闭方重新发送的最终 ACK 并不是因为被动关闭方重传了 ACK（它们并不消耗序列号，被动关闭方也不会重传），而是因为被动关闭方重传了它的 FIN。事实上，被动关闭方总是重传 FIN 直到它收到一个最终的 ACK

- `半关闭`：当 TCP 连接中 A 向 B 发送 FIN 请求关闭，另一端 B 回应 ACK 之后（A 端进入 FIN_WAIT_2状态），并没有立即发送 FIN 给 A，A 方处于半连接状态（半开关），此时 **A 可以接收 B 发送的数据，但是 A 已经不能再向 B 发送数据**
- API 来控制实现半连接状态的方法：` shutdown函数`
  - `int shutdown(int sockfd, int how); `
    - 功能：实现半连接状态
    - 参数
      - `sockfd`：需要关闭的socket的描述符 
      - `how`：允许为shutdown操作选择以下几种方式
        - `SHUT_RD(0)`：关闭sockfd上的读功能，此选项将不允许sockfd进行读操作，该套接字不再接收数据，任何当前在套接字接受缓冲区的数据将被无声的丢弃掉
        - `SHUT_WR(1)`：关闭sockfd的写功能，此选项将不允许sockfd进行写操作。进程不能在对此套接字发 出写操作
        - `SHUT_RDWR(2)`：关闭sockfd的读写功能。相当于调用shutdown两次：首先调用`SHUT_RD`,然后调用 `SHUT_WR`

### shutdown与close

- 使用 `close` 中止一个连接，但它只是**减少描述符的引用计数，并不直接关闭连接**，只有当描述符的引用计数为 0 时才关闭连接
- `shutdown` 不考虑描述符的引用计数，**直接关闭描述符**。也可选择中止一个方向的连接，只中止读或只中止写
- 如果有多个进程共享一个套接字，close 每被调用一次，计数减 1 ，直到计数为 0 时，也就是所用进程都调用了 close，套接字将被释放
- **在多进程中如果一个进程调用了 `shutdown(sfd, SHUT_RDWR)` 后，其它的进程将无法进行通信**。但如果一个进程 `close(sfd)` 将不会影响到其它进程=>==难怪800那个项目调shutdown之后其他线程就不能用了==

### 端口复用

#### 用途

- 防止服务器重启时之前绑定的端口还未释放
- 程序突然退出而系统没有释放端口

#### 方法——`setsockopt`

- `int setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen); `
  - 功能：设置套接字的属性（不仅仅能设置端口复用），以下说明仅针对端口复用，其他详细内容可查看`slide/04Linux网络编程/02 socket通信/UNP（Unix网络编程）.pdf`第七章相关内容 
  - 参数
    - `sockfd`：要操作的文件描述符 
    - `level`：级别，`SOL_SOCKET` (端口复用的级别)
    - `optname`：选项的名称，使用`SO_REUSEADDR`或`SO_REUSEPORT`
    - `optval`：端口复用的值（整形） ，1表示可复用，0表示不可复用
    - `optlen`：optval参数的大小

#### 注意

- 端口复用的设置时机是**在服务器绑定端口之前**
- 如果不设置端口复用，那么在程序异常终止后，再次启动服务会出现`Bind error:Address already in use`

### 查看看网络相关信息命令——netstat

- 格式：`netstat -参数名`
- 常用参数
  - `a`：所有的socket
  - `p`：显示正在使用socket的程序的名称
  - `n`：直接使用IP地址，而不通过域名服务器

# IO多路复用(IO多路转接)

## 说明

本部分笔记及源码出自`slide/04Linux网络编程/03 IO多路复用`

## 阻塞等待(BIO模型)

### 简介

- 遇到`read`/`recv`/`accept`时，阻塞等待，直接有数据或者连接时才继续往下执行

### 单任务

- 好处：不占用CPU宝贵的时间片
- 缺点：同一时刻只能处理一个操作, 效率低
- 克服缺点：多线程或者多进程解决，一个线程/进程对应一个任务

![image-20211124122737594](04Linux网络编程/image-20211124122737594.png)

### 多任务

- 优点：能够同时处理多个任务，一个线程/进程对应一个任务
- 缺点：
  - 线程或者进程会消耗资源
  - 线程或进程调度消耗CPU资源
- 根本问题：阻塞(`blocking`)

![image-20211124122820504](04Linux网络编程/image-20211124122820504.png)

## 非阻塞，忙轮询(NIO模型)

- 优点：提高了程序的执行效率
- 缺点：需要占用更多的CPU和系统资源，每循环都需要 O(n) 系统调用（用来查找哪个任务可执行）
- 克服缺点：使用IO多路转接技术select/poll/epoll

![image-20211124123055701](04Linux网络编程/image-20211124123055701.png)

## IO多路转接技术(简介)

### select/poll

- 委托内核进行操作
- 只会通知有几个任务可用，但不知道具体哪几个任务，还需遍历（与NIO模型略有不同）

![image-20211124125216066](04Linux网络编程/image-20211124125216066.png)

### epoll

- 委托内核进行操作
- 会通知具体有哪几个任务可用

![image-20211124125254136](04Linux网络编程/image-20211124125254136.png)
