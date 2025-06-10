#!/bin/bash

# 安全设置：任何命令执行失败则立即退出脚本
set -e

# 清理构建目录
rm -rf $(pwd)/build/*

# 进入构建目录，执行CMake和Make
cd $(pwd)/build &&
cmake .. &&
make

# 返回上级目录
cd ..

# 拷贝头文件到lib目录
cp -r $(pwd)/src/include $(pwd)/lib