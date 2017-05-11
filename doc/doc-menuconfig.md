字符图像界面配置工程
===================
  make menuconfig 调用 mconf，mconf 源于Linux内核源码，用于便捷的添加、删减工程
  特性。

  ![](./image/menuconfig.png)
# 1 Kconfig

  编辑 Kconfig 修改工程配置选项，
  是选择配置数据库脚本，最终生成.config为目的，如何编辑请参考任意 [Linux Kernel]
  内核文档 (Documentation/kbuild/kconfig-language.txt)
  配置工程，

```
$ make menuconfig
build autoconfig.h autoconfig.hpp
./script/mkheader/mkheader .config include/autoconfig.h "[default-project]"
read config file :.config
make header file :include/autoconfig.h
rm *.gch
```

  .config 经过转换后生成对于的 __autoconfig.h、autoconfig++.hpp__，分别用于C代码、
  C++代码。__使得应用程序得知当前系统的配置__。

```{makefile}
# .config
CONFIG_GIT_SHA1=y
CONFIG_USE_GCH=y
```

```{c}
# autoconfig.h autoconfig++.hpp
#define CONFIG_GIT_SHA1                                         1
#define CONFIG_USE_GCH                                          1
```

# 2 编辑
  建议子工程私有Kconfig保存在 __script/<your project>__ 目录下。
  只在根目录下的Kconfig引用子工程的配置，保留 __mainmenu "MakeDoxygen"__
  区域内容，它是MakeDoxygen的特性，你很可能用得上它。

```
# source script/<your project>/Kconfig
```


# 3 依赖
  - libncurses.so


[Linux Kernel]:https://github.com/torvalds/linux
