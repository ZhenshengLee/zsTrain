aux_source_directory(. DIR_LIB_SRCS)
add_library(mul_static ${DIR_LIB_SRCS})
add_library(mul SHARED ${DIR_LIB_SRCS})

target_link_libraries(mul_static

)

SET_TARGET_PROPERTIES(mul_static PROPERTIES OUTPUT_NAME "mul")  #参考 https://blog.csdn.net/hjxu2016/article/details/83343743