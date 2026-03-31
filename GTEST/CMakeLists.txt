cmake_minimum_required(VERSION 3.5)
project(GTEST_L)

set(CMAKE_CXX_STANDARD 17)

add_executable(GTEST_L1 main.cpp)

add_executable(GTEST_L2 gmock_test.cpp)

target_include_directories(GTEST_L1 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/gtest_install/include)
target_link_directories(GTEST_L1 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/gtest_install/lib)

target_include_directories(GTEST_L2 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/gtest_install/include)
target_link_directories(GTEST_L2 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/gtest_install/lib)

#target_link_libraries(GTEST_L1 gtest gtest_main pthread)

# 自己写main函数，所以不链接gtest_main
target_link_libraries(GTEST_L1 gtest pthread)
target_link_libraries(GTEST_L2 gtest gmock gmock_main pthread)