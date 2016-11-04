# Makedoxygen 组织结构

<span id="TOP"></span>

- [common.mk](#common.mk)
- [listprj.mk](#listprj.mk)
- [project.mk](#project.mk)
- [filelist.mk](#filelist.mk)
- [allprj.mk](#allprj.mk)

<span id="common.mk "></span>
## common.mk 

所有自工程的公共编译选项配置，为不同平台指定缺省的INCLUDE_DIR，LIB_DIR，CFLAGS等环境变量

- **SUPPORT_TARGET**  
指定本工程所支持的目标平台
```
SUPPORT_TARGET=x86 arm920t armv7 win32  arm926
```
对于当前环境下编译不支持平台xxx时会报错，需要在 SUPPORT_TARGET 后添加新平台
```
$ make ARCH=xxx
Makefile:308: *** "unsupport target [xxx]".  Stop.
```
common.mk根据目标平台而修改缺省环境变量INCLUDE_DIR、LFLAGS、LIB_DIR、CFLAGS。  

如下:  
指明x86平台和armv7平台下分别在/usr/local/install/lib、/usr/4412/install/lib目录
下搜索对应平台的 *.so 文件。
./lib-$(ARCH)在不同平台下后缀不同，x86平台下表示在lib-x86目录下寻找 .so 文件
```
ifeq ("$(ARCH)", "x86")
	INCLUDE_DIR	+= 
	LFLAGS		+= -Wl,-rpath=./:lib-x86/
	LIB_DIR 	+= -L/usr/local/install/lib -L./lib-$(ARCH)
	CFLAGS		+= -DTARGET_X86
endif

ifeq ("$(ARCH)", "armv7")
	INCLUDE_DIR	+= -I/usr/4412/install/include
	LFLAGS		+= -Wl,-rpath=./:./lib-armv7/
	LIB_DIR 	+= -L/usr/4412/install/lib -L./lib-$(ARCH)
	CFLAGS		+= -DTARGET_ARMV7
endif
```
- **ARCH**  
指定编译平台  
配置需要所支持的环境平台，最终生成文件存放的文件夹以-$(ARCH)做结尾，如ARCH=x86输出目录为前缀release，最终输出目录release-x86






<span id="listprj.mk"></span>
## listprj.mk
总工程列表，列举所有工程内容  

- **< project index >=script/< xxx >**    
script/<xxx>目录里存放该子工程的配置文件 [project.mk](#project.mk), [filelist.mk](#filelist.mk)。  
若 < xxx > 时不存在的目录，由于对于目录找不到 project.mk filelist.mk而会报错。  
**如下是指明一个不存在的 yyyyyy 目录**
```shell
pi1=script/yyyyyy
	pi1_arg=elf

$ make DP=pi1
Makefile:76: "file_prj undefined"
Makefile:78: *** commands commence before first target.  Stop.
```


- **< project index >_arg=< output type >**  
**< project index >_arg** 前面的命名前缀必须与 **< project index >=script/< xxx >** 相同，否则找不到参数  
**如下是一个例子**
```
pixxxx=script/default
	piyyyy_arg=mlib

$ make DP=pixxxx
Makefile:60: "project 'pixxxx' unfind"
Makefile:61: *** commands commence before first target.  Stop.
```

- **output type**  
工程输出类型，可选elf mlib bin  

	- elf 生产可执行文件  
	- mlib 生产库文件  
	- bin 在elf基础上生产bin文件，通常用于裸机编程，或生成数组、图片的镜像

- **DP=< project index >**   

指定当前编译的默认工程，临时编译某工程采用
```
$ make DP=xxxx
```




<span id="project.mk"></span>
## project.mk
自工程在common.mk基础上自有编译选项

- **PRJ_NAME**  
工程名描述

- **PRJ_VERSION，PRJ_PATCHLEVEL，PRJ_SUBLEVEL**  
工程版本

- **OUTPUT_ELF**   
输出*.elf文件名，默认为download.elf

- **OUTPUT_DIS**  
输出*.dis文件名，默认为download.dis

- **OUTPUT_BIN**  
输出*.bin文件名，默认为download.bin

- **OUTPUT_SO  **  
输出*.so文件名，默认为download.so，当工程输出类型选择mlib时有效

- **OUTPUT_A  **  
输出*.a文件名，默认为download.a，当工程输出类型选择mlib时有效

- **OUTPUT_DIR  **  
输出目录前缀，默认为release，目录后缀为common.mk中的ARCH。如ARCH=x86输出目录为前缀release，最终输出目录release-x86

- **INCLUDE_DIR**  
include搜索目录

- **LFLAGS**  
链接库文件名

- **LIB_DIR**  
链接库文件搜索目录

- **CFLAGS**  
编译选项

<span id="filelist.mk"></span>
## filelist.mk

工程编译文件列表  
SRCS-y为文件列表环境变量，与menuconfig结合动态修改编译文件集合
```
SRC-(CONFIG_XX) += aa.c
```

<span id="allprj.mk"></span>
## allprj.mk
所有自工程列表

- **PRJS**  
列出所有子工程，的 < project index > 它是make all的依赖，若该为空，则有如下错误
```
$ make all
make: Nothing to be done for `all'.
```

所有子工程若之间存在 **依赖关系** ，则需要将被依赖项放在前面，无依赖关系，无顺序要求。
pi1子工程需要pi2 pi3子工程的输出文件liba.so libb.so
```
PRJS:= pi2 pi3 pi1
```

