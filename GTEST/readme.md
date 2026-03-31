# gtest 编译

```bash
# 1. 下载 gtest
wget https://github.com/google/googletest/releases/download/v1.17.0/googletest-1.17.0.tar.gz -O googletest-1.17.0.tar.gz

# 2. 解压
tar -zxvf googletest-1.17.0.tar.gz

# 3. 进入目录
cd googletest-1.17.0

# 4. 创建构建目录
mkdir build
cd build

# 5. 生成 Makefile
cmake .. -DCMAKE_INSTALL_PREFIX=/Users/chengheming/Source/Personal/LearnCPP/GTEST/gtest_install

# 6. 编译
make

# 7. 安装（可选）
make install

```