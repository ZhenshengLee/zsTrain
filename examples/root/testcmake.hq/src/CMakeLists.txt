cmake_minimum_required(VERSION 3.10.1)
project(testcmake)

SET(CMAKE_CXX_FLAGS "-std=c++11 -O3")

aux_source_directory(. sourceList)
message(${sourceList})

include_directories("." "${PROJECT_SOURCE_DIR}/../include") #加入后，代码中加入头文件会在这些文件中查找

set(API_SOURCES 
    "${PROJECT_SOURCE_DIR}/calculate.cc"
    "${PROJECT_SOURCE_DIR}/calculate.h"
    )


add_library(calculate_static STATIC ${API_SOURCES})
#add_library(calculate SHARED ${API_SOURCES})


target_link_libraries(calculate_static
        ${PROJECT_SOURCE_DIR}/build/include/add/libadd.a
        ${PROJECT_SOURCE_DIR}/build/include/mul/libmul.a
        ${PROJECT_SOURCE_DIR}/build/include/sub/libsub.a
        )

SET_TARGET_PROPERTIES(calculate_static PROPERTIES OUTPUT_NAME "calculate")  #参考 https://blog.csdn.net/hjxu2016/article/details/83343743
