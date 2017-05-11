- PRJS-y
- PRJS-CONFIG_xxx
- pixx:piyy pizz

<span id="allprj.mk"></span>
## allprj.mk
所有自工程列表

- **PRJS**  
列出所有子工程，的 < project index > 它是make all的依赖，若该为空，则有如下错误
```
$ make all
make: Nothing to be done for `all'.
```

所有子工程若之间存在 **依赖关系** ，则需要将被依赖项放在前面，无依赖关系，无顺序要求。
pi1子工程需要pi2 pi3子工程的输出文件liba.so libb.so
```
PRJS:= pi2 pi3 pi1
```
