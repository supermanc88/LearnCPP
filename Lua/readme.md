# Lua编译和安装

从Lua官网下载Lua的源代码包，解压后进入目录，执行以下命令：

```bash
make all test

mkdir -p /Users/chengheming/Source/Personal/LearnCPP/Lua/third_party/lua
# 安装到指定目录
make install INSTALL_TOP=/Users/chengheming/Source/Personal/LearnCPP/Lua/third_party/lua
```