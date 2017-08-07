Tuxedo是什么？
Tuxedo:Transaction for Unix has been Extended for Distributed Operation分布式操作扩展之后的Unix事务系统。
交易中间件位于client和server之间
Tuxedo是一个事务处理(TP)监督器（transaction processing monitor），它管理联机事务处理(OLTP)系统操作的事务。客户通过结构化查询语言(SQL)调用，或其它类型的请求，产生对服务器的请求。这个事务处理监督器确信，正确地进行了修改，以保证数据的完整性。这在一个事务可以改变多个位置的数据库的分布式数据库环境是非常重要的。这个事务处理监督器使用双阶段提交，以保证所有的数据库都已经接收和认可了这些数据的正确性。否则，这个数据库返回它的事务前状态
 
WTC:WebLogic Tuxedo Connector
OLTP: On-Line Transaction Processing 联机事务处理
OLAP: On-Line Analytical Processing 联机分析处理
ATMI:application-to-Transaction Monitor Interface 应用程序到事务监视器接口
DTP:Distributed Transaction Processing分布式事务处理
MSSQ：Mutile Server,Singal Queue
 
TUXEDO 采用三层结构的组件软件模型 ：
 Client 为第一逻辑层。实现用户交互和数据表示，向第二层的Server发请求，调用业务逻辑处理服务。
 Server组件中间层，这些组件由TUXEDO管理，实现业务逻辑服务,接收服务请求，并返回服务结果。
 第三层为资源管理器，比如像关系数据库。负责管理应用系统的数据资源    
 
Tuxedo的核心子系统：
事务管理器 TM(Transaction Manager)
工作站 WorkStation
域 Domain
队列 Queue

Tuxedo 安装：
安装前需要创建一个新用户(也可以不用创建)
1. 下载 （这里下载版本 tuxedo111120_32_Linux_01_x86）
./tuxedo111120_32_Linux_01_x86.bin  -i console
2. 安装设置
http://www.cnblogs.com/fnng/archive/2013/02/10/2909860.html


