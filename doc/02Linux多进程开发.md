# 进程概述

## 说明

本部分笔记及源码出自`slide/02Linux多进程开发/01 进程概述`

## 程序和进程

- `程序`是包含一系列**信息**的文件，这些信息描述了如何在运行时创建一个`进程`
  - **二进制格式标识**：每个程序文件都包含用于描述可执行文件格式的元信息。内核利用此信息来解释文件中的其他信息，Linux中为ELF可执行连接格式
  - **机器语言指令**：对程序算法进行编码
  - **程序入口地址**：标识程序开始执行时的起始指令位置
  - **数据**：程序文件包含的变量初始值和程序使用的字面量值（比如字符串）
  - **符号表及重定位表**：描述程序中函数和变量的位置及名称。这些表格有多重用途，其中包括调试和运行时的符号解析（动态链接）
  - **共享库和动态链接信息**：程序文件所包含的一些字段，列出了程序运行时需要使用的共享库，以及加载共享库的动态连接器的路径名
  - 其他信息：程序文件还包含许多其他信息，用以描述如何创建进程
- **`进程`是正在运行的`程序`的实例**。是一个具有一定独立功能的程序关于某个数据集合的一次运行活动。它是操作系统动态执行的基本单元，在传统的操作系统中，进程既是基本的分配单元，也是基本的执行单元
- 可以用**一个程序来创建多个进程**，进程是由内核定义的抽象实体，并为该实体分配用以执行程序的各项系统资源。从内核的角度看，进程由用户内存空间和一系列内核数据结构组成，其中用户内存空间包含了程序代码及代码所使用的变量，而内核数据结构则用于维护进程状态信息。记录在内核数据结构中的信息包括许多与进程相关的标识号（IDs）、虚拟内存表、打开文件的描述符表、信号传递及处理的有关信息、进程资源使用及限制、当前工作目录和大量的其他信息

## 单道、多道程序设计

- `单道程序`，即在计算机内存中只允许一个的程序运行
- `多道程序`设计技术是在计算机内存中同时存放几道相互独立的程序，使它们**在管理程序控制下，相互穿插运行**，两个或两个以上程序在计算机系统中同处于开始到结束之间的状态，这些程序共享计算机系统资源。**引入多道程序设计技术的根本目的是为了提高 CPU 的利用率**
- 对于一个**单 CPU 系统**来说，程序同时处于运行状态只是一种宏观上的概念，他们虽然都已经开始运行，但**就微观而言，任意时刻，CPU 上运行的程序只有一个**
- 在多道程序设计模型中，多个进程轮流使用 CPU。而当下常见 **CPU 为纳秒级**，1秒可以执行大约 10 亿条指令。由于**人眼的反应速度是毫秒级**，所以看似同时在运行

## 时间片

- `时间片（timeslice）`又称为`量子（quantum）`或`处理器片（processor slice）`是操作系统分配给每个正在运行的进程微观上的一段 CPU 时间。事实上，虽然一台计算机通常可能有多个 CPU，但是同一个 CPU 永远不可能真正地同时运行多个任务。在只考虑一个 CPU 的情况下，这些进程“看起来像”同时运行的，实则是轮番穿插地运行，由于时间片通常很短（在 Linux 上为 `5ms－800ms`），用户不会感觉到
- **时间片由操作系统内核的调度程序分配给每个进程**。首先，内核会给每个进程分配相等的初始时间片，然后每个进程轮番地执行相应的时间，当所有进程都处于时间片耗尽的状态时，内核会重新为每个进程计算并分配时间片，如此往复

## 并行和并发

- `并行(parallel)`：指在同一时刻，有多条指令在多个处理器上同时执行
- `并发(concurrency)`：指在同一时刻只能有一条指令执行，但多个进程指令被快速的轮换执行，使得在宏观上具有多个进程同时执行的效果，但在微观上并不是同时执行的，只是把时间分成若干段，使多个进程快速交替的执行

![image-20210916215642423](02Linux多进程开发/image-20210916215642423.png)

## 进程控制块（PCB） 

- 为了管理进程，内核必须对每个进程所做的事情进行清楚的描述。内核为每个进程分配一个`PCB(Processing Control Block)进程控制块`，维护进程相关的信息，Linux 内核的进程控制块是 `task_struct` 结构体

- 在 `/usr/src/linux-headers-xxx/include/linux/sched.h` 文件中可以查看 `struct task_struct` 结构体定义，其中`linux-headers-xxx`需要替换为该目录下相应的版本

- 需要掌握的`struct task_struct` 结构体成员

  - **进程id**：系统中每个进程有唯一的 id，用 `pid_t` 类型表示，其实就是一个非负整数

  - **进程的状态**：有`就绪`、`运行`、`挂起`、`停止`等状态

  - 进程切换时需要**保存和恢复的一些CPU寄存器**

  - 描述**虚拟地址空间**的信息

  - 描述**控制终端**的信息

  - 当前工作目录（Current Working Directory） 

  - `umask 掩码`

  - 文件描述符表，包含很多指向 file 结构体的指针

  - 和信号相关的信息

  - 用户 id 和组 id

  - 会话（Session）和进程组

  - 进程可以使用的资源上限（Resource Limit），在Linux中可用`ulimit -a`查看资源上限

    ![image-20210916220259062](02Linux多进程开发/image-20210916220259062.png)

# 进程状态

## 说明

本部分笔记及源码出自`slide/02Linux多进程开发/02 进程状态及转换`

## 基本概念

- 进程状态反映进程执行过程的变化，这些状态随着进程的执行和外界条件的变化而转换
- 分为`三态模型`和`五态模型`

## 三态模型

- `运行态`：进程占有处理器正在运行
- `就绪态`：进程具备运行条件，等待系统分配处理器以便运行。当进程已分配到除CPU以外的所有必要资源后，只要再获得CPU，便可立即执行。在一个系统中处于就绪状态的进程可能有多个，通常将它们排成一个队列，称为就绪队列
- `阻塞态`：又称为等待(wait)态或睡眠(sleep)态，指进程不具备运行条件，正在等待某个事件的完成

![image-20210916222221394](02Linux多进程开发/image-20210916222221394.png)

## 五态模型

- 除`新建态`和`终止态`，其余三个状态与`三态模型`一致
- `新建态`：进程刚被创建时的状态，尚未进入就绪队列
- `终止态`：进程完成任务到达正常结束点，或出现无法克服的错误而异常终止，或被操作系统及有终止权的进程所终止时所处的状态。进入终止态的进程以后不再执行，但依然保留在操作系统中等待善后。一旦其他进程完成了对终止态进程的信息抽取之后，操作系统将删除该进程

![image-20210916222349607](02Linux多进程开发/image-20210916222349607.png)

## 进程相关命令

### 查看进程-静态

- `ps`命令用来查看进程（静态），可以使用`man ps`查看使用说明

  ![image-20210928203808470](02Linux多进程开发/image-20210928203808470.png)

- 常用参数含义

  - a：显示终端上的所有进程，包括其他用户的进程
  - u：显示进程的详细信息
  - x：显示没有控制终端的进程
  - j：列出与作业控制相关的信息

- `ps -aux`或`ps aux`

  ![image-20210928203512766](02Linux多进程开发/image-20210928203512766.png)

  - `USER`：进程所属用户

  - `PID`：进程ID

  - `%CPU`：CPU使用占比

  - `%MEM`：内存使用占比

  - `TTY`：进程所属终端，在终端直接执行`tty`可查看当前`Terminal`所属终端（因为此时我还打开了另外两个终端）

    ![image-20210928204341231](02Linux多进程开发/image-20210928204341231.png)

  - `STAT`：进程状态

    - D ：不可中断 Uninterruptible（usually IO）
    - R：正在运行，或在队列中的进程
    - S(大写) ：处于休眠状态
    - T：停止或被追踪
    - Z：僵尸进程
    - W：进入内存交换（从内核2.6开始无效）
    - X：死掉的进程
    - <：高优先级
    - N：低优先级
    - s：包含子进程
    - \+：位于前台的进程组

  - `START`：进程开始执行时间

  - `TIME`：进程执行持续时间

  - `COMMAND`：进程执行命令

