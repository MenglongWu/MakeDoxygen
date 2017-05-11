预编译头文件
============
# 背景

  当工程需要无比庞大，头文件之间相互嵌套，在每个C\CPP文件里都展开相同的头文件，
  造成编译时间的浪费，预编译头文件的作用是将需要的头文件编译成二进制，之后
  include 该文件就不必展开，对于大工程节省编译时间明显。

  ![](./image/precompile.png)
  
  __修改前__

```{c}
// module1.c
#include <a.h>
#include <b.h>
#include <c.h>

// module2.c
#include <a.h>
#include <b.h>
#include <c.h>

// module3.c
#include <a.h>
#include <b.h>
#include <c.h>
```

  __修改后__

```{c}
// common.h
#include <a.h>
#include <b.h>
#include <c.h>

// module1.c
#include <common.h>

// module2.c
#include <common.h>

// module3.c
#include <common.h>
```

  预编译common.h 生成 common.h.gch，在include <common.h> 时编译前会检查
  是否存在 common.h.gch 存在则直接引用。

  __需要提醒两点__

  __1. 预编译文件也是平台不兼容的__   
  在更换平台后应该重新编译，如果使用x86平台下首先生成gch用在arm编译环境下会报错，
  编译器依旧使用 .h 文件。

```
  cc1: warning: ./common.h.gch: created by a different GCC executable
```
  
  __2. 使用就版本 gch 导致生成代码不符和预期__  
  gch是旧版本.h生成的，编辑.h后没有重新编译，在编译工程时编译器将使用旧版本的gch  
  不过这一点在MakeDoxygen下不用担心，gch与它的源文件之间存在依赖关系


```{makefile}
# Makefile
%.hpp.gch:%.hpp
	
%.h.gch:%.h
```

# 规则

  - __GCHS-y__  
  
  在 GCHS-y 中定义需要的所有预编译的头文件  
  



```{makefile}
 GCHS-y += common.h.gch
```
  如果选择使用autoconfig.h.gch、autoconfig++.h.gch，两文件的差异在于前者用于
  C代码、后者用于C++代码。

```
  |   Location:
  |     -> Project
  |       -> Support precompile (USE_GCH [=y])
  |            [*]   add autoconfig.h.gch
  |            [*]   add autoconfig++.h.gch
```

  那么将自动在GCHS-y添加他们的依赖。

```{makefile}
 GCHS-y += common.h.gch
 GCHS-y += inclue/autoconfig.h.gch
 GCHS-y += inclue/autoconfig++.h.gch
```

  - __删除gch__  
  预编译的生成文件 *.gch 只有在使用 __make menuconfig或
  make DP=xxx rmgch__ 才删除，区别在于前者删除所有预编译文件，后者只删除某子工程
  所依赖的预编译。

  

