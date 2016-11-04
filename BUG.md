------------------------------------------------------------
gcc-4.3.2不支持带空格的宏，如下所示，更换 >4.4.1 版本gcc支持  
```
Error
PRJ_NAME = "[Project Name]"
Replace
PRJ_NAME = "[Project-Name]"
```
所以要求对所有预定义宏-DXXX="YYY"，YYY部分不能有空格


------------------------------------------------------------
某些工程加入MODULE_INFO，编译成功后并不能生成.modinfo段。  
原因在于某些工程-O3选项后.modinfo段被删除  
修改proginfo.h里对.modinfo的修饰:  
```
__attribute__((section(".modinfo"),unused)) = __stringify(tag) "=" info
__attribute__((section(".modinfo"),used)) = __stringify(tag) "=" info
```