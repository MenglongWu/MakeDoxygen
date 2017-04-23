project.mk 子工程特有配置
=====================
  在 common.mk 
  [《common.mk子工程公共配置》](./doc-common.md)，
  的公共配置不能满足情况下，
  添加各子工程所独有的配置。

# 1 输出命名
  - __PRJ_NAME__  
  工程名描述
  
  - __PRJ_VERSION，PRJ_PATCHLEVEL，PRJ_SUBLEVEL__  
  工程版本默认为 1.0.0
  
  - __OUTPUT_ELF__   
  输出*.elf文件名，默认为download.elf
  
  - __OUTPUT_DIS__  
  输出*.dis文件名，默认为download.dis
  
  - __OUTPUT_BIN__  
  输出*.bin文件名，默认为download.bin
  
  - __OUTPUT_SO__  
  输出*.so文件名，默认为download.so，当工程输出类型选择mlib时有效
  
  - __OUTPUT_A__  
  输出*.a文件名，默认为download.a，当工程输出类型选择mlib时有效
  
  - __OUTPUT_DIR__  
  输出目录前缀，默认为release，目录后缀为common.mk中的ARCH。如ARCH=x86输出目录为  前缀release，最终输出目录release-x86  
  
# 2 独立编译选项
  - __INCLUDE_DIR__  
  include搜索目录
  
  - __LFLAGS__  
  链接库文件名
  
  - __LIB_DIR__  
  链接库文件搜索目录
  
  - __CFLAGS__  
  编译选项，除了默认配置外，其余配置可以使用make menuconfig修改
  
  默认配置

```
CFLAGS      += 
        -DARCH=\"$(ARCH)\"  \
        -DPRJ_VERSION=\"$(PRJ_VERSION)\"    \
        -DPRJ_PATCHLEVEL=\"$(PRJ_PATCHLEVEL)\"  \
        -DPRJ_SUBLEVEL=\"$(PRJ_SUBLEVEL)\"  \
        -DPRJ_NAME=\"$(PRJ_NAME)\" \
```

  
  编译C代码时

```
CFLAGS += -std=gnu99
```

  开启CONFIG_NDEBUG后

```
CFLAGS += -DNDEBUG
```

  开启CONFIG_GIT_SHA1后

```
CFLGAS += -D__GIT_SHA1__=\"$(SHA1)\"
```
  

  开启CONFIG_USE_GCH后

```
CFLAGS += -Winvalid-pch
```

