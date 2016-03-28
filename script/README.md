## common.mk

* SUPPORT_TARGET  

指定本工程所支持的目标平台  
相应的也要根据本地计算机环境，为不同平台修改CROSS_COMPILE，INCLUDE_DIR，LFLAGS，LIB_DIR，CFLAGS环境变量


* ARCH

指定编译平台  
配置需要所支持的环境平台，最终生成文件存放的文件夹以-$(ARCH)做结尾，如ARCH=x86输出目录为前缀release，最终输出目录release-x86


## listprj.mk

总工程列表，列举所有工程内容  
**pi< num >=script/< xxx >**  
script/<xxx>目录里存放该子工程的配置文件project.mk,filelist.mk,

**pi< num >_arg=< output type >**  
output type:工程输出类型，可选bin,elf,mlib
pi< num >_arg:前面的pi<num>必须与 **pi< num >=script/< xxx >** 相同，否则找不到参数

**DP=pi< num >**   
制定当前编译的默认工程  

举例:  
DP=pi2，如下语句相同

```
	pi1=script/default
		pi1_arg=bin
	pi2=script/prj_liba
		pi2_arg=mlib
export DP=pi1
```

则下面语句执行效果相同
```
make 
make all
make bin
make DP=pi1 bin
```


## project.mk

* PRJ_NAME 

工程名描述

* PRJ_VERSION，PRJ_PATCHLEVEL，PRJ_SUBLEVEL  

工程版本

* OUTPUT_ELF

输出*.elf文件名，默认为download.elf

* OUTPUT_DIS

输出*.dis文件名，默认为download.dis

* OUTPUT_BIN

输出*.bin文件名，默认为download.bin

* OUTPUT_SO

输出*.so文件名，默认为download.so，当工程输出类型选择mlib时有效

* OUTPUT_A

输出*.a文件名，默认为download.a，当工程输出类型选择mlib时有效

* OUTPUT_DIR

输出目录前缀，默认为release，目录后缀为common.mk中的ARCH。如ARCH=x86输出目录为前缀release，最终输出目录release-x86

## filelist.mk

工程编译文件列表