filelist.mk 文件树
==================
  相当于IDE的文件目录树，所有文件的路径是顶层目录的相对路径。

  

  - __SRCS-y__  

  所有需要编译的源文件

```
./Makefile
./src/smain.c 
```

  ./script/default/filelist.mk的编辑内容

```
SRCS-y += src/smain.c
```

  - __GCHS-y__

  需要预编译程序

  预编译src/qt/qt.hpp

```
GCHS-y += src/qt/qt.hpp.gch
```

  - __MOCS-y__
  
  Qt扩展C++语法展开工具，是的g++可以编译它

  将 src/qt/dlg-net.h 转换成 src/qt/dlg-net.moc.cpp

```
MOCS-y += src/qt/dlg-net.moc.cpp
```

  
