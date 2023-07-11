//==============================================================================
// 多线程共享 lua table
// Author: toby
// Desc:
//     1. 测试通过 c 接口 set_value(k, v) 将 k, v 压入另一个 lua 虚拟机是否可行
//          大概率不可行，lua value 中可能包含 gc 相关信息，还有字符串引用
//          结果： 失败，lua 不提供直接返回 TValue 的接口，可能可以先提取数据类型，
//                  再调用对应函数来处理，可能 effil 就是这样做的
//     2. 测试将 effil.table 作为 share table
//          少加一个编译选项导致 effil.so 不能正常 require -Wl,-E
//          gcc -std=gnu99 -o a test.c -I/usr/local/lua53/include -L/usr/local/lua53/lib -Wl,-E -llua53 -lm -lpthread -ldl -lstdc++
//
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

lua_State* lshare = NULL;
pthread_mutex_t share_lock;

int gInit;

int error_hook( lua_State* L )
{
    printf("[LUA_ERROR] %s", lua_tostring(L, -1));
    lua_Debug ldb;
    int i = 0;
    for ( i = 0; lua_getstack( L, i, &ldb ) == 1; i++ ) {
        lua_getinfo( L, "Slnu", &ldb );
        const char * name = ldb.name ? ldb.name : "";
        const char * filename = ldb.source ? ldb.source : "";
        printf("[LUA_ERROR] %s '%s' @ file '%s', line %d\n", ldb.what, name, filename, ldb.currentline );
    }
    return 0;
}

// TValue index2adr(lua_State *L, int idx) {
//     if (idx > 0) {
//         return L->ci->func + idx;
//     } else {
//         return L->top + idx;
//     }
// }

int regist_share_table(lua_State *L) {
    const char* name = luaL_checkstring(L, 1);
    void *table = lua_touserdata(L, 2);
    int top = lua_gettop(lshare);
    lua_pushlightuserdata(lshare, table);
    lua_setglobal(lshare, name);
    lua_settop(lshare, top);
    return 0;
}

int lock_share_table(lua_State *L) {
    pthread_mutex_lock(&share_lock);
	return 0;
}

int unlock_share_table(lua_State *L) {
    pthread_mutex_unlock(&share_lock);
    gInit = 1;
	return 0;
}

void *thread_main(void *lmain) {
    int top = lua_gettop(lmain);
    luaL_openlibs(lmain);
    lua_register(lmain, "regist_share_table", regist_share_table);
	if (luaL_loadfile(lmain, "main.lua") || lua_pcall(lmain, 0, 1, top)) {
		printf("excute main.lua failed\n");
		exit(-1);
	}
    return NULL;
}

void *thread_share(void *lshare) {
    while (!gInit) {
    }
    int top = lua_gettop(lshare);
    luaL_openlibs(lshare);
    if(luaL_loadfile(lshare, "share.lua") || lua_pcall(lshare, 0, 1, top)) {
        printf("excute main.lua failed\n");
        exit(-1);
    }
    return NULL;
}

pthread_t create_thread(void *(thread_function)(void *), void *L) {
    lua_register(L, "lock_share_table", lock_share_table);
    lua_register(L, "unlock_share_table", unlock_share_table);
    lua_atpanic(L, error_hook);
    lua_pushcfunction(L, error_hook);
    pthread_t my_thread;
    int result_code;

    // Create the thread
    result_code = pthread_create(&my_thread, NULL, thread_function, L);
    if (result_code != 0) {
        perror("pthread_create failed");
        return 0;
    }

    return my_thread;
}

int main(int argc, char *argv[]) {
    lua_State* lmain = luaL_newstate();
    lshare = luaL_newstate();

    pthread_mutex_init(&share_lock, NULL);

    pthread_t tid_main = create_thread(thread_main, lmain);
    pthread_t tid_share = create_thread(thread_share, lshare);

    if (tid_main > 0) pthread_join(tid_main, NULL);
    if (tid_share > 0) pthread_join(tid_share, NULL);

    pthread_mutex_destroy(&share_lock);

    return 0;
}

