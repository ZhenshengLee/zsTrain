cmake_minimum_required(VERSION 3.10.1)
project(testcmake)

SET(CMAKE_CXX_FLAGS "-std=c++11 -O3")

aux_source_directory(. sourceList)
message(${sourceList})


include_directories("." "src" "include") #加入后，代码中加入头文件会在这些文件中查找

set(API_SOURCES
    "${PROJECT_SOURCE_DIR}/src/calculate.cc"
    "${PROJECT_SOURCE_DIR}/src/calculate.h"
    )
message(${API_SOURCES})
message("************")
message(${PROJECT_SOURCE_DIR})

file(GLOB CPP_FILES_IN_INCLUDE "include/*/*.cc")
message(${CPP_FILES_IN_INCLUDE})


add_subdirectory("include/add")  #需要CMakeLists.txt文件 并且会在build中创建
add_subdirectory("include/mul")
add_subdirectory("include/sub")
#add_subdirectory("src")

add_library(calculate_static STATIC ${API_SOURCES})
add_library(calculate SHARED ${API_SOURCES})


add_executable(maintest ${sourceList} ${API_SOURCES})

target_link_libraries(calculate_static STATIC
        add
        mul
        sub
        )
target_link_libraries(maintest calculate_static)
SET_TARGET_PROPERTIES(calculate_static PROPERTIES OUTPUT_NAME "calculate")  #参考 https://blog.csdn.net/hjxu2016/article/details/83343743

#add_executable(calculate ${sourceList} ${API_SOURCES} ${CPP_FILES_IN_INCLUDE})