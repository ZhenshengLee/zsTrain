include(${CMAKE_SOURCE_DIR}/cmake/public/app.cmake)

# CTest
if(BUILDWITHTEST)
    # 为TestFixture添加，不属于模板的一部分
    # 以后的Test二选一选用测试项构造方法，名字均为helloWorldTest
    add_executable(helloWorldTestFix helloWorldTestFix.cpp)
    target_link_libraries(helloWorldTestFix
        gtest
        gtest_main
        gmock
        gmock_main
        ${CLASS_LIB}
    )
    add_test(
        NAME helloWorldTestFix
        COMMAND $<TARGET_FILE:helloWorldTestFix>
    )
endif()
