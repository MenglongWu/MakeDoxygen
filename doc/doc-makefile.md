Makefile都有些什么
==================

  - __make menuconfig__

  配置工程，编辑 [Kconfig] 修改工程配置选项
  ![](./image/menuconfig.png)

  - __make__

  编译默认子工程

  默认子工程是listprj.mk中 __DP__ 所指向的工程，可以使用

  - __make DP=xxx__ 
  
  临时编译其他子工程

  - __make all__

  编译所有子工程，默认生成文件位于对应平台目录下，如release-x86 lib-x86

  所有工程指的是 [allprj.mk](./doc-allprj.md) 中 __PRJS-y__ 所对应的工程集合。


  - __make strip__

  执行strip去掉所有子工程的ELF格式文件标签

  - __make copy__

  - __COPY_DIR__
拷贝所有子工程到指定目录，该目录通常是tftp/NFS等网络共享目录，用存放目标板平台的交叉编译程序

  - __make clean__

清除所有子工程生成文件

  - __make distclean__

清除所有子工程生成文件，如果对应平台已经清空，则同时删除平台目录。

  - __make run__

本地运行总工程下的默认输出文件。通常只有 x86 平台下才可能执行该命令。
如默认执行工程 **pi1** 所生成的download.elf文件，工程配置相对目录 **script/default** ，生成elf格式文件，elf文件命名为 **download.elf**

script/listprj.mk

```
    pi1=script/default
        pi1_arg=elf
export DP=pi1
```

script/default/project.mk

```
OUTPUT_ELF  = download.elf
```

默认输出如下内容:  
对于工程里的几个宏来历查阅 [工程预定义宏](#prj_macro)

```
$ make run
./release-x86/default.elf
Macro:
        ARCH      x86
        PRJ_NAME      [default-project]
        PRJ_VERSION    1
        PRJ_PATCHLEVEL 0
        PRJ_SUBLEVEL   0
        BUILD_DATE    May 10 2017 21:42:36
asin(1) = 1.570796
test lafun1():  1. I'm fun1() from libla.so
test lbfun1():  1. I'm fun1() from libla.so
```
  - __make se__
 
show eror 高亮显示编译error

  - __make sw__

show warning 高亮显示编译warning

  - __make lp__

列出所有子工程，其中DP指向默认工程配置目录

```
root@UbuntuServer:MakeDoxygen$ make lp
    pi1=script/default
        pi1_arg=elf
    pi2=script/prj_liba
        pi2_arg=mlib
    pi3=script/prj_libb
        pi3_arg=mlib
DP=pi1
```

  - __make ep DP=pi1__

同时打开并编辑pi1子工程目录下两个配置脚本project.mk,filelist.mk

![image](./image/ep.png)

  - __make gdb DP=pi1__

以gdb调试方式运行子工程pi1的输出文件，条件需要在工程配置脚本 [project.mk] 打开 "-g" 选项

  - __make gdb-core__

打开core输出文件调试程序


  - make print_env

  仅仅为了调试Makefile，输出各环境变量

```
root@UbuntuServer:MakeDoxygen# make print_env 
=========================================================
PRJ_VERSION   = 1.0.0
PRJ_NAME      = [Project Name]

file_common   = /mnt/linuxProject/MakeDoxygen/script/common.mk
file_prj      = /mnt/linuxProject/MakeDoxygen/script/project.mk
file_config   = ./script/.config
file_list     = /mnt/linuxProject/MakeDoxygen/script/filelist.mk
file_lds      = ========== no such file ./script/boot.lds

CROSS_COMPILE =
CC            = gcc
LD            = ld
OBJDUMP       = objdump
OBJCOPY       = objcopy

OUTPUT_ELF    = helloworld.elf
OUTPUT_DIS    = download.dis
OUTPUT_BIN    = download.bin
OUTPUT_SO     = download.so
OUTPUT_A      = download.a
OUTPUT_DIR    = release

INCLUDE_DIR   = -I./
LFLAGS        = -lm
LIB_DIR       = -L/usr/local/install/lib
CFLAGS        = -DTARGET_X86 -DBUILD_DATE="2015-10-19 15:09:22" -DPRJ_VERSION="1.0.0" -DPRJ_NAME="[Project Name]" -g -Wall -static -rdynamic
```

  - __make a+xxx__

  几乎以上带有 **所有子工程** 含义的目标（除make all外），在目标前加入 **a**   即可只对当前默认工程执行操作。

    - make astrip
    - make acopy
    - make aclean
    - make distclean

  - __make cpplintconfig__
  
  设置cpplint语法检查规则