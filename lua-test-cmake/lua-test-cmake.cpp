// lua-test-cmake.cpp: 定义应用程序的入口点。
//

#include "lua-test-cmake.h"

using namespace std;

#include <cstdio>

extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

static void call_func(lua_State* L, const char* funcname)
{
    lua_getglobal(L, funcname); // 查找lua文件中的全局函数，并压入虚拟栈
    lua_pushinteger(L, 1);      // 压栈，传入参数
    lua_call(L, 1, 0);          // 调用方法
}

int main(int argc, char* argv[])
{
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);
    //luaL_dofile(L, "test.lua");
    if (argc > 1)
    {
        lua_pushboolean(L, 1);
        lua_setfield(L, LUA_REGISTRYINDEX, "LUA_NOENV");
        if (LUA_OK != luaL_dofile(L, "test.lua"))
            //if (LUA_OK != luaL_dofile(L, argv[1]))
        {
            const char* err = lua_tostring(L, -1);
            fprintf(stderr, "err:\t%s\n", err);
            return -1;
        }
    }
    call_func(L, "Init");
    call_func(L, "Loop");
    call_func(L, "Release");

    lua_close(L);

    return 0;
}
