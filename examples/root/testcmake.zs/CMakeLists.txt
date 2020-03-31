cmake_minimum_required(VERSION 3.10.1)
project(testcmake)

cmake_policy(SET CMP0048 NEW)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

SET(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 99)
set(CMAKE_BUILD_TYPE Debug)

include_directories("." "src" "include") #加入后，代码中加入头文件会在这些文件中查找

add_subdirectory("include/add")  #需要CMakeLists.txt文件 并且会在build中创建
add_subdirectory("include/sub")
add_subdirectory("include/mul")
add_subdirectory("testso")
add_subdirectory("testlib")

set(API_SOURCES
    "${PROJECT_SOURCE_DIR}/src/calculate.cc"
    "${PROJECT_SOURCE_DIR}/src/calculate.h"
    )
message(${API_SOURCES})
message("************")
message(${PROJECT_SOURCE_DIR})

file(GLOB CPP_FILES_IN_INCLUDE "include/*/*.cc")
message(${CPP_FILES_IN_INCLUDE})

add_library(calculate_static STATIC ${API_SOURCES})
add_library(calculate SHARED ${API_SOURCES})
target_link_libraries(calculate_static
        add_static
        mul_static
        sub_static
        )
SET_TARGET_PROPERTIES(calculate_static PROPERTIES OUTPUT_NAME "calculate")  #参考 https://blog.csdn.net/hjxu2016/article/details/83343743

# # 合并目标文件
# add_library(calculate_single_static
#     STATIC
#     ${API_SOURCES}
#     $<TARGET_OBJECTS:add_static>
#     $<TARGET_OBJECTS:mul_static>
#     $<TARGET_OBJECTS:sub_static>
# )

# 另一种合并目标文件的方法
# set(calculate_single_static_file ${PROJECT_BINARY_DIR}/libcalculate_single.a)
# add_custom_target(combined ALL
#         COMMAND ar -x $<TARGET_FILE:calculate_static>
#         COMMAND ar -x $<TARGET_FILE:add_static>
#         COMMAND ar -x $<TARGET_FILE:mul_static>
#         COMMAND ar -x $<TARGET_FILE:sub_static>
#         COMMAND ar -qcs ${calculate_single_static_file} *.o
#         WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
#         DEPENDS calculate_static add_static mul_static sub_static
# )

# add_library(calculate_single_static STATIC IMPORTED GLOBAL)
# add_dependencies(calculate_single_static combined)
# set_target_properties(calculate_single_static PROPERTIES IMPORTED_LOCATION ${calculate_single_static_file} )

# SET_TARGET_PROPERTIES(calculate_single_static PROPERTIES OUTPUT_NAME "calculate_single")  #参考 https://blog.csdn.net/hjxu2016/article/details/83343743

# add_library(calculate_single_static STATIC ${API_SOURCES})
# target_link_libraries(calculate_single_static PUBLIC
# -Wl,--whole-archive
#         $<TARGET_PROPERTY:add_static,INTERFACE_LINK_LIBRARIES>
#         # mul_static
#         # sub_static
# -Wl,--no-whole-archive
# )

add_executable(maintest ./main.cc)
target_link_libraries(maintest calculate_static)

add_executable(maintest_single ./main.cc)
target_link_libraries(maintest_single calculate_single_static)
