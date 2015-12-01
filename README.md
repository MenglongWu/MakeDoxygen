#MakeDoxygen
It's a project templet, include **Makefile temple** and **Doxygen templet**.

##How to use/怎么使用


1. **make disclean**

```
root@fnc:MakeDoxygen# make disclean 
```
1. **make configure**

```
root@fnc:MakeDoxygen# make configure 
echo ./script/config.mk include/autoconfig.h "[default-project]"
./script/config.mk include/autoconfig.h [default-project]
read config file :./script/config.mk
make header file :include/autoconfig.h
```

1. **make allp** make all project

```
root@fnc:MakeDoxygen# make allp
make DP=pi2
make[1]: Entering directory `/mnt/linuxProject/MakeDoxygen'
    ARCH       [x86]
    create     lib-x86/libla.so
    create     lib-x86/libla.a
make[1]: Leaving directory `/mnt/linuxProject/MakeDoxygen'
make DP=pi3
make[1]: Entering directory `/mnt/linuxProject/MakeDoxygen'
    ARCH       [x86]
    create     lib-x86/liblb.so
    create     lib-x86/liblb.a
make[1]: Leaving directory `/mnt/linuxProject/MakeDoxygen'
make DP=pi1
make[1]: Entering directory `/mnt/linuxProject/MakeDoxygen'
    ARCH       [x86]
    compile    src/smain.c
    create     release-x86/default.elf
    create     release-x86/download.bin
make[1]: Leaving directory `/mnt/linuxProject/MakeDoxygen'
```

1. **make run** run default project output target

```
root@fnc:MakeDoxygen# make run
./release-x86/default.elf
Macro:
        PRJ_NAME      [default-project]
        PRJ_VERSION    1
        PRJ_PATCHLEVEL 0
        PRJ_SUBLEVEL   0
        BUILD_DATE    2015-12-01_16:19:25
asin(1) = 1.570796
test lafun1():  I'm fun1() from libla.so
test lafun2():  I'm fun2() from libla.so
test lbfun1():  I'm fun1() from liblb.so
```

##explain/解释
* make configure

默认执行 **mkheader ./script/.config include/autoconfig.h "[Project Name]"**

默认读取 **script/.config** 配置文件生成 **include/autoconfig.h** 头文件，最后一个参数是工程名，.config的格式与Linux Kernel 里的.config相同。转换过程需要工具 **mkheader**,该工具位于tool目录下，将其拷贝到cp ./tool/mkheader /bin/mkheader。

**获取 mkheader**

git clone https://github.com/MenglongWu/mkheader.git

** 运行实例 ** 

```
root@fnc:MakeDoxygen# make configure 
read config file :./script/./config
make header file :include/autoconfig.h
root@fnc:MakeDoxygen# ls ./include/
autoconfig.h
```

```
root@fnc:MakeDoxygen# cat script/.config 
CONFIG_KERNEL = y
# CONFIG_DEBUG = y
CONFIG_DEV_COUNT = 8
CONFIG_FILE_SYSTEM = n
CONFIG_NFS_PATH = "/mnt/nfs"

```

```
root@fnc:MakeDoxygen# cat include/autoconfig.h 
/*
 * Automatically generated C config: don't edit
 * Project "[Project Name]" Configuration
 * Depand on ./script/.config
 */
#ifndef _AUTO_CONFIG_H_
#define _AUTO_CONFIG_H_

#define CONFIG_KERNEL                                           1
#define CONFIG_DEV_COUNT                                        8
#define CONFIG_NFS_PATH                                         "/mnt/nfs"

#endif
```



* make all

生成 *.elf 目标文件

* make library

生成 *.so\*.a 目标文件

* make print_env


仅仅为了调试Makefile，输出各环境变量


```
root@fnc:MakeDoxygen# make print_env 
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

---

## Environment/环境变量
* file_prj - 定义工程配置文件，默认script/project.mk
* file_common - 定义公共环境变量文件，用于子工程里使用相同宏，包括CFLAGS，LDFLAGS等 

##Directory/目录结构
* doxygen - 
* dowx


##Context/联系
**Email:**MenglongWoo@aliyun.com

##Download/下载模板
git clone https://github.com/MenglongWu/MakeDoxygen.git


fsdf[sdf](operator)
[[]: operator](operator)
# []: operator
_jfl_jliw **dfe**
sd

## KnowBug/
gcc-4.3.2不支持带空格的宏，如下所示，更换 >4.4.1 版本gcc支持
```
Error
PRJ_NAME = "[Project Name]"
Replace
PRJ_NAME = "[Project-Name]"
```

![image](http://img-storage.qiniudn.com/15-10-21/68367498.jpg) 
![imageass](image/af.bmp)
[点击跳转](#KnowBug/)
