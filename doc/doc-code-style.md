代码风格审查
============

  支持 __Linux Kernel__、__Google__ 代码风格审查。


  如下是待审查代码
```
 1 /**
 2  * Copyright 2015-2017 MenglongWoo@aliyun.com
 3  * @file  src/code-style.c
 4  * @brief  example for MakeDoxygen
 5 */
 6 
 7 void fun(void)
 8 {
 9   int a=1;
10   int *p = (int *)&a;
11 }
12 
```



# 1 Kernel风格
  支持 __Linux Kernel__ 代码风格审查

  __checkpatch.pl__ 是用于检测补丁文件是否符合风格，加选项 __'-f'__ 同样也可以
  检查代码风格。


  ![](./image/cs-checkpatch.png)

  如上代码里要求在 __'='__ 符号两端添加空格

```
 9   int a = 1;
```

  再次风格审查无任何错误/警告

```
$ ./script/checkpatch.pl -f src/code-style.c 
total: 0 errors, 0 warnings, 11 lines checked

src/code-style.c has no obvious style problems and is ready for submission.
```



  本工程对原始checkpatch.pl审查规则适当修改

  修改原因：__我不喜欢__
  
## 1.1 取消只允许多行注释
  
  原始规则只允许

```
/*
 * comment
 */
```

  修改后允许

```
// comment
```

## 1.2 取消单行嵌套不加括号

  原始规则只允许

```
  if (condition)
    a = 1;
  else
    a = 2;
  while(condition)
    a++;
```

  修改后规则无论嵌套内容多少行，均加括号加花括号

```
  if (condition) {
    a = 1;
  }
  else {
    a = 2;
  }

  while(condition) {
    a++;
  }
```


## 1.3 测试平台

  - perl v5.10.1

# 2 Google风格

  __cpplint.py__ 来源于
  [https://github.com/TheOstrichIO/cpplint](https://github.com/TheOstrichIO/cpplint)

  Google使用它作为自己的C++代码规范检查工具，作适当修改后它也可以检查C代码。

  
  被审查代码存在3个风格错误

```
$ ./script/cpplint.py src/code-style.c 
src/code-style.c:8:  { should almost always be at the end of the previous line  [whitespace/braces] [4]
src/code-style.c:9:  Missing spaces around =  [whitespace/operators] [4]
src/code-style.c:10:  Using C-style cast.  Use reinterpret_cast<int *>(...) instead  [readability/casting] [4]
Done processing src/code-style.c
Total errors found: 3
```
  
  其中 __[whitespace/operators]__ 错误的消除参考 __Kernel风格__ 处理方式。

  其余错误可用 __--filter=__ 添加或消除cpplint.py审查规则，规则名称就是
  __[xxx/yyy]__ 的内容


```
$ ./script/cpplint.py  --filter=-whitespace/braces,-readability/casting src/code-style.c                      
Done processing src/code-style.c
Total errors found: 0
```


## 2.1 配置
  上文中为了添加过滤规则必须写段很长的过滤规则，实际上cpplint.py支持从文件导入
  配置规则，默认名 __CPPLINT.cfg__

  上文的过滤规则写入 __CPPLINT.cfg__ 格式参考

```
$ cat CPPLINT.cfg 
filter=-readability/casting
filter=-whitespace/braces
```


  不过 __MakeDoxygen__ 支持字符界面自动生成 __CPPLINT.cfg__

  __make cpplintconfig__

  ![](./image/cpplintconfig.png)

  以去除 __readability/casting__ 规则为目标，进入 __readability -->__，勾选

```
          [ ] readability/alt_tokens                                  
          [ ] readability/braces                                      
          [*] readability/casting                                     
          [*]   unuse                                                 
          [ ] readability/check                                       
          [ ] readability/constructors  
```
  保存后自动在 __CPPLINT.cfg__ 添加一行规则

```
filter=-readability/casting
```

### 2.1.1 unuse
  每行规则都展开后都有一行 __unuse__

  默认情况 __cpplint.py__ 使用 __所有规则__，即只选择 __readability/casting__ 而
  不选择其下的 __unuse__，不会对该规则有任何影响

  参考如下规则配置后生成的 __CPPLINT.cfg__
```
          [*] readability/alt_tokens                                  
          [ ]   unuse (NEW)                                                 
          [ ] readability/braces                                      
          [*] readability/casting                                     
          [*]   unuse                                                 
          [ ] readability/check                                       
          [*] readability/constructors  
          [ ]   unuse (NEW)                                                
```

```
$ cat CPPLINT.cfg   
filter=+readability/alt_tokens
filter=-readability/casting
filter=+readability/constructors
```

## 2.2 测试平台

  - python 2.7.13 (2.6.6) __(测试通过)__
  - python 3.6.1 __(失败)__
