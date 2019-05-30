#!/bin/sh

# 文件名称:  gmock_gen.sh
# 内容摘要:  使用google-mock工具生成mock class类定义
# 作    者:  黎振胜
# 完成日期:  2018-09-20, 10:29:04 am

# ******************************************************************************
# usage
# cd here
# ./gmock_gen.sh ../include/logAnalyzer.h fileExtMgr
# ******************************************************************************

PARA_FILE_NAME=$1
PARA_CLASS_NAME=$2

../tools/googletest-release-1.8.0/googlemock/scripts/generator/gmock_gen.py "${PARA_FILE_NAME}" "${PARA_CLASS_NAME}"
