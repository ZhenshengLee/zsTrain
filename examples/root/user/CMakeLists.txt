cmake_minimum_required(VERSION 3.10.1)
project(testcmake)

SET(CMAKE_CXX_FLAGS "-std=c++11 -O3")

include_directories("." "src" "include")
link_directories(./lib)

# add_executable(maintestso ./maintestso.cc)

# # 默认动态链接
# target_link_libraries(maintestso
# calculate
# sub
# mul
# add
# )

# 通过引入外部依赖项功能实现静态链接
add_library(calculate_static STATIC IMPORTED GLOBAL)
set_target_properties(calculate_static PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib/libcalculate.a )

add_library(calculate_single_static STATIC IMPORTED GLOBAL)
set_target_properties(calculate_single_static PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib/libcalculate_single.a )

add_executable(maintestlib ./maintestlib.cc)
target_link_libraries(maintestlib
calculate_single_static
)


