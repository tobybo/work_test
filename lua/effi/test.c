//==============================================================================
// 多线程共享 lua table
// Author: toby
// Desc:
//     1. 测试通过 c 接口 set_value(k, v) 将 k, v 压入另一个 lua 虚拟机是否可行
//          大概率不可行，lua value 中可能包含 gc 相关信息，还有字符串引用
//          结果： 失败，lua 不提供直接返回 TValue 的接口，可能可以先提取数据类型，
//                  再调用对应函数来处理，可能 effil 就是这样做的
//     2. 测试将 effil.table 作为 share table
//          结果： 失败，由 c 来启动 lua 虚拟机，无法加载 effil.so
// History:
//     2023-06-05 02:11:27 Updated
// Copyright © 2023 IGG SINGAPORE PTE. LTD. All rights reserved.
//==============================================================================

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>

static int
lcopy(lua_State *L) {
    printf("this is lcopy\n");
    return 0;
}

static int
lnewwriter(lua_State *L) {
    lua_pushvalue(L, lua_upvalueindex(1));
    lua_setmetatable(L, -2);
    return 0;
}

int get_func_tab(lua_State *L) {
    lua_createtable(L, 0, 3);


    luaL_Reg writer[] = {
        { "new", lnewwriter },
        { NULL, NULL },
    };
    lua_createtable(L, 0, 2);
    lua_pushcfunction(L, lcopy);
    lua_setfield(L, -2, "__index");
    luaL_setfuncs(L, writer, 1);
    return 1;
}

int main(int argc, char *argv[]) {
    lua_State* lmain = luaL_newstate();
    luaL_openlibs(lmain);
    lua_register(lmain, "get_func_tab", get_func_tab);
	if(luaL_loadfile(lmain, "upvalue.lua") || lua_pcall(lmain, 0, 0, 0)) {
		printf("excute main.lua failed\n");
		exit(-1);
	}
    return 0;
}