- `ps -ajx`或`ps ajx`

  ![image-20210928203535360](02Linux多进程开发/image-20210928203535360.png)

  - `PPID`：该进程的父进程ID
  - `PGID`：该进程所属组ID
  - `SID`：该进程所属会话(session)ID，多个组构成会话

### 查看进程-动态

- `top`

  ![image-20210928205835614](02Linux多进程开发/image-20210928205835614.png)

- 可以在使用 top 命令时加上 -d 来指定显示信息更新的时间间隔

- 在 top 命令执行后，可以按以下按键对显示的结果进行排序

  - M：根据内存使用量排序
  - P：根据 CPU 占有率排序
  - T：根据进程运行时间长短排序
  - U：根据用户名来筛选进程
  - K：输入指定的 PID 杀死进程

### 杀死进程

- `kill [-signal] pid`

- `kill -l`：列出所有信号

  ![image-20210928210055119](02Linux多进程开发/image-20210928210055119.png)

- `kill -9 进程ID`等价于`kill –SIGKILL 进程ID`

  ![image-20210928210427167](02Linux多进程开发/image-20210928210427167.png)

- `killall name`：根据进程名杀死进程

##  进程号和相关函数

- 每个进程都由进程号来标识，其类型为 `pid_t（整型）`，进程号的范围：`0～32767`。进程号总是唯一的，但可以重用。当一个进程终止后，其进程号就可以再次使用
- **任何进程（除 init 进程）都是由另一个进程创建**，该进程称为被创建进程的父进程，对应的进程号称为父进程号（PPID）
- **进程组是一个或多个进程的集合**。他们之间相互关联，进程组可以接收同一终端的各种信号，关联的进程有一个进程组号（PGID）。默认情况下，当前的进程号会当做当前的进程组号
- 进程号和进程组相关函数
  - `pid_t getpid(void);`：获取进程ID
  - `pid_t getppid(void);`：获取进程的父进程ID
  - `pid_t getpgid(pid_t pid);`：获取进程的组ID

# 进程创建

## 说明

本部分笔记及源码出自`slide/02Linux多进程开发/03 进程创建`

## 进程创建：fork

- 可通过`man 2 fork`查看帮助

  ![image-20211002151951979](02Linux多进程开发/image-20211002151951979.png)

- `pid_t fork(void);`

  ```c
  /*
      #include <sys/types.h>
      #include <unistd.h>
  
      pid_t fork(void);
          函数的作用：用于创建子进程。
          返回值：
              fork()的返回值会返回两次。一次是在父进程中，一次是在子进程中。
              在父进程中返回创建的子进程的ID,
              在子进程中返回0
              如何区分父进程和子进程：通过fork的返回值。
              在父进程中返回-1，表示创建子进程失败，并且设置errno
  */
  
  #include <sys/types.h>
  #include <unistd.h>
  #include <stdio.h>
  
  int main() 
  {
      int num = 10;
  
      // 创建子进程
      pid_t pid = fork();
  
      // 判断是父进程还是子进程
      if(pid > 0) {
          printf("pid : %d\n", pid);
          // 如果大于0，返回的是创建的子进程的进程号，当前是父进程
          printf("i am parent process, pid : %d, ppid : %d\n", getpid(), getppid());
  
          printf("parent num : %d\n", num);
          num += 10;
          printf("parent num += 10 : %d\n", num);
      } else if(pid == 0) {
          // 当前是子进程
          printf("i am child process, pid : %d, ppid : %d\n", getpid(),getppid());
         
          printf("child num : %d\n", num);
          num += 100;
          printf("child num += 100 : %d\n", num);
      }
  
      // for循环
      for(int i = 0; i < 3; i++) {
          printf("i : %d , pid : %d\n", i , getpid());
          sleep(1);
      }
  
      return 0;
  }
  ```

  ![image-20210928220107951](02Linux多进程开发/image-20210928220107951.png)

## fork工作原理

- Linux 的 `fork()` 使用是通过**写时拷贝 (copy- on-write) 实现**。写时拷贝是一种可以推迟甚至避免拷贝数据的技术

- 内核此时并不复制整个进程的地址空间，而是让**父子进程共享同一个地址空间**，只有在**需要写入的时候**才会复制地址空间，从而使各个进程拥有各自的地址空间。即**资源的复制是在需要写入的时候才会进行，在此之前，只有以只读方式共享**（示例程序中`num`的作用）

- **fork之后父子进程共享文件**。fork产生的子进程与父进程**有相同的文件描述符，指向相同的文件表**，引用计数增加，共享文件偏移指针

- 使用**虚拟地址空间**，由于用的是**写时拷贝 (copy- on-write) **，下图**不完全准确，但可帮助理解**

  ![image-20211001210207674](02Linux多进程开发/image-20211001210207674.png)

## 父子进程关系

### 区别

- **fork()函数的返回值不同**。父进程中: >0 返回的是子进程的ID，子进程中: =0
- **pcb中的一些数据不同**。pcb中存的是**当前进程的ID(pid)**，**当前进程的父ID(ppid)**和**信号集**

### 共同点

- 在某些状态下，即**子进程刚被创建出来，还没有执行任何的写数据的操作**。此时**用户区的数据**和**文件描述符表**父进程和子进程一样

### 父子进程对变量共享说明

- 刚开始的时候，是一样的，共享的。如果修改了数据，不共享了
- 读时共享（子进程被创建，两个进程没有做任何的写的操作），写时拷贝

## GDB 多进程调试

- 在以下调试程序**第10行**及**第20行**打断点，后续说明都基于这两个断点

  ![image-20211001212316252](02Linux多进程开发/image-20211001212316252.png)

- 打断点及查看

  ![image-20211001212346310](02Linux多进程开发/image-20211001212346310.png)

- 使用 GDB 调试的时候，GDB 默认只能跟踪一个进程，可以在 fork 函数调用之前，通过指令设置 GDB 调试工具跟踪父进程或者是跟踪子进程，**默认跟踪父进程**

- 查看当前跟踪的进程：`show follow-fork-mode`

  ![image-20211001211945721](02Linux多进程开发/image-20211001211945721.png)

- 设置调试父进程或者子进程：`set follow-fork-mode [parent（默认）| child]`

  ![image-20211001212004830](02Linux多进程开发/image-20211001212004830.png)

  - 调试父进程，子进程循环会自动执行，完毕后需要输入`n`继续执行父进程

    ![image-20211001213311443](02Linux多进程开发/image-20211001213311443.png)

  - 调试子进程，父进程循环会自动执行，完毕后需要输入`n`继续执行子进程

    ![image-20211001213147830](02Linux多进程开发/image-20211001213147830.png)

- 查看调试模式：`show detach-on-fork`

  ![image-20211001212131057](02Linux多进程开发/image-20211001212131057.png)

- 设置调试模式：`set detach-on-fork [on | off]`

  - 默认为 on，表示调试当前进程的时候，其它的进程继续运行，如果为 off，调试当前进

    程的时候，其它进程被 GDB 挂起

  - 注：在设置为`off`时，执行程序会报以下错误，原因是**gdb 8.x版本存在bug**

    ![image-20211001212533538](02Linux多进程开发/image-20211001212533538.png)

  - 以下正常执行的`gdb`版本为`v7.11.1`（截图来源于视频），与设置为`on`的区别在于，**`for`循环是否打印**

    ![image-20211001213504787](02Linux多进程开发/image-20211001213504787.png)

