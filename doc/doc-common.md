common.mk子工程公共配置
========================
  common.mk 是整个工程的公共配置
  [《project.mk 子工程特有配置》](./doc-project.md)，
  但子工程必须对 __OUTPUT_ELF、OUTPUT_SO、OUTPUT_A__ 设置唯一值， 
  其余可以使用common.mk的默认配置。

# 1 主要变量
  - __SUPPORT_TARGET__  

  指定本工程所支持的目标平台，或者说编译环境安装了哪些平台的交叉编译环境

```
SUPPORT_TARGET=x86 arm920t armv7 win32  arm926
```
  对于当前环境下编译不支持平台xxx时会报错，需要在 SUPPORT_TARGET 后添加新平台

```
$ make ARCH=xxx
Makefile:308: *** "unsupport target [xxx]".  Stop.
```

  - __CROSS_COMPILE__  
  
  交叉编译工具目录，它根据指定平台 （__ARCH__） 而动态修改

  - __ARCH__  

  指定编译平台  
  配置需要所支持的环境平台，最终生成文件存放的文件夹以-$(ARCH)  做结尾，如ARCH=x86输出目录为前缀release，最终输出目录release-x86  

  如下:  
  指明x86平台和arm920t平台下分别在/usr/local/install/lib、/usr/arm920t/install/lib目录下搜索对应平台的 *.so 文件。
  ./lib-$(ARCH)在不同平台下后缀不同，x86平台下表示在lib-x86目录下寻找 .so 文件

```
ifeq ("$(ARCH)", "x86")
    INCLUDE_DIR += 
    LFLAGS      += -Wl,-rpath=./:./lib-$(ARCH)/
    LIB_DIR     += -L/usr/local/install/lib -L./lib-$(ARCH)
    CFLAGS      += 
endif

ifeq ("$(ARCH)", "arm920t")
    INCLUDE_DIR += -I/usr/arm920t/install/include
    LFLAGS      += -Wl,-rpath=./:./lib-$(ARCH)/
    LIB_DIR     += -L/usr/arm920t/install/lib -L./lib-$(ARCH)
    CFLAGS      += 
endif
```



# 2 如何添加新平台
  去掉 common.mk 里相应注释，按照上文介绍的规则修改。

```
# SUPPORT_TARGET+=xxx

# todo More
# ifeq ("$(ARCH)", "your_target")
#   CROSS_COMPILE   = your crosstools directory
# endif


# todo More
#ifeq ("$(ARCH)", "your_target")
#   INCLUDE_DIR += -I/usr/your_target/install/include
#   LFLAGS      += -Wl,-rpath=./:./lib-$(ARCH)/
#   LIB_DIR     += -L/usr/your_target/install/lib -L./lib-$(ARCH)
#   CFLAGS      +=
# endif

```
