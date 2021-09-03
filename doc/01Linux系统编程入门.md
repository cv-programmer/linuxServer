# 准备工作

## 系统配置

1. 在虚拟机中安装Linux系统，本项目采用`VMware Workstation 16.1.2`和`Ubuntu 18.04`，本机系统为`Win 10`

2. 更新`Ubuntu 18.10`源并安装`open-vm-tools`

   1. 进入`/etc/apt/sources.list` 修改为国内镜像源（速度快），全部删除，替换为下述内容

      ```shell
      # 默认注释了源码镜像以提高 apt update 速度，如有需要可自行取消注释
      deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ bionic main restricted universe multiverse
      # deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ bionic main restricted universe multiverse
      deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ bionic-updates main restricted universe multiverse
      # deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ bionic-updates main restricted universe multiverse
      deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ bionic-backports main restricted universe multiverse
      # deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ bionic-backports main restricted universe multiverse
      deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ bionic-security main restricted universe multiverse
      # deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ bionic-security main restricted universe multiverse
      
      # 预发布软件源，不建议启用
      # deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ bionic-proposed main restricted universe multiverse
      # deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ bionic-proposed main restricted universe multiverse
      ```

   2. 更新系统源：

      ```shell
      # update 是同步 /etc/apt/sources.list 和 /etc/apt/sources.list.d 中列出的源的索引，这样才能获取到最新的软件包
      sudo apt update
      # upgrade 是升级已安装的所有软件包(可选)
      # sudo apt upgrade
      ```

   3. 安装`open-vm-tools`：`sudo apt install open-vm-tools`

   4. ~~如果要实现文件夹共享，需要安装`open-vm-tools-dkms`：`sudo apt install open-vm-tools-dkms`~~=>清华源找不到`open-vm-tools-dkms`，不安装不影响

   5. 桌面环境还需要安装`open-vm-tools-desktop`以支持双向拖放文件：`sudo apt install open-vm-tools-desktop`

   6. 重启（使用VMware自带重启，使用`reboot`重启可能失败）后成功进行拖拽复制

   注：[参考链接](https://blog.csdn.net/hhdhz/article/details/87922794)

3. 在`Ubuntu 18.10`安装必要组件

   ```shell
   # 安装Vim环境
   sudo apt install vim
   
   # 用于远程连接虚拟机
   sudo apt install openssh-server
   
   # 用于查看IP地址
   sudo apt install net-tools
   
   # 树形查看文件夹内容
   sudo apt install tree
   ```

## VS code

1. 安装`Remote Development`插件

2. 在Linux中使用`ifconfig`查看`ip地址`

3. 按下图步骤设置`config`文件

   ![image-20210831142010206](01Linux系统编程入门/image-20210831142010206.png)

4. `config`内容如下

   ```shell
   # Read more about SSH config files: https://linux.die.net/man/5/ssh_config
   Host 自定义名称
       HostName 远程服务器IP
       User 远程服务器用户名
   ```

## GCC

### 安装`gcc`

命令：`sudo apt install gcc g++`，本项目安装版本为：`7.5.0`

### gcc工作流程

![image-20210831132508825](01Linux系统编程入门/image-20210831132508825.png)

### gcc常用参数选项

![image-20210831132654506](01Linux系统编程入门/image-20210831132654506.png)

![image-20210831135954037](01Linux系统编程入门/image-20210831135954037.png)

- -D实例

  - 源程序

    ```c
    #include<stdio.h>
    
    int main()
    {
    #if DEBUG
        printf("Debug\n");
    #endif
        printf("hello, world\n");
        return 0;
    }
    ```

  - 编译命令1：

    ```shell
    gcc test.c -o test
    ./test
    
    # 输出
    hello, world
    ```

  - 编译命令2：

    ```shell
    gcc test.c -o test -D DEBUG
    ./test
    
    # 输出
    Debug
    hello, world
    ```

### gcc与g++区别

- `gcc` 和 `g++` 都是`GNU(组织)`的一个编译器
- **误区一：`gcc` 只能编译 c 代码，g++ 只能编译 c++ 代码**
  - 后缀为` .c` 的，`gcc` 把它当作是 C 程序，而 `g++` 当作是 `c++` 程序
  - 后缀为 `.cpp` 的，两者都会认为是 `C++` 程序，`C++` 的语法规则更加严谨一些
  - 编译阶段，`g++` 会调用 `gcc`，对于 `C++` 代码，两者是等价的，但是因为 `gcc` 命令不能自动和 `C++` 程序使用的库联接，所以通常用 `g++` 来完成链接，为了统一起见，干脆编译/链接统统用 `g++` 了，这就给人一种错觉，好像 `cpp` 程序只能用 `g++` 似的
- **误区二：`gcc` 不会定义 `__cplusplus` 宏，而 `g++` 会 **
  - 实际上，这个宏只是标志着编译器将会把代码按 C 还是 C++ 语法来解释
  - 如上所述，如果后缀为 .c，并且采用 `gcc` 编译器，则该宏就是未定义的，否则，就是已定义
- **误区三：编译只能用 gcc，链接只能用 g++**
  - 严格来说，这句话不算错误，但是它混淆了概念，应该这样说：编译可以用 `gcc/g++`，而链接可以用 `g++` 或者 `gcc -lstdc++`
  - `gcc` 命令不能自动和C++程序使用的库联接，所以通常使用 `g++` 来完成链接。但在编译阶段，`g++` 会自动调用 `gcc`，二者等价

# Linux系统编程基础知识

## 静态库与动态库

### 库

- 库文件是计算机上的一类文件，可以简单的把库文件看成一种代码仓库，它提供给使用者一些**可以直接拿来用的变量、函数或类**
- 库是特殊的一种程序，编写库的程序和编写一般的程序区别不大，只是**库不能单独运行**
- 库文件有两种，`静态库`和`动态库（共享库）`。区别是：
  - **静态库**在程序的链接阶段被复制到了程序中
  - **动态库**在链接阶段没有被复制到程序中，而是程序在运行时由系统动态加载到内存中供程序调用
- 库的好处：**代码保密** 和**方便部署和分发**

### 静态库的制作

- 规则

![image-20210831163546031](01Linux系统编程入门/image-20210831163546031.png)

- 示例：有如下图所示文件(其中每个分文件用于实现四则运算)，将其打包为**静态库**

  ![image-20210831164707648](01Linux系统编程入门/image-20210831164707648.png)

  1. 生成`.o`文件：`gcc -c 文件名`

     ![image-20210831164903714](01Linux系统编程入门/image-20210831164903714.png)

  2. 将`.o`文件打包：`ar rcs libxxx.a xx1.o xx2.o`

     ![image-20210831165142693](01Linux系统编程入门/image-20210831165142693.png)

### 静态库的使用

- 需要提供**静态库文件和相应的头文件**，有如下结构文件，其中`main.c`测试文件

  ![image-20210831170033041](01Linux系统编程入门/image-20210831170033041.png)

  ```c
  // main.c
  #include <stdio.h>
  #include "head.h"
  
  int main()
  {
      int a = 20;
      int b = 12;
      printf("a = %d, b = %d\n", a, b);
      printf("a + b = %d\n", add(a, b));
      printf("a - b = %d\n", subtract(a, b));
      printf("a * b = %d\n", multiply(a, b));
      printf("a / b = %f\n", divide(a, b));
      return 0;
  }
  ```

- 编译运行：`gcc main.c -o app -I ./include -l calc -L ./lib`

  - `-I ./include`指定头文件目录，如果不指定，出现以下错误

    ![image-20210831170715090](01Linux系统编程入门/image-20210831170715090.png)

  - `-l calc`指定静态库名称，如果不指定，出现以下错误

    ![image-20210831170816127](01Linux系统编程入门/image-20210831170816127.png)

  - `-L ./lib`指定静态库位置，如果不指定，出现以下错误

    ![image-20210831170844743](01Linux系统编程入门/image-20210831170844743.png)

  - **正确执行**（成功生成`app`可执行文件）

    ![image-20210831170923394](01Linux系统编程入门/image-20210831170923394.png)

  - 测试程序

    ![image-20210831193122578](01Linux系统编程入门/image-20210831193122578.png)

### 动态库的制作

- 规则

![image-20210831171945803](01Linux系统编程入门/image-20210831171945803.png)

- 示例：有如下图所示文件(其中每个分文件用于实现四则运算)，将其打包为**动态库**

  ![image-20210831164707648](01Linux系统编程入门/image-20210831164707648.png)

  1. 生成`.o`文件：`gcc -c -fpic 文件名`

     ![image-20210831173502435](01Linux系统编程入门/image-20210831173502435.png)

  2. 将`.o`文件打包：`gcc -shared xx1.o xx2.o -o libxxx.so`

     ![image-20210831173600480](01Linux系统编程入门/image-20210831173600480.png)

### 动态库的使用

- 需要提供**动态库文件和相应的头文件**

- 定位动态库（**原因见工作原理->如何定位共享库文件**，其中路径为动态库所在位置）

  - 方法一：修改环境变量，**当前终端生效**，退出当前终端失效

    ```shell
    export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/u/Desktop/Linux/calc/lib
    ```

  - 方法二：修改环境变量，用户级别永久配置

    ```shell
    # 修改~/.bashrc
    vim ~/.bashrc
    
    # 在~/.bashrc中添加下行，保存退出
    export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/u/Desktop/Linux/calc/lib
    
    # 使修改生效
    source ~/.bashrc
    ```

  - 方法三：修改环境变量，系统级别永久配置

    ```shell
    # 修改/etc/profile
    sudo vim /etc/profile
    
    # 在~/.bashrc中添加下行，保存退出
    export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/u/Desktop/Linux/calc/lib
    
    # 使修改生效
    source /etc/profile
    ```

  - 方法四：修改`/etc/ld.so.cache文件列表`

    ```shell
    # 修改/etc/ld.so.conf
    sudo vim /etc/ld.so.conf
    
    # 在/etc/ld.so.conf中添加下行，保存退出
    /home/u/Desktop/Linux/calc/lib
    
    # 更新配置
    sudo ldconfig
    ```

- 有如下结构文件，其中`main.c`测试文件

  ![image-20210831173858257](01Linux系统编程入门/image-20210831173858257.png)

- 编译运行：`gcc main.c -o app -I ./include -l calc -L ./lib`

  ![image-20210831193101168](01Linux系统编程入门/image-20210831193101168.png)

- 测试程序

  ![image-20210831193122578](01Linux系统编程入门/image-20210831193122578.png)

- 如果不将动态库文件绝对路径加入环境变量，则会出现以下错误

  ![image-20210831174331780](01Linux系统编程入门/image-20210831174331780.png)

### 工作原理

- 静态库：`GCC` 进行链接时，会把静态库中代码打包到可执行程序中

- 动态库：`GCC` 进行链接时，动态库的代码不会被打包到可执行程序中

- 程序启动之后，动态库会被动态加载到内存中，通过 `ldd （list dynamic dependencies）`命令检查动态库依赖关系

  ![image-20210831174842063](01Linux系统编程入门/image-20210831174842063.png)

- 如何定位共享库文件呢？

  - 当系统加载可执行代码时候，能够知道其所依赖的库的名字，但是还需要知道**绝对路径**。此时就需要系统的动态载入器来获取该绝对路径
  - 对于`elf格式`的可执行程序，是由`ld-linux.so`来完成的，它先后搜索elf文件的 `DT_RPATH`段 => `环境变量LD_LIBRARY_PATH` => `/etc/ld.so.cache文件列表` => `/lib/`，`usr/lib`目录找到库文件后将其载入内存

### 静态库和动态库的对比

#### 程序编译成可执行程序的过程

![image-20210902092607878](01Linux系统编程入门/image-20210902092607878.png)

#### 静态库制作过程

![image-20210902092645051](01Linux系统编程入门/image-20210902092645051.png)

#### 动态库制作过程

![image-20210902092702345](01Linux系统编程入门/image-20210902092702345.png)

#### 静态库的优缺点

![image-20210902092725852](01Linux系统编程入门/image-20210902092725852.png)

#### 动态库的优缺点

![image-20210902092749213](01Linux系统编程入门/image-20210902092749213.png)

## Makefile

### 概念及安装

- 一个工程中的源文件不计其数，其按类型、功能、模块分别放在若干个目录中，Makefile 文件定义了一系列的规则来指定哪些文件需要先编译，哪些文件需要后编译，哪些文件需要重新编译，甚至于进行更复杂的功能操作，因为 Makefile 文件就像一个 Shell 脚本一样，也可以执行操作系统的命令
- Makefile 带来的好处就是“自动化编译” ，一旦写好，只需要一个 make 命令，整个工程完全自动编译，极大的提高了软件开发的效率。make 是一个命令工具，是一个解释 Makefile 文件中指令的命令工具，一般来说，大多数的 IDE 都有这个命令，比如 Delphi 的 `make`，Visual C++ 的 `nmake`，Linux 下 GNU 的 `make`
- 安装：`sudo apt install make`

### Makefile 文件命名和规则

- 文件命名：`makefile` 或者 `Makefile`

- `Makefile` 规则

  - 一个 Makefile 文件中可以有一个或者多个规则

    ![image-20210902093603940](01Linux系统编程入门/image-20210902093603940.png)

    - 目标：最终要生成的文件（伪目标除外）
    - 依赖：生成目标所需要的文件或是目标
    - 命令：通过执行命令对依赖操作生成目标（命令前必须 Tab 缩进）

  - Makefile 中的其它规则一般都是为第一条规则服务的。

### Makefile编写方式

#### 说明

假设有如下文件

![image-20210902100556519](01Linux系统编程入门/image-20210902100556519.png)

#### 方式一：Makefile+直接编译链接（不推荐）

```makefile
app:add.c div.c multi.c sub.c main.c
	gcc add.c div.c multi.c sub.c main.c -o app
```

![image-20210902101930762](01Linux系统编程入门/image-20210902101930762.png)

#### 方式二：Makefile+编译+链接

```makefile
app:add.o div.o multi.o sub.o main.o
	gcc add.o div.o multi.o sub.o main.o -o app

add.o:add.c
	gcc -c add.c -o add.o

div.o:div.c
	gcc -c div.c -o div.o

multi.o:multi.c
	gcc -c multi.c -o multi.o

sub.o:sub.c
	gcc -c sub.c -o sub.o

main.o:main.c
	gcc -c main.c -o main.o
```

![image-20210902101856277](01Linux系统编程入门/image-20210902101856277.png)

#### 方式三：Makefile+变量

##### 知识点

- 自定义变量：`变量名=变量值`，如`var=hello`

- 预定义变量

  - `AR` : 归档维护程序的名称，默认值为 ar

  - `CC `: C 编译器的名称，默认值为 cc

  - `CXX` : C++ 编译器的名称，默认值为 g++

  - `$@` : 目标的完整名称

  - `$<` : 第一个依赖文件的名称

  - `$^`: 所有的依赖文件

  - 示例

    ![image-20210902095418237](01Linux系统编程入门/image-20210902095418237.png)

- 获取变量的值：`$(变量名)`，如`$(var)`

##### 示例

```makefile
src=add.o div.o multi.o sub.o main.o
target=app
$(target):$(src)
	$(CC) $^ -o $@

add.o:add.c
	$(CC) -c $^ -o $@

div.o:div.c
	$(CC) -c $^ -o $@

multi.o:multi.c
	$(CC) -c $^ -o $@

sub.o:sub.c
	$(CC) -c $^ -o $@

main.o:main.c
	$(CC) -c $^ -o $@
```

![image-20210902103929268](01Linux系统编程入门/image-20210902103929268.png)

#### 方式四：Makefile+模式匹配

##### 知识点

当所要编译的文件过多时，使用模式匹配能够简化操作

![image-20210902095522095](01Linux系统编程入门/image-20210902095522095.png)

##### 示例

```makefile
src=add.o div.o multi.o sub.o main.o
target=app
$(target):$(src)
	$(CC) $^ -o $@

%.o:%.c
	$(CC) -c $< -o $@
```

![image-20210902104314203](01Linux系统编程入门/image-20210902104314203.png)

#### 方法五：Makefile + 函数

##### 知识点

- `$(wildcard PATTERN...)`

  - 功能：获取指定目录下指定类型的文件列表

  - 参数：PATTERN 指的是某个或多个目录下的对应的某种类型的文件，如果有多个目录，一般使用空格间隔

  - 返回：得到的若干个文件的文件列表，文件名之间使用空格间隔

  - 示例

    ![image-20210902100119333](01Linux系统编程入门/image-20210902100119333.png)

- `$(patsubst <pattern>,<replacement>,<text>)`

  - 功能：查找`<text>`中的单词(单词以“空格”、“Tab”或“回车”“换行”分隔)是否符合模式`<pattern>`，如果匹配的话，则以`<replacement>`替换

  - `<pattern>`可以包括通配符`%`，表示任意长度的字串。如果`<replacement>`中也包含`%`，那么，`<replacement>`中的这个`%`将是`<pattern>`中的那个%所代表的字串。(可以用`\`来转义，以`\%`来表示真实含义的`%`字符)

  - 返回：函数返回被替换过后的字符串

  - 示例

    ![image-20210902100350848](01Linux系统编程入门/image-20210902100350848.png)

##### 示例

```makefile
src=$(wildcard ./*.c)
objs=$(patsubst %.c, %.o, $(src))
target=app
$(target):$(objs)
	$(CC) $^ -o $@

%.o:%.c
	$(CC) -c $< -o $@
```

![image-20210902104748931](01Linux系统编程入门/image-20210902104748931.png)

### 清除中间文件

```makefile
src=$(wildcard ./*.c)
objs=$(patsubst %.c, %.o, $(src))
target=app
$(target):$(objs)
	$(CC) $^ -o $@

%.o:%.c
	$(CC) -c $< -o $@

clean:
	rm *.o
```

![image-20210902104842411](01Linux系统编程入门/image-20210902104842411.png)

### 工作原理

- 命令在执行之前，需要先检查规则中的依赖是否存在
  - 如果存在，执行命令
  - 如果不存在，向下检查其它的规则，检查有没有一个规则是用来生成这个依赖的，如果找到了，则执行该规则中的命令
- 检测更新，在执行规则中的命令时，会比较目标和依赖文件的时间
  - 如果依赖的时间比目标的时间晚，需要重新生成目标
  - 如果依赖的时间比目标的时间早，目标不需要更新，对应规则中的命令不需要被执行

- 示例

  - 当修改`main.c`且重新`make`时，如下

    ![image-20210902105057184](01Linux系统编程入门/image-20210902105057184.png)

  - 当不做任何修改且重新`make`时，如下

    ![image-20210902105119451](01Linux系统编程入门/image-20210902105119451.png)