- 查看调试的进程：`info inferiors`，此时调试进程为`parent`，需要执行后才会显示进程

  - 当`detach-on-fork`为`on`时，只会显示一个进程（==因为另一个进程已经执行完毕，销毁==，猜测）

    ![image-20211001215254459](02Linux多进程开发/image-20211001215254459.png)

  - 当`detach-on-fork`为`off`时，会显示两个进程

    ![image-20211001215414550](02Linux多进程开发/image-20211001215414550.png)

- 切换当前调试的进程：`inferior Num`

- 使进程脱离 GDB 调试：`detach inferiors Num`

# exec函数族

## 说明

本部分笔记及源码出自`slide/02Linux多进程开发/04 exec函数族`

## 基本概念

- 可通过`man 3 exec`查看帮助

  ![image-20211002092129575](02Linux多进程开发/image-20211002092129575.png)

- `exec 函数族`的作用是根据指定的文件名找到可执行文件，并用它来取代调用进程的内容，换句话说，就是**在调用进程内部执行一个可执行文件**

- exec 函数族的函数执行成功后不会返回，因为调用进程的实体，包括代码段，数据段和堆栈等都已经被新的内容取代，只留下进程 ID 等一些表面上的信息仍保持原样，颇有些神似“三十六计”中的“金蝉脱壳”。看上去还是旧的躯壳，却已经注入了新的灵魂。只有调用失败了，它们才会返回 -1，从原程序的调用点接着往下执行

- 用户区替换为`a.out`的内容，内核区不变

  ![image-20211002090629048](02Linux多进程开发/image-20211002090629048.png)

## 种类

- 基本组件为`exec`，后面跟不同参数，代表不同含义

  - `l(list) `：参数地址列表，以**空指针结尾**

  - `v(vector) `：存有各参数地址的指针数组的地址

  - `p(path) `：按 PATH 环境变量指定的目录搜索可执行文件，可用`env`查看现有的环境变量

    ![image-20211002093521376](02Linux多进程开发/image-20211002093521376.png)

  - `e(environment)`：存有环境变量字符串地址的指针数组的地址，增加新的环境变量

- 说明：下列示例程序除核心代码外，保持一致，初始包含文件有

  ![image-20211002091926160](02Linux多进程开发/image-20211002091926160.png)

- `int execl(const char *path, const char *arg, .../* (char *) NULL */);`

  - `path`：需要指定的执行的文件的路径或者名称

  - `arg`：是执行可执行文件所需要的参数列表。第一个参数一般没有什么作用，为了方便，一般写的是执行的程序的名称，从第二个参数开始往后，就是程序执行所需要的的参数列表，参数最后需要以NULL结束（哨兵）

  - code

    ```c
    #include <unistd.h>
    #include <stdio.h>
    
    int main() {
    
    
        // 创建一个子进程，在子进程中执行exec函数族中的函数
        pid_t pid = fork();
    
        if(pid > 0) {
            // 父进程
            printf("i am parent process, pid : %d\n",getpid());
            // 如果不加这句，会存在孤儿进程，输出异常
            sleep(1);
        }else if(pid == 0) {
            // 子进程
            // 调用自己写的可执行程序
            execl("/home/u/Desktop/Linux/hello","hello",NULL);
    
            // 调用系统进程
            // execl("/bin/ps", "ps", "aux", NULL);
            perror("execl");
            printf("i am child process, pid : %d\n", getpid());
    
        }
    
        for(int i = 0; i < 3; i++) {
            printf("i = %d, pid = %d\n", i, getpid());
        }
    
    
        return 0;
    }
    ```

  - output

    ![image-20211002092658778](02Linux多进程开发/image-20211002092658778.png)

  - 说明：可以看到，子进程的内容（用户区）被替换，打印的是`hello`中的内容

- `int execlp(const char *file, const char *arg, ... /* (char *) NULL */);`

  - 会到环境变量中查找指定的可执行文件，如果找到了就执行，找不到就执行不成功

  - `file`：只需要提供名称（不需要提供路径）

  - code

    ```c
    #include <unistd.h>
    #include <stdio.h>
    
    int main() {
    
    
        // 创建一个子进程，在子进程中执行exec函数族中的函数
        pid_t pid = fork();
    
        if(pid > 0) {
            // 父进程
            printf("i am parent process, pid : %d\n",getpid());
            sleep(1);
        }else if(pid == 0) {
            // 子进程
            execlp("ps", "ps", "aux", NULL);
    
            printf("i am child process, pid : %d\n", getpid());
    
        }
    
        for(int i = 0; i < 3; i++) {
            printf("i = %d, pid = %d\n", i, getpid());
        }
    
    
        return 0;
    }
    ```

  - output

    ![image-20211002093005924](02Linux多进程开发/image-20211002093005924.png)

- `int execle(const char *path, const char *arg, .../*, (char *) NULL, char * const envp[] */);`

  - `envp`：添加路径至环境变量，注意以`NULL`结尾，否则报`execle: Bad address`

  - code

    ```c
    #include <unistd.h>
    #include <stdio.h>
    
    int main() {
    
    
        // 创建一个子进程，在子进程中执行exec函数族中的函数
        pid_t pid = fork();
    
        if(pid > 0) {
            // 父进程
            printf("i am parent process, pid : %d\n",getpid());
            sleep(1);
        }else if(pid == 0) {
            // 子进程
            // 需要已NULL结尾，否则报 execle: Bad address 错误
            char* envp[] = {"/home/u/Desktop/Linux/", NULL};
            execle("/home/u/Desktop/Linux/hello", "hello", NULL, envp);
            perror("execle");
            printf("i am child process, pid : %d\n", getpid());
    
        }
    
        for(int i = 0; i < 3; i++) {
            printf("i = %d, pid = %d\n", i, getpid());
        }
    
    
        return 0;
    }
    ```

  - output

    ![image-20211002095344859](02Linux多进程开发/image-20211002095344859.png)

- `int execv(const char *path, char *const argv[]);`

  - `argv`：将运行参数都写在数组中

  - code

    ```c
    #include <unistd.h>
    #include <stdio.h>
    
    int main() {
    
    
        // 创建一个子进程，在子进程中执行exec函数族中的函数
        pid_t pid = fork();
    
        if(pid > 0) {
            // 父进程
            printf("i am parent process, pid : %d\n",getpid());
            sleep(1);
        }else if(pid == 0) {
            // 子进程
            char* argv[] = {"hello", NULL};
            execv("/home/u/Desktop/Linux/hello", argv);
            perror("execv");
            printf("i am child process, pid : %d\n", getpid());
    
        }
    
        for(int i = 0; i < 3; i++) {
            printf("i = %d, pid = %d\n", i, getpid());
        }
    
    
        return 0;
    }
    ```

  - output

    ![image-20211002095544288](02Linux多进程开发/image-20211002095544288.png)

- ` int execvp(const char *file, char *const argv[]);`

- `int execvpe(const char *file, char *const argv[], char *const envp[]);`

- `int execve(const char *filename, char *const argv[], char *const envp[]);`

# 进程控制

## 说明

本部分笔记及源码出自`slide/02Linux多进程开发/05 进程控制`

## 进程退出

- 标准C库：`exit()`

- Linux系统：`_exit()`

- 区别

  ![image-20211002102156043](02Linux多进程开发/image-20211002102156043.png)

- 程序说明

  - `exit()`

    ![image-20211002102546106](02Linux多进程开发/image-20211002102546106.png)

  - `_exit()`

    ![image-20211002102641454](02Linux多进程开发/image-20211002102641454.png)

  - 原因：调用`_exit`时没有刷新缓冲区，所以`world`还留在缓冲区中，没有被输出，`\n`会刷新缓冲区

