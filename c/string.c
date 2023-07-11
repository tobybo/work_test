
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <lua.h>
#include <lauxlib.h>


void ptstr(char *s) {
    printf("%d,%d\n", sizeof(s), strlen(s));
    s[0] = 'm';
}

void ptstr2(char *s) {
    printf("%d,%d\n", sizeof(s), strlen(s));
    s[0] = 'm';
}

#define ptstr(s) ptstr("" s)

int main() {
    printf("%d\n", sizeof("hello"));
    //ptstr("hello");
    //ptstr2("hello");
    lua_State *L = luaL_newstate();
    char a[10] = "hello";
    lua_pushlstring(L, a, 10);
    //lua_pushstring(L, "hello");
    return 0;
}
