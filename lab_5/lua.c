#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>

#include <lua.h>  
#include <lauxlib.h>  
#include <lualib.h>  

/* thread status */
#define LUA_OK          0

static int report (lua_State *L, int status) {
    if (status != LUA_OK) {
        const char *msg = lua_tostring(L, -1);
        printf("error: %s\n", msg);
        lua_pop(L, 1);  /* remove message */
    }
    return status;
}

static int dochunk (lua_State *L, int status) {
    if (status == LUA_OK) status = lua_pcall(L, 0, 0, 0);
    return report(L, status);
}

static int dofile (lua_State *L, const char *name) {
    return dochunk(L, luaL_loadfile(L, name));
}

int main (int argc, char *argv[])
{
    lua_State *L;

    L = lua_open();
    luaL_openlibs(L);

    dofile(L, "t.lua");

    lua_getglobal(L, "hello");
    lua_pushstring(L, "zz");
    lua_call(L, 1, 1);

    if(lua_isstring(L, 1)){
        printf("name: %s\n", lua_tostring(L, 1));
    }

    lua_close(L);

    return 0;
}