## 孤儿进程

- 父进程运行结束，但子进程还在运行（未运行结束），这样的子进程就称为`孤儿进程（Orphan Process）`
- 每当出现一个孤儿进程的时候，内核就把孤儿进程的父进程设置为 init ，而 init 进程会循环地 wait() 它的已经退出的子进程。
- 孤儿进程并不会有什么危害

```c
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main() 
{
    // 创建子进程
    pid_t pid = fork();
    // 判断是父进程还是子进程
    if(pid > 0) {
        printf("i am parent process, pid : %d, ppid : %d\n", getpid(), getppid());
    } else if(pid == 0) {
        sleep(1);
        // 当前是子进程
        printf("i am child process, pid : %d, ppid : %d\n", getpid(),getppid());
    }
    // for循环
    for(int i = 0; i < 3; i++) {
        printf("i : %d , pid : %d\n", i , getpid());
    }

    return 0;
}
```

![image-20211002105534145](02Linux多进程开发/image-20211002105534145.png)

## 僵尸进程

- 每个进程结束之后，都会释放自己地址空间中的用户区数据，内核区的 PCB 没有办法自己释放掉，需要父进程去释放

- 进程终止时，父进程尚未回收，子进程残留资源（PCB）存放于内核中，变成`僵尸（Zombie）进程`

- **僵尸进程不能被 `kill -9` 杀死**，这样就会导致一个问题，如果父进程不调用 `wait()` 或 `waitpid()` 的话，那么保留的那段信息就不会释放，其进程号就会一直被占用，但是系统所能使用的进程号是有限的，如果大量的产生僵尸进程，将因为没有可用的进程号而导致系统不能产生新的进程，此即为僵尸进程的危害，应当避免

- 示例

  - code

    ```c
    #include <sys/types.h>
    #include <unistd.h>
    #include <stdio.h>
    
    int main() {
    
        // 创建子进程
        pid_t pid = fork();
    
        // 判断是父进程还是子进程
        if(pid > 0) {
            while(1) {
                printf("i am parent process, pid : %d, ppid : %d\n", getpid(), getppid());
                sleep(1);
            }
    
        } else if(pid == 0) {
            // 当前是子进程
            printf("i am child process, pid : %d, ppid : %d\n", getpid(),getppid());
           
        }
    
        // for循环
        for(int i = 0; i < 3; i++) {
            printf("i : %d , pid : %d\n", i , getpid());
        }
    
        return 0;
    }
    ```

  - 僵尸进程ID：45161，可以通过杀死父进程45160，从而使僵尸进程变为孤儿进程，让init领养进行释放

    ![image-20211002110239941](02Linux多进程开发/image-20211002110239941.png)

  - 释放后

    ![image-20211002110519810](02Linux多进程开发/image-20211002110519810.png)

## 进程回收

### 基本概念

-  在每个进程退出的时候，内核释放该进程所有的资源、包括打开的文件、占用的内存等。但是仍然为其保留一定的信息，这些信息主要主要指进程控制块PCB的信息（包括进程号、退出状态、运行时间等）
- 父进程可以通过调用`wait`或`waitpid`得到它的退出状态同时彻底清除掉这个进程，查看帮助：`man 2 wait`
- `wait()` 和 `waitpid()` 函数的功能一样，区别在于
  - `wait()` 函数会阻塞
  - `waitpid()` 可以设置是否阻塞，`waitpid()` 还可以指定等待哪个子进程结束
- 注意：**一次`wait`或`waitpid`调用只能清理一个子进程，清理多个子进程应使用循环**

### 退出信息相关宏函数

- `WIFEXITED(status)`：非0，进程正常退出
- `WEXITSTATUS(status)`：如果上宏为真，获取进程退出的状态（exit的参数）
- `WIFSIGNALED(status)`：非0，进程异常终止
- `WTERMSIG(status)`：如果上宏为真，获取使进程终止的信号编号
- `WIFSTOPPED(status)`：非0，进程处于暂停状态
- `WSTOPSIG(status)`：如果上宏为真，获取使进程暂停的信号的编号
- `WIFCONTINUED(status)`：非0，进程暂停后已经继续运行

### wait()

- 可通过`man 2 wait`查看帮助

  ![image-20211002152046247](02Linux多进程开发/image-20211002152046247.png)

- `pid_t wait(int *wstatus);`

  - 功能：等待任意一个子进程结束，如果任意一个子进程结束了，此函数会回收子进程的资源
  - 参数
    - `int *wstatus`：进程退出时的状态信息，传入的是一个int类型的地址，传出参数。

  - 返回值
    - 成功：返回被回收的子进程的id
    - 失败：-1 (所有的子进程都结束，调用函数失败)

- 其他说明

  - 调用wait函数的进程会被挂起（阻塞），直到它的一个子进程退出或者收到一个不能被忽略的信号时才被唤醒（相当于继续往下执行）
  - 如果没有子进程了，函数立刻返回，返回-1；如果子进程都已经结束了，也会立即返回，返回-1

```c
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() 
{
    // 有一个父进程，创建5个子进程（兄弟）
    pid_t pid;

    // 创建5个子进程
    for(int i = 0; i < 5; i++) {
        pid = fork();
        // 避免嵌套重复生成子进程
        if(pid == 0) {
            break;
        }
    }

    if(pid > 0) {
        // 父进程
        while(1) {
            printf("parent, pid = %d\n", getpid());
            // int ret = wait(NULL);
            int st;
            int ret = wait(&st);

            if(ret == -1) {
                break;
            }

            if(WIFEXITED(st)) {
                // 是不是正常退出
                printf("退出的状态码：%d\n", WEXITSTATUS(st));
            }
            if(WIFSIGNALED(st)) {
                // 是不是异常终止
                printf("被哪个信号干掉了：%d\n", WTERMSIG(st));
            }

            printf("child die, pid = %d\n", ret);

            sleep(1);
        }

    } else if (pid == 0){
        // 子进程
         while(1) {
            printf("child, pid = %d\n",getpid());    
            sleep(1);       
         }

        exit(0);
    }

    return 0; // exit(0)
}
```

- 程序开始执行

  ![image-20211002150658401](02Linux多进程开发/image-20211002150658401.png)

- 通过命令杀死子进程：`kill -9 47548`

  ![image-20211002150754497](02Linux多进程开发/image-20211002150754497.png)

### waitpid()

- 可通过`man 2 wait`查看帮助

  ![image-20211002152139398](02Linux多进程开发/image-20211002152139398.png)

- `pid_t waitpid(pid_t pid, int *wstatus, int options);`
  - 功能：回收指定进程号的子进程，可以设置是否阻塞
  - 参数
    - `pid`
      - `pid > 0` : 回收某个子进程的pid
      - `pid = 0` : 回收当前进程组的所有子进程
      - `pid = -1` : 回收所有的子进程，相当于 wait() （最常用）
      - `pid < -1` : 某个进程组的组id的绝对值，回收指定进程组中的子进程
    - options：设置阻塞或者非阻塞
      - 0 : 阻塞
      - WNOHANG : 非阻塞
    - 返回值
      - \> 0 : 返回子进程的id
      - 0 : options=WNOHANG, 表示还有子进程活着
      - -1 ：错误，或者没有子进程了

