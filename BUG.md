# gcc-4.3.2 -D缺陷
------------------------------------------------------------
gcc-4.3.2不支持带空格的宏，如下所示，更换 >4.4.1 版本gcc支持  
```
Error
PRJ_NAME = "[Project Name]"
Replace
PRJ_NAME = "[Project-Name]"
```
所以要求对所有预定义宏-DXXX="YYY"，YYY部分不能有空格

# -O3 优化 .modinfo
------------------------------------------------------------
某些工程加入MODULE_INFO，编译成功后并不能生成.modinfo段。  
原因在于某些工程-O3选项后.modinfo段被删除  
修改proginfo.h里对.modinfo的修饰:  
```
__attribute__((section(".modinfo"),unused)) = __stringify(tag) "=" info
__attribute__((section(".modinfo"),used)) = __stringify(tag) "=" info
```

# 多核编译
------------------------------------------------------------
启用多核编译时，启用同步任务数超过核心数编译会导致有依赖子工程编译顺序不对，
导致编译出错。该缺陷源于 **make** 不自动检测cpu核心数而直接采用用户指定的任务
数


## 例子
-------

cpu：双核
make： GNU Make 3.81

- 正编译（正常）

```
$ make  all
make DP=pi3 --no-print-directory
    ARCH       [x86] 
    compile    src/lb/lb_part1.c 
    create     lib-x86/liblb.so 
    create     lib-x86/liblb.a 
make DP=pi2 --no-print-directory
make[1]: Warning: File `.sha1' has modification time 0.75 s in the future
    ARCH       [x86] 
    compile    src/la/la_part1.c 
    create     lib-x86/libla.so 
    create     lib-x86/libla.a 
make[1]: warning:  Clock skew detected.  Your build may be incomplete.
make DP=pi1 --no-print-directory
make[1]: Warning: File `.sha1' has modification time 0.67 s in the future
    ARCH       [x86] 
    compile    src/smain.c 
    create     release-x86/default.elf 
make[1]: warning:  Clock skew detected.  Your build may be incomplete.
```

- 双任务编译（正常）

```
$ make  all -j2
make DP=pi3 --no-print-directory
make DP=pi2 --no-print-directory
    ARCH       [x86] 
    ARCH       [x86] 
    compile    src/lb/lb_part1.c 
    compile    src/la/la_part1.c 
    create     lib-x86/liblb.so 
    create     lib-x86/libla.so 
    create     lib-x86/liblb.a 
make DP=pi1 --no-print-directory
    create     lib-x86/libla.a 
make[1]: Warning: File `.sha1' has modification time 0.69 s in the future
    ARCH       [x86] 
    compile    src/smain.c 
    create     release-x86/default.elf 
make[1]: warning:  Clock skew detected.  Your build may be incomplete.
```


- 4任务编译（异常）

```
$ make -j4 all  
make DP=pi3 --no-print-directory
make DP=pi2 --no-print-directory
make DP=pi1 --no-print-directory
    ARCH       [x86] 
    ARCH       [x86] 
    ARCH       [x86] 
    compile    src/smain.c 
    compile    src/la/la_part1.c 
    compile    src/lb/lb_part1.c 
    create     release-x86/default.elf 
    create     lib-x86/liblb.so 
    create     lib-x86/libla.so 
/usr/bin/ld: cannot find -lla         <-- libla.so 应该在default.elf前完成编译
/usr/bin/ld: cannot find -llb         <-- liblb.so 应该在default.elf前完成编译
collect2: ld returned 1 exit status
make[1]: *** [load_lds-n] Error 1
make: *** [all-pi1] Error 2
make: *** Waiting for unfinished jobs....
    create     lib-x86/liblb.a 
    create     lib-x86/libla.a 
```