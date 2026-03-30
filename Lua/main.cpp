#include <iostream>
// 必须包裹在 extern "C" 中，因为 Lua 是 C 库
extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}


int main() {
    // 1. 初始化 Lua 状态机 (现代 C++ 中建议用智能指针或 RAII 封装)
    lua_State* L = luaL_newstate();
    luaL_openlibs(L); // 加载基础库

    // 2. 执行一段 Lua 代码
    std::string lua_code = "print('Hello from Lua!') return 42";
    if (luaL_dostring(L, lua_code.c_str()) != LUA_OK) {
        std::cerr << "Error: " << lua_tostring(L, -1) << std::endl;
        lua_pop(L, 1); // 弹出错误信息
    } else {
        // 3. 从栈顶获取返回值
        if (lua_isinteger(L, -1)) {
            std::cout << "Lua returned: " << lua_tointeger(L, -1) << std::endl;
        }
        lua_pop(L, 1); // 弹出返回值，保持栈平衡
    }

    // 4. 清理资源
    lua_close(L);
    return 0;
}