```c
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {

    // 有一个父进程，创建5个子进程（兄弟）
    pid_t pid;

    // 创建5个子进程
    for(int i = 0; i < 5; i++) {
        pid = fork();
        if(pid == 0) {
            break;
        }
    }

    if(pid > 0) {
        // 父进程
        while(1) {
            printf("parent, pid = %d\n", getpid());
            sleep(1);

            int st;
            // int ret = waitpid(-1, &st, 0);
            int ret = waitpid(-1, &st, WNOHANG);

            if(ret == -1) {
                break;
            } else if(ret == 0) {
                // 说明还有子进程存在
                continue;
            } else if(ret > 0) {

                if(WIFEXITED(st)) {
                    // 是不是正常退出
                    printf("退出的状态码：%d\n", WEXITSTATUS(st));
                }
                if(WIFSIGNALED(st)) {
                    // 是不是异常终止
                    printf("被哪个信号干掉了：%d\n", WTERMSIG(st));
                }

                printf("child die, pid = %d\n", ret);
            }
           
        }

    } else if (pid == 0){
        // 子进程
         while(1) {
            printf("child, pid = %d\n",getpid());    
            sleep(1);       
         }
        exit(0);
    }

    return 0; 
}
```

![image-20211002154934131](02Linux多进程开发/image-20211002154934131.png)

# 进程间通信

## 说明

本部分笔记及源码出自`slide/02Linux多进程开发/06 进程间通信`

## 进程间通讯概念

- 进程是一个独立的资源分配单元，不同进程（这里所说的进程通常指的是用户进程）之间的资源是独立的，没有关联，不能在一个进程中直接访问另一个进程的资源
- 但是，进程不是孤立的，不同的进程需要进行信息的交互和状态的传递等，因此需要`进程间通信( IPC：Inter Processes Communication)`
- 进程间通信的目的
  - 数据传输：一个进程需要将它的数据发送给另一个进程
  - 通知事件：一个进程需要向另一个或一组进程发送消息，通知它（它们）发生了某种事件（如进程终止时要通知父进程）
  - 资源共享：多个进程之间共享同样的资源。为了做到这一点，需要内核提供互斥和同步机制
  - 进程控制：有些进程希望完全控制另一个进程的执行（如 Debug 进程），此时控制进程希望能够拦截另一个进程的所有陷入和异常，并能够及时知道它的状态改变

## Linux 进程间通信的方式

![image-20211002162256108](02Linux多进程开发/image-20211002162256108.png)

## 管道

### 管道特点

- 管道其实是一个在**内核内存中维护的缓冲器**，这个缓冲器的存储能力是有限的，不同的操作系统大小不一定相同
- 管道拥有文件的特质：读操作、写操作
  - **匿名管道**没有文件实体
  - **有名管道**有文件实体，但不存储数据。可以按照操作文件的方式对管道进行操作
- **一个管道是一个字节流**，使用管道时不存在消息或者消息边界的概念，从管道读取数据的进程可以读取任意大小的数据块，而不管写入进程写入管道的数据块的大小是多少
- 通过管道传递的数据是顺序的，从管道中读取出来的字节的顺序和它们被写入管道的顺序是完全一样的
- 在管道中的数据的传递方向是单向的，一端用于写入，一端用于读取，管道是**半双工**的
- 从管道读数据是一次性操作，数据一旦被读走，它就从管道中被抛弃，释放空间以便写更多的数据，**在管道中无法使用 lseek() 来随机的访问数据**
- `匿名管道`只能在**具有公共祖先的进程（父进程与子进程，或者两个兄弟进程，具有亲缘关系）之间使用**

![image-20211002170404267](02Linux多进程开发/image-20211002170404267.png)

### 管道实现进程通信的原理

- 管道相当于**一个中间媒介，共享数据**

![image-20211002170600779](02Linux多进程开发/image-20211002170600779.png)

### 管道的数据结构

![image-20211002170726732](02Linux多进程开发/image-20211002170726732.png)

### 匿名管道

#### 概念及使用

- `管道`也叫`无名（匿名）管道`，它是是 UNIX 系统 IPC（进程间通信）的最古老形式，所有的 UNIX 系统都支持这种通信机制
- 统计一个目录中文件的数目命令：`ls | wc –l`，为了执行该命令，shell 创建了两个进程来分别执行 ls 和 wc

![image-20211002170052657](02Linux多进程开发/image-20211002170052657.png)

- 查看帮助：`man 2 pipe`

- 创建匿名管道：`int pipe(int pipefd[2]);`

- 查看管道缓冲大小命令：`ulimit –a `（共8个，每个521byte，即4k）

  ![image-20211002183127455](02Linux多进程开发/image-20211002183127455.png)

- 查看管道缓冲大小函数：`long fpathconf(int fd, int name);`

#### 创建匿名管道

- `int pipe(int pipefd[2])`

  - 功能：创建一个匿名管道，用来进程间通信。
  - 参数：`int pipefd[2]` 这个数组是一个传出参数。
    - `pipefd[0]` 对应的是管道的读端
    - `pipefd[1]` 对应的是管道的写端
  - 返回值：成功 0，失败 -1

- 注意

  - 管道默认是阻塞的：如果管道中没有数据，read阻塞，如果管道满了，write阻塞
  - 匿名管道只能用于具有关系的进程之间的通信（父子进程，兄弟进程）

- 实现**子进程发送数据给父进程，父进程读取到数据输出**

  - 管道应在子进程创建前生成，否则父子进程不一定对应同一个管道

  - 单向发送时

    - 由于读写顺序不定，看起来像自己写自己读

    ![image-20211002184318546](02Linux多进程开发/image-20211002184318546.png)

    - 解决方法：关闭不需要的端口（即代码中的`close(pipefd[1]);`）

      ![image-20211002184931014](02Linux多进程开发/image-20211002184931014.png)

    - 实际在不加`sleep`运行时，会出现下列问题，原因是==写的速度过快，向管道连续写了好多次，才被读取到一次，父进程接收到过多的子进程信息是因为父进程每次读完管道中的数据，想要再次读取时就会因为管道为空而被阻塞。所以就造成了从效果上来看写的速度要比读的快==

      ![image-20211002184623154](02Linux多进程开发/image-20211002184623154.png)

  - 注意双向发送时，注意父子进程的读写顺序（代码中注释段）

  ```c
  /*
      #include <unistd.h>
      int pipe(int pipefd[2]);
          功能：创建一个匿名管道，用来进程间通信。
          参数：int pipefd[2] 这个数组是一个传出参数。
              pipefd[0] 对应的是管道的读端
              pipefd[1] 对应的是管道的写端
          返回值：
              成功 0
              失败 -1
  
      管道默认是阻塞的：如果管道中没有数据，read阻塞，如果管道满了，write阻塞
  
      注意：匿名管道只能用于具有关系的进程之间的通信（父子进程，兄弟进程）
  */
  
  // 子进程发送数据给父进程，父进程读取到数据输出
  #include <unistd.h>
  #include <sys/types.h>
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  
  int main() {
  
      // 在fork之前创建管道
      int pipefd[2];
      int ret = pipe(pipefd);
      if(ret == -1) {
          perror("pipe");
          exit(0);
      }
  
      // 创建子进程
      pid_t pid = fork();
      if(pid > 0) {
          // 父进程
          printf("i am parent process, pid : %d\n", getpid());
  
          // 关闭写端
          // close(pipefd[1]);
          
          // 从管道的读取端读取数据
          char buf[1024] = {0};
          while(1) {
              int len = read(pipefd[0], buf, sizeof(buf));
              printf("parent recv : %s, pid : %d\n", buf, getpid());
              
              // 向管道中写入数据
              //char * str = "hello,i am parent";
              //write(pipefd[1], str, strlen(str));
              //sleep(1);
          }
  
      } else if(pid == 0){
          // 子进程
          printf("i am child process, pid : %d\n", getpid());
          // 关闭读端
          // close(pipefd[0]);
          char buf[1024] = {0};
          while(1) {
              // 向管道中写入数据
              char * str = "hello,i am child";
              write(pipefd[1], str, strlen(str));
              sleep(1);
  
              // int len = read(pipefd[0], buf, sizeof(buf));
              // printf("child recv : %s, pid : %d\n", buf, getpid());
              // bzero(buf, 1024);
          }
          
      }
      return 0;
  }
  ```

  ![image-20211002173606571](02Linux多进程开发/image-20211002173606571.png)

