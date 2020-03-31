cmake_minimum_required(VERSION 3.10.1)
project(testcmake)

SET(CMAKE_CXX_FLAGS "-std=c++11 -O3")

set(ROOT "/home/haoqi/haoqi/kaldi-api/testcmake/build")
aux_source_directory(. sourceList)
message(${sourceList})

add_executable(maintest ${sourceList})
target_link_libraries(maintest "${ROOT}/libcalculate.so")