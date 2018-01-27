# JsonCpp的使用
## 两种调用方法

- （1）由ubuntu安装jsoncpp库，sudo apt-get install libjsoncpp-dev。这种方法最方便，不过要求运行环境都得装这个库
```cpp
// 在调用jsoncpp的源码文件中
#include<jsoncpp/json/json.h>
```
```bash
# 编译时，指定链接到jsoncpp库
-ljsoncpp

# jsoncpp静态和动态库的位置可以这样找到
ls /usr/lib/*/*jsoncpp*
```

- （2）下载[jsoncpp的源码](https://sourceforge.net/projects/jsoncpp/files/)编译生成jsoncpp的静态和动态库；将静态库和一系列的json头文件放入自己的项目中。这种方法方便项目移植，不要求运行环境装了jsoncpp库；本项目采用这种方法
    - lib目录中的libjsoncpp_linux-4.9.4.a，是从jsoncpp源码编译后生成的静态库文件复制而来
    - include/json目录中的一系列头文件，也是从jsoncpp源码中复制而来
    - 特地留了静态库的版本号，以便读者判断是否可以直接拿去用

> 参考：[wiki-jsoncpp](https://en.wikiversity.org/wiki/JsonCpp#JSON)