#### 实例：自建管道实现shell命令(`ps aux`)

- 思路

  - 子进程： 实现`ps aux`, 子进程结束后，将数据发送给父进程
  - 父进程：获取到数据并打印
  - `pipe()->fork()->execlp()<在此之前，输出为文件描述符重定向>->打印`

- code

  ```c
  /*
      实现 ps aux | grep xxx 父子进程间通信
      
      子进程： ps aux, 子进程结束后，将数据发送给父进程
      父进程：获取到数据，过滤
      pipe()
      execlp()
      子进程将标准输出 stdout_fileno 重定向到管道的写端。  dup2
  */
  
  #include <unistd.h>
  #include <sys/types.h>
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include <wait.h>
  
  int main() {
  
      // 创建一个管道
      int fd[2];
      int ret = pipe(fd);
  
      if(ret == -1) {
          perror("pipe");
          exit(0);
      }
  
      // 创建子进程
      pid_t pid = fork();
  
      if(pid > 0) {
          // 父进程
          // 关闭写端，必须要有，否则程序不会结束
          close(fd[1]);
          // 从管道中读取
          char buf[1024] = {0};
  
          int len = -1;
          while((len = read(fd[0], buf, sizeof(buf) - 1)) > 0) {
              // 过滤数据输出
              printf("%s", buf);
              memset(buf, 0, 1024);
          }
  
          wait(NULL);
  
      } else if(pid == 0) {
          // 子进程
          // 关闭读端
          close(fd[0]);
  
          // 文件描述符的重定向 stdout_fileno -> fd[1]
          dup2(fd[1], STDOUT_FILENO);
          // 执行 ps aux
          execlp("ps", "ps", "aux", NULL);
          perror("execlp");
          exit(0);
      } else {
          perror("fork");
          exit(0);
      }
  
  
      return 0;
  }
  ```

- ==未解决：./ipc | wc - c 比 ps aux | wc -c 统计的进程数不同==

#### 设置管道非阻塞

```c
int flags = fcntl(fd[0], F_GETFL);  // 获取原来的flag
flags |= O_NONBLOCK;            // 修改flag的值
fcntl(fd[0], F_SETFL, flags);   // 设置新的flag
```

#### 读写特点总结

- 读管道
  - 管道中有数据，read返回实际读到的字节数
  - 管道中无数据
    - 写端被全部关闭，read返回0（相当于读到文件的末尾）
    - 写端没有完全关闭，read阻塞等待
- 写管道
  - 管道读端全部被关闭，进程异常终止（进程收到`SIGPIPE`信号）
  - 管道读端没有全部关闭：
    - 管道已满，write阻塞
    - 管道没有满，write将数据写入，并返回实际写入的字节数

### 有名管道

#### 概念及使用

- 匿名管道，由于没有名字，只能用于亲缘关系的进程间通信。为了克服这个缺点，提出了`有名管道（FIFO）`，也叫`命名管道`、`FIFO文件`
- `有名管道（FIFO）`不同于匿名管道之处在于它**提供了一个路径名与之关联**，以 **FIFO 的文件形式存在于文件系统中**，并且其打开方式与打开一个普通文件是一样的，这样即使与 `FIFO` 的创建进程不存在亲缘关系的进程，只要可以访问该路径，就能够彼此通过 `FIFO` 相互通信，因此，通过 `FIFO` 不相关的进程也能交换数据
- 一旦打开了 `FIFO`，就能在它上面使用与操作匿名管道和其他文件的系统调用一样的I/O系统调用了（如`read()`、`write()`和`close()`）。与管道一样，`FIFO` 也有一个写入端和读取端，并且从管道中读取数据的顺序与写入的顺序是一样的。FIFO 的名称也由此而来：先入先出
- `有名管道（FIFO)`和`匿名管道（pipe）`有一些特点是相同的，不一样的地方在于
  - `FIFO` 在文件系统中作为一个特殊文件存在，但 `FIFO` 中的**内容却存放在内存中**
  - 当使用 `FIFO` 的进程退出后，`FIFO` 文件将继续保存在文件系统中以便以后使用
  - `FIFO` 有名字，不相关的进程可以通过打开有名管道进行通信

- 可使用`man fifo`查看帮助

#### 创建有名管道

- shell命令创建：`mkfifo 文件名`，可通过`man 1 mkfifo`查看帮助

  ![image-20211003160648019](02Linux多进程开发/image-20211003160648019.png)

- 函数创建：`int mkfifo(const char *pathname, mode_t mode);`，可通过`man 3 mkfifo`查看帮助

  ```c
  #include <sys/types.h>
  #include <sys/stat.h>
  #include <stdio.h>
  #include <unistd.h>
  #include <stdlib.h>
  
  int main()
  {
      // 判断文件是否存在
      int ret = access("test", F_OK);
      // 不存在则创建
      if (ret == -1) {
          printf("管道不存在，创建管道...\n");
          ret = mkfifo("test", 0664);
          if (ret == -1) {
              perror("mkfifo");
              exit(0);
          }
      }
      
      return 0;
  }
  ```

  ![image-20211003161504190](02Linux多进程开发/image-20211003161504190.png)

#### 实例：两进程通过有名管道通信（单一发送）

- 写端

  ```c
  #include <stdio.h>
  #include <sys/types.h>
  #include <sys/stat.h>
  #include <stdlib.h>
  #include <unistd.h>
  #include <fcntl.h>
  #include <string.h>
  
  // 向管道中写数据
  int main() 
  {
      // 1.判断文件是否存在
      int ret = access("test", F_OK);
      if(ret == -1) {
          printf("管道不存在，创建管道\n");
          
          // 2.创建管道文件
          ret = mkfifo("test", 0664);
  
          if(ret == -1) {
              perror("mkfifo");
              exit(0);
          }       
  
      }
  
      // 3.以只写的方式打开管道
      int fd = open("test", O_WRONLY);
      if(fd == -1) {
          perror("open");
          exit(0);
      }
  
      // 写数据
      for(int i = 0; i < 100; i++) {
          char buf[1024];
          sprintf(buf, "hello, %d\n", i);
          printf("write data : %s\n", buf);
          write(fd, buf, strlen(buf));
          sleep(1);
      }
  
      close(fd);
  
      return 0;
  }
  ```

- 读端

  ```c
  #include <stdio.h>
  #include <sys/types.h>
  #include <sys/stat.h>
  #include <stdlib.h>
  #include <unistd.h>
  #include <fcntl.h>
  
  // 从管道中读取数据
  int main() 
  {
      // 1.打开管道文件
      int fd = open("test", O_RDONLY);
      if(fd == -1) {
          perror("open");
          exit(0);
      }
  
      // 读数据
      while(1) {
          char buf[1024] = {0};
          // 这里不能写strlen(buf) 因为这里的含义是每次按固定长度读取，最开始strlen(buf)=0
          int len = read(fd, buf, sizeof(buf));
          if(len == 0) {
              printf("写端断开连接了...\n");
              break;
          }
          printf("recv buf : %s\n", buf);
      }
  
      close(fd);
  
      return 0;
  }
  ```

- 运行

  - 当写端开始写数据，但读端没有启动时，写端阻塞

    ![image-20211003164458310](02Linux多进程开发/image-20211003164458310.png)

  - 当读端开始读数据，但写端没有启动时，读端阻塞

    ![image-20211003164517651](02Linux多进程开发/image-20211003164517651.png)

  - 两端都启动时，正常输出（无关哪个写启动）

    ![image-20211003164554381](02Linux多进程开发/image-20211003164554381.png)

    - 先关闭读端

      ![image-20211003164654992](02Linux多进程开发/image-20211003164654992.png)

    - 先关闭写端![image-20211003164634420](02Linux多进程开发/image-20211003164634420.png)

