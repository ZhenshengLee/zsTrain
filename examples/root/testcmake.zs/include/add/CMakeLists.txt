aux_source_directory(. DIR_LIB_SRCS)
add_library(add_static ${DIR_LIB_SRCS})
add_library(add SHARED ${DIR_LIB_SRCS})

SET_TARGET_PROPERTIES(add_static PROPERTIES OUTPUT_NAME "add")  #参考 https://blog.csdn.net/hjxu2016/article/details/83343743