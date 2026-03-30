cmake_minimum_required(VERSION 3.5)

project(LuaWithCpp)

set(CMAKE_CXX_STANDARD 14)

add_executable(LuaWithCpp main.cpp)
add_executable(LuaCallCpp LuaCallCpp.cpp)

target_include_directories(LuaWithCpp PRIVATE ${PROJECT_SOURCE_DIR}/third_party/Lua/include)
target_link_directories(LuaWithCpp PRIVATE ${PROJECT_SOURCE_DIR}/third_party/Lua/lib)
target_link_libraries(LuaWithCpp lua)

target_include_directories(LuaCallCpp PRIVATE ${PROJECT_SOURCE_DIR}/third_party/Lua/include)
target_link_directories(LuaCallCpp PRIVATE ${PROJECT_SOURCE_DIR}/third_party/Lua/lib)
target_link_libraries(LuaCallCpp lua)