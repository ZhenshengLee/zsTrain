cmake_minimum_required(VERSION 3.10.1)
project(testcmake)

SET(CMAKE_CXX_FLAGS "-std=c++11 -O3")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

link_directories(./lib)
include_directories(./include)
# add_executable(maintestso ./maintestso.cc)


# 通过引入外部依赖项功能实现静态链接
add_library(calculate_static STATIC IMPORTED GLOBAL)
set_target_properties(calculate_static PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib/libcalculate.a )

add_library(calculate_single_static STATIC IMPORTED GLOBAL)
set_target_properties(calculate_single_static PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib/libcalculate_single.a )

# 这个动态库是从静态库中提取所需要的符号的，8M
add_library(user1lib SHARED ./src/maintestlib.cc)
target_link_libraries(user1lib
calculate_single_static
)

add_library(user1lib_static STATIC ./src/maintestlib.cc)
target_link_libraries(user1lib_static
calculate_single_static
)

# 另一种合并目标文件的方法
set(user1lib_single_static_file ${PROJECT_BINARY_DIR}/libuser1lib_single.a)
add_custom_target(combined ALL
        COMMAND ar -x $<TARGET_FILE:user1lib_static>
        COMMAND ar -x $<TARGET_FILE:calculate_single_static>
        COMMAND ar -qcs ${user1lib_single_static_file} *.o
        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
        DEPENDS user1lib_static calculate_single_static
)

add_library(user1lib_single_static STATIC IMPORTED GLOBAL)
add_dependencies(user1lib_single_static combined)
set_target_properties(user1lib_single_static PROPERTIES IMPORTED_LOCATION ${user1lib_single_static_file} )

SET_TARGET_PROPERTIES(user1lib_single_static PROPERTIES OUTPUT_NAME "user1lib_single")  #参考 https://blog.csdn.net/hjxu2016/article/details/83343743