tmboot  启动服务：
参数说明：
-l  lmid 启动逻辑服务器名为lmcd服务器上的所有进程
-g grpname 启动GROUP名为grpname的所有进程
-i  srvid 启动SRVID为srvid中的服务进程
-s aout 启动名aout的服务进程
- o sequence 启动SEQUENCE=sequence的服务进程
-A 启动所有的管理进程
-b 在没有把BACKUP服务器变为MASTER服务器的情况下，从BACKUP服务器上启动整个TUXEDO的进程。
-B lmid 在逻辑名为lmid的服务器上启动BBL进程
-M 在MASTER服务器上启动所有管理进程。如果TUXEDO应用系统是SHM模式，则启动BBL进程如果该TUXEDO应用系统是MP模式，则启动DBBL、BBL、和BRAIDGE进程
-dl 把服务进程启动时命令行参数显示出来，一般在用sdb等调试工具调试服务进程是使用。
-T grpname 启动grpname中所有TMS进程
-e command 若某个基础启动失败，执行command参数指定的命令，该命令可以是一个可执行程序，SHELL脚本等
-y 对启动服务器上的所有进程回答YES
-c 计算该TUXEDO 应用系统在运行时对IPC资源的最小需求并输出
如果一个TUXEDO应用启动失败，可能的原因有：
1，MAXACCESSES,MAXSERVERS和MAXSERVICES参数的值太大，超过了系统的IPC资源的限制，可减少它们的值再试。
2，在该TUXEDO应用系统中要用到TLOG，当该TLOG文件还没有创建时，应该先创建该TLOG文件。
3，在UBBCONFIG中指定的IPCKEY的值与其他系统的值冲突，可改变IPCKEY的值再试。
tmshutdown  关闭进程
参数同上，
区别参数：
-w    delay 立即挂起所有要关闭的server,并在过了delay秒之后马上关闭这些服务进程。系统将给这些服务进程发送SIGTERM信号，然后发送SIGKILL信号。
-k (TERM|KILL) 立即挂起所有要关闭的SERVER，系统将给这些服务进程先发送SIGTERM信号或发送
-R 只有在进行系统迁移时才用到，必须和-l或-g一起使用，关闭指定的服务进程，但不把它从BB中删除。
-c 管理BBL进程，即使现在有客户端与该TUXEDO应用系统连接
-p lmid 在lmid指定的机器上执行该命令，把该服务器从整个tuxedo应用系统中分离出去。如果该unix平台上TUXEDO应用服务器出了很严重的错误，无法正常管理该TUXEDO应用系统，可用下面的脚本把该tuxedo系统管理员所拥有的IPC资源全部清空，这样就可以把该TUXEDO应用系统关闭，名为rmipc的脚本内容如下?/P>
cipcrm `ipcs |grep $1|awk '{print "~" $1 " " $2 } ' `
如果TUXEDO系统管理员用户名为TUXEDO,则用下面的命令执行：
rmipc tuxedo
实例如下：ipckill.sh
if [ $# = "0" ]
then
USER=`logname`
else
USER=$1
fi
ipcrm `ipcs -s|grep $USER|awk '{print "-s" $2}'`
ipcrm `ipcs -m|grep $USER|awk '{print "-m" $2}'`
ipcrm `ipcs -q|grep $USER|awk '{print "-q" $2}'`
运行： ipckill  zhcx

tmadmin tmadmin是TUXEDO提供的一个命令行管理工具，可用它对TUXEDO应用系统进行监控、管理和动态修改配置等操作。
查询类命令：
psr 显示该系统所有server的信息
>psr
Prog Name      Queue Name  Grp Name      ID RqDone Load Done Current Service
---------      ----------  --------      -- ------ --------- ---------------
Q73001         00004.00200 GROUP4       200      0         0 (  IDLE )
BBL            170105                SITE1          0         1        50 (  IDLE )
WSL            00001.00005 GROUP1          5          0         0 (  IDLE )
信息含义：
RqDone:该SERVER当前已接受的请求数。
Load Done:RqDone*负载因子（负载因子的默认值为50）
CurrentServerce:当前正在处理客户端请求的SERVER，如果没有则为IDLE
 
Ø         help(h)              查看所能使用的管理命令
Ø         help(h)  command     查看指定命令的使用方法
Ø         default (d)          为其他命令设置默认参数
default  -m site1    将管理的对象设成site1 LMID
default –m *        解除缺省
Ø         dump(du) filename    将当前的Bulletin Board 下载到指定的文件
Ø         echo (e)             显示命令的输入行
Ø         pageinate(page)      按页显示命令输出
Ø         quit(q)              退出当前管理session
Ø         verbose(v)           将命令输出以详细信息格式显示
Ø         ! shlcmd             退出到shell执行特定的shell命令
Ø         !!                   重复前一个shell command
Ø         <RETURN>             回车重复上一次tmadmin命令
   
Ø         psr [-m machine] [-g groupname] [-i srvid] [-q qaddress]
-m  machine  LMID为 machine的所有服务进程
-g  groupname 组名为groupname的所有服务进程
-I srvid  SRVID为srvid的服务进程
-q qaddress 消息队列为qaddress的所有SERVERS
 
查看server的信息
Prog Name      Queue Name  Grp Name      ID RqDone Load Done Current Servic
BBL            123456      SITE1          0      0         0 (  IDLE )
WSL            00001.00001 GROUP1         1      0         0 (  IDLE )
A01100         00002.00011 GROUP2        11     46      2300 (  IDLE )
显示的结果包括:
l         Prog  Name  程序名
l         Queue Name  消息队列名,如果没有指定名称，则消息队列的名称的规则为“5为GRPNO.5位SRVID”，不足5位前补0。在SHM模式中，BBL的消息队列名是RESOUCES Section 的IPCKEY
的值。在MP模式，DBBL的消息队列名是RESOUCES Section 的IPCKEY的值。
l         Grp Name  SERVER所在的组
l         ID        SERVER的ID号
l         RqDone    SERVER 被调用的次数
l         Load Done  负载量(该SERVER的所有service的负载因子总和)
l         Current Service 当前正在被调用的service名称。如果当前没有service被调用，则为IDLE
 
Ø         psc [-m machine] [-g groupname] [-I srvid] [-q qaddress]
[-s service] [-a {0|1|2}]
        -s service 显示名为sevice的service信息
        -a {0|1|2} 显示系统的隐含的service
        其他参数与psr命令相同
查看service的信息
Service Name Routine Name Prog Name  Grp Name  ID    Machine  # Done Status
------------ ------------ ---------  --------  --    -------  ------ ------
A0110025     A0110025     A01100     GROUP2    11      SITE1       2 AVAIL
l         Service Name  :服务名
l         Routine Name  :函数名(采用TUXEDO服务的别名机制,一个函数可以对应多个服务名)
l         Prog Name     :service 所在的SERVER名
l         Grp Name      :组名
l         ID            ：server的ID号
l         Machine       :server所在的LMID
l         # Done        ：service被调用的次数
l         Status        :service的状态。AVAIL表示可用
 
Ø           bbstats(bbs)
  打印BB的统计信息
Current Bulletin Board Status:
          Current number of servers: 63
         Current number of services: 936
   Current number of request queues: 62
Current number of server groups: 12
 
Ø         printclient (pclt) [-m machine] [-u usrname] [-c cltname]
显示client端连接的情况
 -m machine    显示LMID号为machine上的客户端连接
 -u usrname    显示用户名为usename 的客户端连接
 -c ctlname    显示用户进程为ctlname的客户端连接
显示结果
  LMID         User Name       Client Name    Time    Status  Bgn/Cmmt/Abrt
------------ --------- --------------- -------- ------- -------------
SITE1           cpic            WSH             17:50:42 IDLE    0/0/0
SITE1           cpic            WSH             17:50:42 IDLE    0/0/0
SITE1           cpic            tmadmin          0:10:36 IDLE    0/0/0
l         LMID               逻辑机器名   
l         UerName            用户名
l         Client Name        客户进程名
l         Time               客户进程处在Staus的时间
l         Status            IDLE/BUSY
l         Bgn/Cmmt/Abrt     the num of transaction begun/commited/aborted
 
Ø         printqueue (pq) [qaddress]
显示消息队列的信息
qaddress 消息队列名称
Prog Name      Queue Name  # Serve Wk Queued  # Queued  Ave. Len    Machine
---------      ----------- ---------  --------  --------    -------
A00000         A00000_q        2         0         0       0.0      SITE1
输出结果说明:
l         Prog Name    :消息队列对应的可执行文件名
l         Queue Name   :消息队列名
l         #Serve       :连接到消息队列的SERVER数
l         Wk Queued    :消息队列的当前负载量
l         Queued       :消息队列的当前实际请求数
l         Ave.Len      :消息队列的平均长度
l         Machine      :逻辑机器名
 
Ø         printnet (pnw) [mach_list]
      site1                          Connected To:  msgs sent    msgs received
                                       site2         28               54
 
site2                          Connected To:  msgs sent    msgs received
site1         55               29
       打印当前系统的网络连接情况。
Ø          bbparms
打印BB的主要参数配置
Bulletin Board Parameters:
      MAXSERVERS: 150
     MAXSERVICES: 32000
    MAXACCESSERS: 160
          MAXGTT: 100
         MAXCONV: 64
      MAXBUFTYPE: 16
     MAXBUFSTYPE: 32
          IPCKEY: 123456
          MASTER: SITE1
           MODEL: SHM
           LDBAL: Y
        SCANUNIT: 10
      SANITYSCAN: 12
        DBBLWAIT: 2
        BBLQUERY: 30
       BLOCKTIME: 18
Shared Memory ID: 303
 
tmadmin 用来查看TUXEDO的运行情况。在tmadmin命令界面中可以使用如下命令：

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
psr
为printserver命令的简写，监控服务器运行情况，查看处理的请求数目、忙闲程度。
参数如下：
-m machine LMID为 machine的所有服务进程
-g groupname 组名为groupname的所有服务进程
-i srvid SRVID为srvid的服务进程
-q qaddress 消息队列为qaddress的所有SERVERS查看server的信息
> psr -i 15058
Prog Name Queue Name Grp Name ID RqDone Load Done Current Service
——— ———- ——– — —— ——— —————
RK016 00060.15058 CHGGRP_+ 15058 0 0 ( IDLE )
-i srvid SRVID为srvid的服务进程
#接续日志记录
RK016 SRVGRP=CHGGRP_SXBOSS SRVID=15058 CONV=N MIN=1 MAX=1
CLOPT=”-A -r -t -o /boss18/run/log/RK016.log”
结果说明:
列号 描述
1. 服务的可执行文件名
2. 服务连接的队列名
3. 组名
4. 服务的数字id
5. 服务已经处理的请求数(该SERVER的所有service的负载因子总和)
6. 服务处理的全部请求的参数和，如果当前没有service被调用，则为IDLE

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
psc
为printservice的简写，查看TUXEDO各服务的运行情况和处理的交易数。
psc [-m machine] [-g groupname] [-I srvid] [-q qaddress][-s service] [-a {0|1|2}]
-s service 显示名为sevice的service信息
-a {0|1|2} 显示系统的隐含的service
其他参数与psr命令相同
(2) 结果示例:
> psc -s sK005insert
Service Name Routine Name Prog Name Grp Name ID Machine # Done Status
———— ———— ——— ——– — ——- —— ——
sK005insert sK005insert RK005 CHGGR+ 15046 SXBOSS 33 AVAIL
(3) 结果说明:
列号 描述
1. Service Name :服务名
2. Routine Name :函数名(采用TUXEDO服务的别名机制,一个函数可以对应多个服务名)
3. Prog Name :service 所在的SERVER名
4. Grp Name :组名
5. ID ：server的ID号
6. Machine :server所在的LMID
7. # Done ：service被调用的次数
8. Status :service的状态。AVAIL表示可用

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
pq
查看队列信息
(1) 命令: printqueue 简写:pq [PADRESS]
(2) 结果示例:
pq 00004.05062
Prog Name Queue Name # Serve Wk Queued # Queued Ave. Len Machine
——— ———— —— ——— ——– ——– ——-
CCS_GEDAIPC_50 00004.05062 1 0 0 0.0 simple
(3) 结果说明:
列号 描述
1. Prog Name :队列连接的服务的可执行文件名
2. Queue Name :字符队列名，是RQADDR参数或一个随机值
3. #Serve :连接的服务数
4. Wk Queued :当前队列的所有请求的参数和
5. #Queued :实际请求数
6. Ave.Len :平均队列长度
7. Machine :队列所在机器的LMID

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
pclt
4查看客户端信息pclt
(1) 命令: printclient 简写:pclt
-m machine 显示LMID号为machine上的客户端连接
-u username 显示用户名为username 的客户端连接
-c ctlname 显示用户进程为ctlname的客户端连接
(2) 结果示例:
LMID User Name Client Name Time Status Bgn/Cmmt/Abrt
———- ————— ————— ——– ——- ————-
simple ccsmis WSH 17:42:47 IDLE 0/0/0
simple ccsmis tmadmin 0:44:28 IDLE 0/0/0
(3) 结果说明:
列号 描述
1. 已经登录的客户端机器的LMID
2. 用户名，由tpinit()提供的
3. 客户端名，由tpinit()提供的
4. 客户端连接后经过的时间
5. 客户端状态
6. IDLE——表示客户端目前没有任何交易在工作
7. IDLET——表示客户端启动了一个交易
8. BUSY——表示客户端在工作中
9. BUSYT——表示客户端正在交易控制下工作
10. 启动/提交/中断的交易数

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bbs
5查看部分统计信息bbs
(4) 命令: bbstats 简写：bbs
> bbs
Current Bulletin Board Status:
Current number of servers: 335
Current number of services: 2324
Current number of request queues: 27
Current number of server groups: 11
Current number of interfaces: 0

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
default
6观察某个节点的进程信息default
(5) 命令：default –m
> default -m SITE13
SITE13> psr
Prog Name Queue Name Grp Name ID RqDone Load Done Current Service
——— ———- ——– — —— ——— —————
BBL 30004.00000 SITE13 0 22827 1141350 ..ADJUNCTBB
BRIDGE 836437 SITE13 1 0 0 ( IDLE )
GWADM 00021.00019 BGWGRP1+ 19 0 0 ( IDLE )
GWTDOMAIN 00021.00020 BGWGRP1+ 20 123826 0
GWADM 00022.00021 BGWGRP2+ 21 0 0 ( IDLE )
GWTDOMAIN 00022.00022 BGWGRP2+ 22 0 0 ( IDLE )
GWADM 00025.00027 GWGRP1_+ 27 4 200 ( IDLE )

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
pnw
7查看消息发送状态pnw
(6) 命令：printnetwork 简写 pnw
> pnw SITE12
SITE12 Connected To: msgs sent msgs received
SITE14 61904 62319
SITE13 61890 62288
SITE11 15972 13564
 
 
 
修改了UBBCONFIG文件后，需要对该文件进行重新加载，tmloadcf命令即用来实现该功能。
tmloadcf命令接受以下4个参数：
-c 计算运行应用需要的IPC资源，该信息将提供给管理员，用于在各机器上配置资源。
-n 进行语法检查并不生成TUXCONFIG。
-b 控制TUXCONFIG占用的物理页数。
-y 无条件覆盖TUXCONFIG
 
 
 
 
tmshutdown命令用于关闭所有或部分应用并释放IPC资源。
本命令所有参数与tmboot类似（如：-A，-g，-i，-s，-S），意义相同。
tmshutdown的特殊参数有：
-c
当有客户端正在连接时，tmshutdown不能关闭管理服务。参数-c则可以超越次规则。该参数仅用于管理员需要立即关机而又无法及时通知客户端时。
-P
在非主控节点上，可以用-P参数仅关闭该机器上的应用。
示例：
tmboot -s s1104Cfm;
s1104Cfm为服务名。

tmboot命令启动TUXEDO系统的应用，创建必要的IPC资源、启动相关机器的规定的系统和应用服务进程。
tm的主要参数有：
-A 启动所有机器上的管理进程。
-M 启动主控机器上的管理进程。
-i srvid 启动服务id等于srvid的进程。
-g grpname 启动指定的一组服务（含TMS）。
-S 启动所有应用服务。
-s server-name 启动可执行文件名为server-name的服务。
-e 打印本配置所需要的最少的IPC资源。
示例：
tmboot -s s1104Cfm;
s1104Cfm为服务名。


TUXEDO函数说明：
1 与缓冲区使用有关的ATMI
1.1 tpalloc.
1.2 tprealloc.
1.3 tpfree.
1.4 tptypes.
2 常用的FML(FML32)操作函数
2.1 Falloc.
2.2 Finit
2.3 Fadd
2.4 Fchg
2.5 Fget
2.5 Fprint
2.6 Ferror
3连接的建立与断开有关的ATMI
3.1 tpchkauth.
3.2 tpinit
3.3 tpterm
4 与请求TUXEDO SERVER 有关的ATMI
4.1 tpcall
4.2 tpacall
4.3 tpgetrply
4.4 tpcancel
4.5 tpgprio
4.6 tpsprio
5 与请求错误处理有关的ATMI
5.1 tpstrerror
5.2 tperrordetail
5.3 tpstrerrordetail
 
 
1 与缓冲区使用有关的ATMI
1.1 tpalloc
char * tpalloc(char *type, char *subtype, long size)
描述:分配缓冲区
参数:type:缓冲区的类型
    subtype:缓冲区的子类型,只有VIEW有子类型,其他的缓冲区该参数要设为NULL
    long:缓冲区的大小
返回值: 成功返回一个指向所分配空间首地址的CHAR *形指针,失败返回NULL。
1.2 tprealloc
char * tprealloc(char *ptr, long size)
描述:重新分配缓冲区
参数:ptr:指向原缓冲区首地址的指针
    size:新缓冲区的大小
返回值: 成功返回一个指向新分配空间首地址的CHAR *形指针,失败返回NULL。
1.3 tpfree
void tpfree(char *bufptr)
描述:释放由TPALLOC()或TPREALLOC()分配的缓冲区
参数:bufptr:指向要释放的缓冲区首地址的指针
返回值:无
注意: 用TPALLOC(),TPREALLOC()分配的内存只能有TPFREE()释放掉,不能用FREE()
1.4 tptypes
long tptypes(char *ptr, char *type, char *subtype)
描述:返回有ptr所指向的缓冲区的类型及子类型
参数: ptr:指向要进行类型识别的缓冲区首地址的指针
type：类型名
subtype：子类型名（只对VIEW类型有效）
返回值:0成功，-1失败, 错误号保存在全局变量tperrno中。
 
2 常用的FML(FML32)操作函数
2.1 Falloc
FBFR*  Falloc (FLDOCC F, FLDLEN V)
描述： 分配一块FML缓冲区
参数：
    FLDOCC: 该FML缓冲区的字段个数,
    FLDLEN: 该FML缓冲区的长度
返回值：成功返回一个指向该FML缓冲区首地址的指针,失败返回NULL，错误号保存在全局
变量Ferror中
注意:   该FML缓冲区不能用于TPCALL(),TPACALL(),TPRETURN()等中,在这些函数中用到
的FML缓冲区只能用TPALLOC()分配。
2.2 Finit
int Finit(FBFR *fbfr, FLDLEN buflen)
描述： 初始化该FML缓冲区
参数：
   fbfr: 一个指向该FML缓冲区首地址的指针
   buflen: 该FML缓冲区的长度
返回值：失败为-1, 错误号保存在全局变量Ferror中
2.3 Fadd
int Fadd(FBFR *fbfr, FLDID fieldid, char *value, FLDLEN len)
 
描述： 往FML缓冲区fbfr中ID为fieldid的字段增加一个值value
参数：
fbfr:    指向该FML缓冲区首地址的指针
fieldid: 要增加的字段的ID
value:   要增加的值,如果时其他类型的要转化为char *
len:     该字段的长度,如果不时CARRARY类型的,可设为0
返回值： 失败为-1, 错误号保存在全局变量Ferror中
2.4 Fchg
int Fchg(FBFR *fbfr, FLDID fieldid,int occ, char *value, FLDLEN len)
描述：   改变fbfr中ID为fieldid字段的值。
参数：
fbfr:    指向该FML缓冲区首地址的指针
fieldid: 要增加的字段的ID
value:   该字段的新值,如果时其他类型的要转化为char *
len:     该字段的长度,如果不时CARRARY类型的,可设为0
返回值：失败为-1，错误号保存在全局变量Ferror中
2.5 Fget
int Fget(FBFR *fbfr, FLDID fieldid,int occ, char *value, FLDLEN *maxlen)
描述：   从fbfr缓冲区中取ID为fieldid字段的值到value中。
参数：
fbfr:    指向该FML缓冲区首地址的指针
fieldid: 字段的ID
value:   取出的值保存到该指针指向的地址中
maxlen:  可以COPY到缓冲区value中的字符串的长度,返回值为真正COPY到该缓冲区的字符串的长度
返回值：失败为-1, 错误号保存在全局变量Ferror中
2.5 Fprint
Fprint(FBFR *fbfr)
描述： 按格式打印fbfr缓冲区的内容。一般用于程序调试中。
参数：
fbfr:    指向该FML缓冲区首地址的指针
返回值：失败为-1, 错误号保存在全局变量Ferror中
2.6 Ferror
Ferror：
和C语言中的errno类似，当调用FML（FML32）函数出错时，把错误号保存在全局变量Ferror中。
char *  Fstrerror(int err)
描述：返回错误号为err的错误描述
参数：err: Ferror的值
返回值：成功返回错误描述，失败返回NULL
 
 
3 连接的建立与断开有关的ATMI
3.1 tpchkauth
int tpchkauth()
描述: 检查该TUXEDO SERVER所采用的安全方式
参数:无
返回值:
      TPNOAUTH:不需要认证
      TPSYSAUTH:需要口令认证
      TPAPPSUTH:需要口令认证,并且还需要应用级的认证或授权.
      -1:调用失败, 错误号保存在全局变量tperrno中。
3.2 tpinit
int tpinit(TPINIT *tpinfo)
描述: 与TUXEDO SERVER建立连接
参数:TPINFO
返回值: 失败返回-1, 错误号保存在全局变量tperrno中。
 
TPINIT结构体在atmi.h中的定义如下
struct  tpinfo_t {
    char    usrname[MAXTIDENT+2];   /* client user name */
    char    cltname[MAXTIDENT+2];   /* application client name */
    char    passwd[MAXTIDENT+2];    /* application password */
    char    grpname[MAXTIDENT+2];   /* client group name */
    long    flags;          /* initialization flags */
    long    datalen;        /* length of app specific data */
    long    data;           /* placeholder for app data */
};
typedef struct  tpinfo_t TPINIT;
说明:username,cltname,passwd,grpname,data,datalen用于安全认证中
flags:用于定义以何种方式通知该客户端一个UNSOLICTED MESSAGE的到来.它的值可以为:
TPU-SIG
TPU-DIP
TPU-IGN
TPSA-FASTPATH
TPSA-PROTECTED
3.3 tpterm
int tpterm()
描述: 断开与TUXEDO SERVER建立连接
参数:无
返回值: 失败返回-1, 错误号保存在全局变量tperrno中。
 
4 与请求TUXEDO SERVER 有关的ATMI
4.1 tpcall
int tpcall(char *svc, char *idata, long ilen, char **odata, long   *olen, long flags)
描述：客户端同步调用服务端的名为svc的SERVICE，
参数：
*svc：SERVICE的名称
char *idata： 输入缓冲区的地址，客户端传给服务端的参数放在该缓冲区内
long ilen：   输入缓冲区的长度
char **odata  输出缓冲区的地址，服务端传给客户端的结果放在该缓冲区内
long   *olen：输出缓冲区的长度  
long flags：  调用标志，由以下几个：
TPNOTRAN
如果调用svc的客户端当前在TRANSACTION方式下，那么svc不参与当前的TRANSACTION。
 
TPNOCHANGE
如果服务端返回的缓冲区类型与客户端定义的缓冲区(odata)类型不一致，默认情况下，odata会转换成与服务端返回的缓冲区类型一致的类型，如果设置了该FLAG，那么当出现这种情况时，不进行缓冲区类型转换，并且会保错。
 
TPNOBLOCK
默认情况下,如果客户端有阻塞条件存在（如CLIENT的TCP/IP中的缓冲区满,磁盘I/O忙等），那么客户端会阻塞在那里，直到阻塞消除或超时出错。如果设置了TPNOBLOCK,当客户端有阻塞条件存在时,TPCALL()会立刻返回并报错. 注意TPNOBLOCK只对发送请求时起作用,如果在接收服务端返回的结果时有阻塞条件存在,客户端会在那里等待,直到阻塞消除或超时出错
 
TPNOTIME
如果客户端有阻塞条件存在，客户端会一直阻塞在那里，即使到了超时时间也不返回，但如果该客户端是在TRANSACTION模式下，当到了
事务的超时时间，还是会报超时错误并返回。
 
TPSIGRSTRT
如果在进行系统调用时，被信号中断，该系统调用会重新进行。
 
调用成功返回0,失败返回-1, 错误号保存在全局变量tperrno中。
 
4.2 tpacall
int tpacall(char *svc, char *data, long len, long flags)
描述:  客户端异步调用服务端的名为svc的SERVICE,不等服务端返回结果,程序可继续往
下走,在某个地方调用tpgetrply()取的服务端的返回
参数:
char *svc, char *data, long len参数的含义与tpcall()中的一样
flags 可设置为：TPNOTRAN, TPNOREPLY, TPNOBLOCKTPNOTIME, TPSIGRSTRT.
TPNOTRAN, TPNOBLOCKTPNOTIME, TPSIGRSTRT的含义与与tpcall()中的一样
TPNOREPLY：调用tpacall（）的客户端不想接收SEVER端的应答。如果设置了
TPNOREPLY：服务端不会给该客户端发送应答。
返回值: 失败返回-1，成功返回一个HANDLER，可作为tpgetrply的参数，用于取应答
4.3 tpgetrply
int tpgetrply(int *cd, char **data, long *len, long flags)
描述:取出服务端对tpacall（）的应答。
参数: cd tpacall（）返回的HANDLER
char **data返回缓冲区的地址，服务端传给客户端的结果放在该缓冲区内
long   *len：返回缓冲区的长度
flags：可以是：TPNOBLOCK, TPNOTIME,TPSIGRSTRT，TPGETANY(不管cd的值,从服务
器的应答队列中取第一个可用的消息)，TPNOCHANGE
返回值: 失败返回-1，错误号保存在全局变量tperrno中。
 
4.4 tpcancel
int tpcancel(int handle)
描述: 如果当前的程序不处于事务模式中,取消对tpacall（）的应答, 如果处于事务模式
中,则不能取消对tpacall（）的应答,该调用会失败.
参数: tpacall（）返回的HANDLER
返回值: 失败返回-1，错误号保存在全局变量tperrno中。
4.5 tpgprio
int tpgprio()
描述:返回最近发送(tpcall(),tpacall())或接收(tpgetrply())的一个消息的优先级
参数:无
返回值: 1-100消息的优先级,值越高, 优先级越高
        失败返回-1, 错误号保存在全局变量tperrno中。
 
struct {
int hdl; /* handle*/
int pr; /* priority*/
} pa[SIZE];
for (i=0; i
/* Determine service and data for request */
pa [i].hdl = tpacall(Svc, buf, len, flags);
/* Save priority used to send request */
pa[i].pr = tpgprio();
}
/* Use qsort(3) routine to sort handles in priority order */
qsort((char*) pa, requests, sizeof(pa[0]), cmpfcn);
for (i=0; i< requests; i++) {
tpgetrply(&pa[i].hdl, &rbufp, &rlen, rflags);
}
 
4.6 tpsprio
int tpsprio (int prio, long flags)
描述: 设置下一个要发送的消息的优先级
参数: 0- prio为相对值, 设置下一个要发送的消息的优先级为现在的优先级加上prio
     TPABSOLUTE: prio为绝对值, 设置下一个要发送的消息的优先级为prio
返回值: 失败返回-1，错误号保存在全局变量tperrno中。
 
 
5 与请求错误处理有关的ATMI
5.1 tpstrerror
char *tpstrerror(int tperrno)
描述:返回错误号为tperrno的错误描述
参数: tperrno:在atmi.h中定义的全局变量,用于标识错误号,类似于C中的errno
返回值: 失败返回NULL,成功返回错误号为tperrno的错误描述.
5.2 tperrordetail
int tperrordetail(long flags)
描述: 返回当前进程或线程最近调用ATMI的出错的更详细的描述
参数:设为0
返回值: 如果没有错误返回0,有错误返回错误描述号
 
5.3 tpstrerrordetail
char * tpstrerrordetail(int err, long flags)
描述: 返回错误描述号err的详细描述信息
参数:
err : tperrordetail()的返回值,
flags: 设为0
返回值: 失败返回NULL,成功返回详细描述信息

Tuxedo服务启动时，执行tpsvrinit()函数，可以打开一些如数据库之类的资源供以后使用
Tuxedo服务停止时，执行tpsvrdown()函数，关闭资源
服务程序调用tpreturn()函数来结束服务请求，并返回一个缓冲区，必要时，将它传给客户程序。

Tuxedo在客户机和服务器通信中大量使用UNIX系统的消息队列。
  SSSO(Single Server Single Queue)模式：每个客户机都有一个响应队列来接受客户端请求。
  MSSO(Multiple Server Single Queue)模式：多个服务器共享同一个请求队列。

Tuxedo使用共享内存存储公告牌，用来公告进程状态信息和需要在进程间共享或传递的数据。 BBL

一些名词解释：
WSC: Workstation Client 调用服务的客户端
WSL: Workstation Listener TUXEDO系统自带的一个SERVER，它侦听一个指定的端口，WSC最初与该SERVER建立连接
WSH: Workstation Handler TUXEDO系统自带的一个SERVER，由它处理WSC与TUXEDO SERVER之间的通讯。

Workstation Client与TUXEDO SERVER建立连接的过程为：
1．    WSC 调用tpinit()或tpchkauth()
2．    WSC采用在WSNADDR中指定的IP地址与服务端的WSL建立连接
3．    WSL为该WSC指定一个WSH，并把该WSH的侦听端口返回给WSC
4．    WSC采用返回的端口与指定的WSH建立连接，并与WSL断开连接，这之后WSC与TUXEDO SERVER之间的通讯通过WSH进行处理，与WSL无关。
5．    tpinit()或tpchkauth()调用返回。


UBBCONFIG文件的定义
一个tuxedo应用系统的所有资源都在一个文本文件中定义，该文件被称为UBBCONFIG。在配置完成后，UBBCONFIG被编译成一个二进制的文件：TUXCONFIG。在tuxedo系统启动时，会从该文件中读取系统的配置信息。UBBCONFIG文件类似Windows下的*.ini文件。

UBBCONFIG文件的组成
UBBCONFIG包括以下8部分，我们称之为节。

RESOURCE(必须) --> 与整个系统有关的配置信息。
MACHINES（必须） --> 逻辑机器; 一个tuxedo应用系统可以跨越多台服务器，在该节中配置与每台服务器有关的信息。
GROUPS（必须） --> 服务器组; tuxedo中规定而服务可以被分为多个组，在该节中配置与组有关的信息。
SERVERS（可选） --> 服务进程; 与server有关的信息在该节中配置。
SERVICES（可选） --> 服务; 与service有关的信息在该节中配置。
NETWORK（可选） --> 与网络有关的信息在该节中配置。
ROUTING（可选） --> 路由规则在该节中配置。
NETGROUPS（可选） --> 与网络分组有关的信息在该节中配置。

*RESOURCES节点   
    IPCKEY 共享内存id   
    UID TUXEDO管理员用户id   
    GID TUXEDO管理员组id   
    PERM TUXEDO管理员组用户的权限 ，如 0660   
    MAXACCESSERS 服务端和客户端的最大进程数   
    MAXSERVERS 限制可以启动服务总数   
    MAXSERVICES 限制可以发布交易总数   
    MASTER 指出主控节点的逻辑名，第二个是备份节点   
    MODEL 应用构架，SHM表示单机，MP表示多机   
    OPTIONS LAN，MIGRATE表示是一个网络应用，服务可以移植到替代处理器上   
    SECURITY 安全级别(5个);
    AUTHSVC 客户端可以通过交易"AUTHSVC"获得认证;
    NOTIFY DIPIN，客户端通过dip-in收到广播通知;  
    SYSTEM_ACCESS PROTECTED，NO_OVERRIDE，应用代码不得干扰共享内存   
    LDBAL 设Y则进行负载均衡   
    MAXBUF[S]TYPE 数据缓冲类型及子类的最大数   
    SCANUNIT 内部时间间隔单位，单位是秒   
    SANITYSCAN 检索公告牌的内部时间间隔，单位是SCANUNIT  （健康检查参数） 
    BLOCKTIME 交易超时时间，单位是SCANUNIT   
    BBLQUERY DBBL查询所有BLL的时间间隔   
    DBBLWAIT DBBL等待BBL回应的超时时间   
    MAXCONV 同时最大会话数
*MACHINES MACHINES节点   
    vctest2 物理处理器名，可以通过"uname -n"得到节点名称
    TUXDIR TUXEDO系统软件安装位置， 如 /home/hdp/tuxedo/tuxedo11gR1   
    APPDIR 应用服务位置全路径  , 如 /home/hdp/bin 
    TUXCONFIG 二进制文件(ubb)配置文件全路径   
    ENVFILE 环境文件全路径   
    ULOGPFX 应用日志文件全路径   
    MAXACCESSERS 本机最多处理器数，可以超越*RESOURCES节定义   
    MAXCONV 本机最大会话数，可以超越*RESOURCES节定义   
 *GROUPS GROUP节点   
    BANKB1      组的唯一标识符，可以是字母数字   
    GRPNO       组的唯一数字标识符   
    LMID        组所在的机器   
 *SERVERS SERVER节点，列出所有服务程序   
    DEFAULT:        本处列出的参数为其下列出的服务的缺省值，但可以被单列条目替代相应值   
    RESTART         如果设成Y，则服务可以重启动   
    MAXGEN          在GRACE定义时间之内，服务可以重启动MAXGEN次   
    GRACE           周期，单位是秒   
    RCMD            每次服务重启动，本处定义的脚本或命令被执行   
    ENVFILE         列有环境变量的文件，在交易启动前设入环境   
    TLR             一个服务名，用buildserver建立，应在APPDIR或$TUXDIR/bin   
    SRVGRP          服务属于一个在*GROUPS节中定义的服务组；如果需要移植服务，也可以定义在多个组中。   
    SRVID           服务组中代表服务的唯一值   
    MIN             最少在启动时启动的服务数   
    MAX             运行时，最多可以起的实例数   
    CLOPT           跟随服务启动的其他参数   
        -A 服务内建交易全发布   
        -r 指定服务记录时间戳，用于以后计算交易处理时间   
        -e 定义标准错误重定向文件   
        -o 定义标准输出重定向文件  
        -t tuxedo允许一个client连接的时间多长，指连接的动作，不是连接后的持续时间，如果你用tuxedo6.5的client去连tuxedo7, 则必须要写此参数(确认？) 
        -T 客户端超时
        -n WSL 网络连接参数，客户端可以按照这个设置
        -c 每个客户端或者处理程序所用的压缩阈值  
        -m 服务器起来之后的最小常连接 
        -M 最大常连接，默认值是UBB中的MAXWSCLIENTS的数量
        -x 服务器一次处理的最大客户端数量，必须大于0，默认值是10， -x 10 可以理解为WSH的请求缓存区可以10个请求
            （he value for this parameter indicates the number of Workstation clients that can be supported simultaneously by each workstation handler.
             The workstation listener ensures that new handlers are started as necessary to handle new Workstation clients. This value must be greater than or equal to 1 and less than or equal to 4096.
             The default for this parameter is 10.）
        -T 定义客户端会话超时，单位以分钟， 如果超过这个时间客户没有请求到服务器，WSH会自动断开与其连接，最后返回到WSH Pool中
        -- TUXEDO参数和服务特定参数的分隔符   
        … 传给tpsvrinit()的参数   
    SYSTEM_ACCESS 设定后，应用错误不干扰公告牌   
    RQADDR 当设定此项后，所有本服务的实例都使用相同的请求队列。这是在应用中设置MSSQ（Multiple Server Single Queue）的方便办法，可以改善处理流量。任何时候，所有MSSQ集中的实例发布相同的交易集。   
    XFER 另一个服务   
    REPLYQ 设成Y，则服务又作为一个MSSQ集配置，任何其中的交易调用其他交易，就建立一个单独的回应队列。
 *SERVICES 交易节点   
    # 注释行符号   
    大写字母 交易名，由应用服务提供   
    BUFTYPE 任何向该交易的请求，数据应该是此处定义类型   
    GROUP 交易所在服务所在的组   
    LOAD 负载因子，表示处理请求的时间，用于计算负载平衡   
    PRIO 优先级

注意：
一旦配置WSL， 需要指出连接的WSCLINET连接数大于0
MAXACCESSERS > MAXWSCLIENTS + MAXSERVERS

tuxedo wsl 负载均衡 unix 下的配置  
WSNADDR=//128.192.109.50:6830  多个地址的方式是：export WSNADDR='(//128.192.109.50:6830|//128.192.109.51:6830)'; 注意这里需要单引号!!

Domain是在Tuxedo的架构中，可以共同负载均衡，迁移，备份等功能的一组机器，勿要同Group混淆。 

一个tuxedo应用只能有一个DMADM，可以在任何一个组中
一个tuxedo应用可以有多个GWADM---GWTDOMAIN对,一个组只能有一个GMADM----GWTDOMAIN对,

tuxedo 几个重要的进程：
比较重要的进程为
1、BBL(Bulletin Board Liaison)，主要对公告板等进行管理，包含了一个公告牌的本地拷贝和本地服务器上应用的状态。
    Bulletin Board（BB，公告板）：Tuxedo把系统的配置信息保存在一个共享内存中，该共享内存称为公告板。
2、DBBL(Distinguished Bulletin Board Liaison)，TUXEDO用于多服务器配置各个服务器之间的协调工作，只有当TUXEDO配置为MP方式时才需要用到DBBL 。
    DBBL与BBL协同，保证所有的公告牌内容的一致性。
3、WSL：WorkStation Listener，Tuxedo系统自带的一个Server，它侦听一个指定的端口，WSC最初与该Server建立连接。
    注意： 只有在远程客户端与服务进行通信才配置的，而如果客户端使用本地客户端则使用IPC连接
4、WSH：WorkStation Handler Server ，Tuxedo系统自带的一个Server，由它处理WSC与Tuxedo Server之间的通信。
5、BRIDGE，不同的服务器之间通过BRIDGE进程进行通讯，该BRIDGE的侦听IP地址及端口 在NADDR中指定。如果是在UNIX下要指定该BRIDGE所用的网络设备，如果是在NT下则不要。
6、DMADM，域间通信的进程：管理域的server,在运行时管理BDMCONFIG,对已登记的gateway group提供支持,在tuxedo系统中,只能有一个DMADM进程,且不能对它采用MSSQ,不能有REPLYQ
7、GWADM，管理DOMAIN的域网关进程（在/DOMAIN中是GWTDOMAIN）的SERVER，在运行时可以对某一组域网关 （Domain Gateway Group）进行管理。主要从DMADM那里取得域的配置信息,并对域网管进程及跨越域的全局事务的LOG文件进行管理
8、GWTDOMAIN，处理DOMAIN之间的互操作,使本地域和调用远程域可以互相调用彼此的service,其中GMADM和GWTDOMAIN必须 在一个组中,一个tuxedo应用可以有多个 GWADM,GWTDOMAIN对,一个组只能 有一个GMADM,GWTDOMAIN对,但一个tuxedo应用只能有 一个DMADM, DMADM可以在任何一个组中,一个本地域可以和多个 远程域实现互操作。
9、tlisten，是TUXEDO自带的管理程序，在MP模式下，完成主机之间的初始化通讯，如非MASTER机从MASTER机中下载tuxconfig配置文件。
tlisten的启动办法:tlisten –l //NLSADDR


WSH 进程与 Server进程的关系：
WSH接受WTC的请求数据， 放在缓冲区，然后发送给Server进程处理，因为在同一台机器上，一般采用本地进程间通信机制，效率比较高，Server处理完后返回给WSH，这个
过程中WSH与WTC是TCP连接着的，而Server过程并不是直接和WSC连通的，正真处理client的是Server进程，所有业务和数据库相关操作都是在Server进程完成的。

WSC连接步骤：
Step1：
            tpinit() / tpchkauth()
    WSC  -------------------------------------->  WSL
        <---------------------------------------
            return address of WSH

Step2:
            return address of WSH
    WSC  <-------------------------------------- WSL ---------> WSH
                                                
Step3:
            send reques with data 
    WSC  --------------------------------------> WSH
         <-------------------------------------
            return result set

远程客户端配置与开发：
环境变量配置：
    WSNADDR=//IP:PORT 与Server保持一致

在tpinit()函数前添加一行代码：
    tuxputenv("WSNADDR=//IP:PORT")

编译客户端程序时：
    buildclient -f client.c -o client -w

java客户端使用WTC， JOLT连接Tuxedo

实例使用：
编译流程：

错误信息：
1： CMDTUX_CAT:873: ERROR: TUXCONFIG environment variable not set
    则需要配置TUXCONFIG环境变量， export TUXCONFIG=指向config编译的位置

0.关闭tuxedo服务
tmshutdown -y

1.修改配置文件，重新加载
tmloadcf -y ubbsimple
 

2.编译服务程序，（可以放到makefile里面，或者一个脚本里面）
-s后面写的是对应的服务名
buildserver -o aslan -f simpserv.c -s TOUPPER -s TOLOWER -s HELLOWORLD

3.编译client程序
buildclient -o myfirst -f myfirst.c

4.启动tuxedo服务
tmboot -y 

5.执行client程序查看效果
./myfirst hello world

为WTC配置TUXEDO配置文件domconfig:


BDMCONFIG: DOM 节点的配置
一般是domXXX(服务跨节点使用)
DMCONFIG 文件的配置：

*DM_RESOURCES： 全局域配置信息，只有一个参数VERSION=vesions1_1; 可以用它定义配置文件版本; VERSION=vesions1_1
*DM_LOCAL:      *DM_LOCAL_DOMAINS: 定义本地网关访问点
*DM_REMOTE:     *DM_REMOTE_DOMAINS
*DM_REMOTE_DOMAINS: 定义远程网关访问点，一个本地网关访问点，必须有一个远程网关访问点与之对应
*DM_TDOMAIN: 为本地网关访问点和远程网关访问点指定监听地址和端口。远程网关通过本地网关的监听地址来建立连接和发送请求，本地网关通过远程连接到远程网关的监听地址上去发服务请求
*DM_ACCESS_CONTROL: 用于控制哪些远程域可以请求本地服务
*DM_EXPORT    别名 *DM_LOCAL_SERVICES
*DM_IMPORT    别名 *DM_REMOTE_SERVICES
