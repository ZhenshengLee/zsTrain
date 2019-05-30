#!/bin/sh

# 文件名称:  lcov_check.sh
# 内容摘要:  使用google-mock工具生成mock class类定义
# 作    者:  黎振胜
# 完成日期:  2018-09-20, 10:29:04 am

# ******************************************************************************
# usage:
# cd here
# ./lcov_check.sh
# ******************************************************************************

cd ..
test -d ./out || mkdir ./out
# ./tools/lcov-1.13/bin/lcov --capture --directory ./build --output-file ./out/coverage.info
# ./tools/lcov-1.13/bin/genhtml  ./out/coverage.info --output-directory out
# gcovr --source-encoding utf-8 --root ./lib/ --object-directory D:/E_DISK/zsGit/zsCMake/build  -j6 --html-details --output ./out/coverage.html
gcovr --source-encoding utf-8 --root ./lib/ --object-directory $(pwd)/build  -j6 --html-details --output ./out/coverage.html
