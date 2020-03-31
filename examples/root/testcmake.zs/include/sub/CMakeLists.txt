aux_source_directory(. DIR_LIB_SRCS)
add_library(sub_static ${DIR_LIB_SRCS})
add_library(sub SHARED ${DIR_LIB_SRCS})

SET_TARGET_PROPERTIES(sub_static PROPERTIES OUTPUT_NAME "sub")  #参考 https://blog.csdn.net/hjxu2016/article/details/83343743