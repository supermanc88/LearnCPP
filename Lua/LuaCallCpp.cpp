#include <iostream>

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}


// 定义符合Lua的C++函数
int my_cpp_add(lua_State* L) {

    // 从Lua栈中获取参数
    int a = luaL_checkinteger(L, 1); // 获取第一个参数
    int b = luaL_checkinteger(L, 2); // 获取第二个参数

    lua_pushinteger(L, a + b); // 将结果压入Lua栈

    return 1;
}

int main() {

    lua_State* L = luaL_newstate();
    luaL_openlibs(L); // 加载Lua标准库

    // 注册C++函数到Lua
    lua_register(L, "cpp_add", my_cpp_add);

    // Lua代码调用C++函数
    std::string lua_code = R"(
        local result = cpp_add(10, 20)
        print("Result from C++ function: " .. result)
    )";

    if (luaL_dostring(L, lua_code.c_str()) != LUA_OK) {
        std::cerr << "Error: " << lua_tostring(L, -1) << std::endl;
        lua_pop(L, 1); // 弹出错误信息
    }

    lua_close(L); // 关闭Lua状态机

    return 0;
}