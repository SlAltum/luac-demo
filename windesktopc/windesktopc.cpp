// windesktopc.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

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
    if (argc > 1)
    {
        lua_pushboolean(L, 1);
        lua_setfield(L, LUA_REGISTRYINDEX, "LUA_NOENV");
        if (LUA_OK != luaL_dofile(L, argv[1]))  //加载lua文件到c语言内存中，进行语法检查，不会编译
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
    system("pause");

    return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
