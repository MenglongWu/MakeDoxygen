3min搭建Hello World
===================

[详细参考](./doc/xxx)

# 1 拷贝空模板目录

```
$ cp script/empty script/hello-world -r
```

# 2 编辑script/listprj.mk
  - 添加子工程别名pimy
  - 子工程输出类型elf
  - 默认子工程从pi7修改成pimy

```
    pi6=script/prj_moc
        pi6_arg=elf
    pi7=script/prj_printl
        pi7_arg=elf

    pimy=script/hello-world
        pimy_arg=elf

# default project item
# export DP=pi7
export DP=pimy

```

# 3 编辑工程依赖script/allprj.mk（非必须）
  添加子工程pimy到依赖

```
PRJS-y:= pi1 pi2 pi3 pimy
```

# 4 编辑script/hello-world/filelist.mk
  添加工程文件

```
#################################################################
# list all souce file while be compiled
# file select or not please edit script/config.mk

SRCS-y += src/main.c
```

# 5 编辑script/hello-world/project.mk
  重命名输出文件

```
# default download.elf,download.dis,download.bin
OUTPUT_ELF  = hello-world.elf
# OUTPUT_DIS    = 
# OUTPUT_BIN    = 
```

# 6 编辑src/main.c

```
#include <stdio.h>

int main(void)
{
    printf("Hello World\r\n");
    return 0;
}
```

# 7 测试

  编译

```
$ make
```

  运行

```
$ make run
Hello World
或
$ make release-x86/hello-world.elf
Hello World
```

  清除

```
$ make aclean
或
$ make all
```