#### 实例：简易版聊天功能（连续发送）

- 功能：两个进程相互发送数据及接收数据，能够连续发送及接收

- 思路

  - 由于两个进程并没有亲缘关系，所以只能使用有名管道实现
  - 需要两个管道
    - 一个管道用于进程A的写与进程B的读
    - 一个管道用于进程B的写与进程A的读
  - 需要父子进程，实现连续发送及接收
    - 父进程负责写入数据到管道
    - 子进程负责从管道读取数据

- 流程（不包含父子进程，即下图所示流程不能实现连续发送功能）

  ![image-20211003171227426](02Linux多进程开发/image-20211003171227426.png)

- 进程A

  ```c
  /*
  chatA
  1. 读、写数据分开，用两个管道
      1. fifo1用于进程A写及进程B读
      2. fifo2用于进程B写及进程A读
  2. 连续发送及接收信息，使用两个进程
      1. 父进程用于写数据
      2. 子进程用于读数据
  */
  #include <stdio.h>
  #include <unistd.h>
  #include <sys/types.h>
  #include <sys/stat.h>
  #include <stdlib.h>
  #include <unistd.h>
  #include <fcntl.h>
  #include <string.h>
  
  int main()
  {
      // 判断写管道是否存在，不存在则创建
      int ret = access("fifo1", F_OK);
      if (ret == -1) {
          printf("fifo1不存在，创建...\n");
          ret = mkfifo("fifo1", 0664);
          if (ret == -1) {
              perror("mkfifo");
              exit(-1);
          }
      } 
  
      // 判断读管道是否存在，不存在则创建
      ret = access("fifo2", F_OK);
      if (ret == -1) {
          printf("fifo2不存在，创建...\n");
          ret = mkfifo("fifo2", 0664);
          if (ret == -1) {
              perror("mkfifo");
              exit(-1);
          }
      } 
      // 创建进程
      pid_t pid = fork();
      char buf[1024];
      if (pid > 0) {
          // 父进程
          // 打开写管道
          // 打开一次，否则系统可能会崩
          int fdw = open("fifo1", O_WRONLY);
          while (1) {
              // 从键盘读取输入
              printf("[chatA]please input: \n");
              fgets(buf, sizeof(buf), stdin);
              write(fdw, buf, strlen(buf));
              // 清空数组
              memset(buf, 0, sizeof(buf));
          }
          close(fdw);
      } else if (pid == 0) {
          // 子进程
          // 打开读管道
          // 打开一次，否则系统可能会崩
          int fdr = open("fifo2", O_RDONLY);
          while (1) {
              char buf[1024];
              int len = read(fdr, buf, sizeof(buf));
              if(len == 0) {
                  printf("[chatA]写端断开连接了...\n");
                  break;
              }
              printf("[chatA]recv : %s", buf);
              // 清空数组
              memset(buf, 0, sizeof(buf));
          }
          close(fdr);
      } else {
          perror("fork");
          exit(-2);
      }
  
      return 0;
  }
  ```

- 进程B

  ```c
  /*
  chatB
  1. 读、写数据分开，用两个管道
      1. fifo1用于进程A写及进程B读
      2. fifo2用于进程B写及进程A读
  2. 连续发送及接收信息，使用两个进程
      1. 父进程用于写数据
      2. 子进程用于读数据
  */
  #include <stdio.h>
  #include <unistd.h>
  #include <sys/types.h>
  #include <sys/stat.h>
  #include <stdlib.h>
  #include <unistd.h>
  #include <fcntl.h>
  #include <string.h>
  
  int main()
  {
      // 判断写管道是否存在，不存在则创建
      int ret = access("fifo1", F_OK);
      if (ret == -1) {
          printf("fifo1不存在，创建...\n");
          ret = mkfifo("fifo1", 0664);
          if (ret == -1) {
              perror("mkfifo");
              exit(-1);
          }
      } 
  
      // 判断读管道是否存在，不存在则创建
      ret = access("fifo2", F_OK);
      if (ret == -1) {
          printf("fifo2不存在，创建...\n");
          ret = mkfifo("fifo2", 0664);
          if (ret == -1) {
              perror("mkfifo");
              exit(-1);
          }
      } 
      // 创建进程
      pid_t pid = fork();
      char buf[1024] = { 0 };
      if (pid > 0) {
          // 父进程
          // 打开写管道
          // 打开一次，否则系统可能会崩
          int fdw = open("fifo2", O_WRONLY);
          while (1) {
              // 从键盘读取输入
              printf("[chatB]please input: \n");
              fgets(buf, sizeof(buf), stdin);
              write(fdw, buf, strlen(buf));
              // 清空数组
              memset(buf, 0, sizeof(buf));
          }
          close(fdw);
      } else if (pid == 0) {
          // 子进程
          // 打开读管道
          // 打开一次，否则系统可能会崩
          int fdr = open("fifo1", O_RDONLY);
          while (1) {
              char buf[1024];
              int len = read(fdr, buf, sizeof(buf));
              if(len == 0) {
                  printf("[chatB]写端断开连接了...\n");
                  break;
              }
              printf("[chatB]recv : %s", buf);
              // 清空数组
              memset(buf, 0, sizeof(buf));
          }
          close(fdr);
      } else {
          perror("fork");
          exit(-2);
      }
  
      return 0;
  }
  ```

- 运行结果

  ![image-20211003223202138](02Linux多进程开发/image-20211003223202138.png)

- ==存在的问题==：
  - 乱码
  - 一个进程结束后，另一个还未结束，需要手动关闭

#### 读写特点总结

- 读管道
  - 管道中有数据，`read`返回实际读到的字节数
  - 管道中无数据：
    - 管道写端被全部关闭，`read`返回0，（相当于读到文件末尾）
    - 写端没有全部被关闭，` read`阻塞等待
- 写管道
  - 管道读端被全部关闭，进行异常终止（收到一个`SIGPIP`信号）
  - 管道读端没有全部关闭：
    - 管道已经满了，`write`会阻塞
    - 管道没有满，`write`将数据写入，并返回实际写入的字节数

## 内存映射

### 概念

- `内存映射（Memory-mapped I/O）`是将**磁盘文件的数据映射到内存**，用户通过修改内存就能修改磁盘文件

  ![image-20211004093620731](02Linux多进程开发/image-20211004093620731.png)

- 内存映射相关系统调用，使用`man 2 mmap`查看帮助
  - `void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);`
    - 功能：将一个文件或者设备的数据映射到内存中
    - 参数
      - `addr`：设置为 NULL时, 由内核指定（推荐做法）
      - `length` : 要映射的数据的长度，这个值**不能为0。建议使用文件的长度**，获取文件的长度：`stat `，`lseek`
      - `prot` : 对申请的内存映射区的操作权限
        - `PROT_EXEC` ：可执行的权限
        - `PROT_READ` ：读权限
        - `PROT_WRITE` ：写权限
        - `PROT_NONE` ：没有权限
      - `flags`
        - `MAP_SHARED` : 映射区的数据会自动和磁盘文件进行同步，进程间通信，必须要设置这个选项
        - `MAP_PRIVATE` ：不同步，内存映射区的数据改变了，对原来的文件不会修改，会重新创建一个新的文件。（`copy on write`）
      - `fd`: 需要映射的那个文件的文件描述符，通过`open`得到，`open`的是一个磁盘文件
      - `offset`：偏移量，一般进行特殊指定（指定为0即可），如果使用必须指定的是 `4k` 的整数倍，0表示不偏移
    - 返回值：返回创建的内存的首地址。失败返回`MAP_FAILED(即(void *) -1)`
  - `int munmap(void *addr, size_t length);`
    -  功能：释放内存映射
    - 参数
      - `addr` : 要释放的内存的首地址
      - `length` : 要释放的内存的大小，要和`mmap`函数中的length参数的值一样

