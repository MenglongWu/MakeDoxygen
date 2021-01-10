没Qt Creator时如何用Makefile编译QT工程、rule.mk自定义规则
================
  __自定义__规则，实际上它也是个Makefile。

  MakeDoxygen工程已经能应对大多数项目开发规则需求 __（make xxx）__,
  不过难免开发者有定制需求，倘若直接修改根目录Makefile添加自定义规则
  存在困难，那么另起一个文件用于存放这些规则是个好办法，它就是rule.mk。


  rule.mk存放在子工程与filelist.mk project.mk同一级目录，添加自定义规则。

# 例子
  首先按照[__《3min搭建Hello World》__](./simple-guide.md)向导，创建pimy工程，
  再添加rule.mk

```
# rule.mk
hello:
    @echo "new rule"
    @echo $(SRCS-y)
    @echo $(CFLAGS)

```

  尝试效果

```
$ make DP=pimy hello
```


  对于有共通的规则，不必要再每个子工程rule.mk里写相同的内容，直接引用即可。
  被引用工程可看成是该类子工程的公共模板，如下两个新工程都引用hello里的规则。

```
# script/new-project-1/rule.mk
include script/hello/rule.mk

# script/new-project-2/rule.mk
include script/hello/rule.mk

```

# Qt工程模板
  script/prj_qt、script/prj_moc都是Qt项目子工程

  - [rule.mk](./script/qt-common/rule.mk) 引用script/qt-common/rule.mk规则
  - [project.mk](./script/qt-common/qt.mk) 引用script/qt-common/qt.mk

  Qt有自己的扩展C++语法
  需要将从 __*.h__ 预编译成 gcc 可识别的语法格式 __*.moc.cpp__ 。

  为Qt工程定制moc规则。

- __MOC__  
  指定Qt语法扩展分析工具存放位置

- __MOCS-y__  
  依赖源文件集，与SRCS-y作用一样，只不过它只被moc规则所用。  
  规则里填添加 __*.moc.cpp__ 所需文件，其中 __*__ 对应于同名的 __*.h__ 
  
