add_executable(zst_example_test test.cpp)
# target_link_libraries(zsa_example_test PRIVATE zsa::zsa)
target_link_libraries(zst_example_test PRIVATE gtest::gtest)

zsa_add_tests(TARGET zst_example_test HARDWARE_REQUIRED TEST_TYPE FUNCTIONAL)