### 进程间通信

- 有关系的进程（父子进程）
  - 还没有子进程的时候，通过唯一的父进程，先创建内存映射区
  - 有了内存映射区以后，创建子进程
  - 父子进程共享创建的内存映射区
- 没有关系的进程间通信
  - 准备一个大小不是0的磁盘文件
  - 进程1 通过磁盘文件创建内存映射区，得到一个操作这块内存的指针
  - 进程2 通过磁盘文件创建内存映射区，得到一个操作这块内存的指针
  - 使用内存映射区通信

### 注意事项

- 要操作映射内存，**必须要有读的权限**，即权限为`PROT_READ`或`PROT_READ|PROT_WRITE`

- 在使用**内存映射**通信时，使用文件的大小不能为0，**`open`指定的权限不能和`prot`参数有冲突**

  |          `prot`          |        `open`         |
  | :----------------------: | :-------------------: |
  |       `PROT_READ`        | `O_RDONLY` 或`O_RDWR` |
  | `PROT_READ | PROT_WRITE` |       `O_RDWR`        |

- 内存映射区通信，是非阻塞

- 一个文件对应一个内存映射区

- 如果对`mmap`的返回值(`ptr`)做`++操作(ptr++)`, `munmap`是否能够成功?

  - 不能成功，因为回收资源时，需要传递指针，如果变化，将会回收失败

- 如果`open`时`O_RDONLY`, `mmap`时`prot`参数指定`PROT_READ | PROT_WRITE`会怎样?

  - 错误，返回`MAP_FAILED`，`open()`函数中的权限建议和`prot`参数的权限保持一致

- 如果文件偏移量为1000会怎样?

  - 偏移量必须是`4K`的整数倍，返回`MAP_FAILED`

- `mmap`什么情况下会调用失败?

  - 第二个参数：length = 0
  - 第三个参数：`prot`
    - 只指定写权限
    - `prot`和`open()`两者的权限不匹配

- 可以open的时候`O_CREAT`一个新文件来创建映射区吗?

  - 可以的，但是创建的文件的大小如果为0的话，肯定不行(因为`mmap`调用时，长度不允许为0)

- `mmap`后关闭文件描述符，对`mmap`映射有没有影响？

  - 映射区还存在，创建映射区的`fd`被关闭，没有任何影响

- 对`ptr`越界操作会怎样？

  - 越界操作操作的是非法的内存 -> 段错误

### 实例：父子进程通信

- 思路
  1. 打开指定文件并获取文件长度
  2. 创建内存映射区
  3. 父子进程功能，父进程负责收数据，子进程负责发数据
  4. 回收资源

- code

  ```c
  #include <stdio.h>
  #include <sys/mman.h>
  #include <sys/types.h>
  #include <fcntl.h>
  #include <unistd.h>
  #include <wait.h>
  #include <string.h>
  #include <stdlib.h>
  
  int main()
  {
      // 打开指定文件
      int fd = open("ipc.txt", O_RDWR);
      // 获取给定文件长度
      int size = lseek(fd, 0, SEEK_END);
      // 创建内存映射区
      void* ptr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
      // 判断是否成功
      if (ptr == MAP_FAILED) {
          perror("mmap");
          exit(-1);
      }
      // 创建子进程
      pid_t pid = fork();
      if (pid > 0) {
          // 父进程，用于读取数据
          // 回收子进程
          wait(NULL);
          // 接收数据并打印
          char buf[64];
          // 类型需要强转
          strcpy(buf, (char *)ptr);
          printf("recv : %s\n", buf);
  
      } else if (pid == 0) {
          // 子进程，用于发送数据
          // 类型需要强转
          strcpy((char *)ptr, "hello, i am child process");
      } else {
          perror("fork");
          exit(-1);
      }
  
      // 关闭内存映射区
      munmap(ptr, size);
      // 关闭文件
      close(fd);
      return 0;
  }
  ```

- 注意：程序执行后，文件大小不改变，那么子进程写入的数据会被截断，==原因未知==

  - 执行前

    ![image-20211004111150651](02Linux多进程开发/image-20211004111150651.png)

  - 执行后

    ![image-20211004111241118](02Linux多进程开发/image-20211004111241118.png)

### 实例：文件拷贝

- 思路

  1. 需要两个文件，一个是有内容的文件（待拷贝文件），一个是空文件
  2. 由于有两个文件，需要两个内存映射区
  3. 然后将文件A的内存映射区内容拷贝给文件B的内存映射区
  4. 回收资源

- code

  ```c
  #include <stdio.h>
  #include <sys/types.h>
  #include <sys/stat.h>
  #include <fcntl.h>
  #include <unistd.h>
  #include <sys/mman.h>
  #include <string.h>
  #include <stdlib.h>
  
  int main()
  {
      // 打开源文件，获取文件长度并创建对应内存映射区
      int fdSource = open("source.txt", O_RDONLY);
      int len = lseek(fdSource, 0, SEEK_END);
      void *ptrSource = mmap(NULL, len, PROT_READ, MAP_SHARED, fdSource, 0);
      if (ptrSource == MAP_FAILED) {
          perror("mmap");
          exit(-1);
      }
      
      // 打开目标文件，并创建对应内存映射区
      int fdTarget = open("target.txt", O_RDWR | O_CREAT, 0664);
      // 由于目标文件是通过创建得到，所以需要扩展长度与源文件保持一致
      truncate("target.txt", len);
      // 如果不加，扩展可能失败（保险起见）
      write(fdTarget, " ", 1);
      void *ptrTarget = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED, fdTarget, 0);
      if (ptrTarget == MAP_FAILED) {
          perror("mmap");
          exit(-1);
      }
      
      // 内存拷贝
      memcpy(ptrTarget, ptrSource, len);
      
      // 回收资源
      close(fdTarget);
      close(fdSource);
      munmap(ptrTarget, len);
      munmap(ptrSource, len);
  
      return 0;
  }
  ```

- output

  - 执行前

    ![image-20211004144251533](02Linux多进程开发/image-20211004144251533.png)

  - 执行后

    ![image-20211004144319921](02Linux多进程开发/image-20211004144319921.png)

### 实例：匿名内存映射

- 思路

  1. 匿名内存映射不存在文件实体，那么只能通过父子进程实现
  2. 父子进程操作同一块区域，重点在于内存映射区在创建时新增flags参数`MAP_ANONYMOUS`
  3. 父进程读，子进程写

- code

  ```c
  #include <stdio.h>
  #include <sys/mman.h>
  #include <sys/types.h>
  #include <unistd.h>
  #include <stdlib.h>
  #include <string.h>
  #include <sys/wait.h>
  
  int main()
  {
      void *ptr = mmap(NULL, 128, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
      if (ptr == MAP_FAILED) {
          perror("mmap");
          exit(-1);
      }
      pid_t pid = fork();
      if (pid > 0) {
          // 父进程
          wait(NULL);
          char buf[128];
          strcpy(buf, (char*)ptr);
          printf("recv : %s\n", buf);
      } else if (pid == 0) {
          // 子进程
          strcpy((char*)ptr, "i am a message");
      } else {
          perror("fork");
          exit(-1);
      }
  
      // 释放资源
      munmap(ptr, 128);
      return 0;
  }
  ```

- output

  ![image-20211004145355131](02Linux多进程开发/image-20211004145355131.png)
