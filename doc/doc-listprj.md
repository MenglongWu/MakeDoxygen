listprj.mk多工程列表
====================

总工程列表，列举所有工程内容  

  - __< project alias >=script/< xxx >__  
  script/<xxx>目录里存放该子工程的配置文件 [project.mk](./doc-project.md), [filelist.mk](./doc-filelist.md)，[rule.mk](./doc-rule.md)。  
  若 < xxx > 是不存在的目录，由于对于目录找不到 project.mk filelist.mk而会报错。  

 > 如下是指明一个不存在的 yyyyyy 目录
 
```shell
pi1=script/yyyyyy
	pi1_arg=elf

$ make DP=pi1
Makefile:76: "file_prj undefined"
Makefile:78: *** commands commence before first target.  Stop.
```


  - __< project alias >_arg=< output type >__  
  **< project alias >_arg** 前面的命名前缀必须与 **< project alias >=script/< xxx >** 相同，否则找不到参数  
  **如下是一个例子**

```
pixxxx=script/default
	piyyyy_arg=mlib

$ make DP=pixxxx
Makefile:60: "project 'pixxxx' unfind"
Makefile:61: *** commands commence before first target.  Stop.
```

  - __output type__  
  工程输出类型，可选elf mlib bin  

	- elf 生产可执行文件  
	- mlib 生产库文件  
	- bin 在elf基础上生产bin文件，通常用于裸机编程，或生成数组、图片的镜像

  - __DP=< project alias >__  

  指定当前编译的默认工程，临时编译某工程采用

```
$ make DP=xxxx
```

