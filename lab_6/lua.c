#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <math.h>

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

static int lua_sin(lua_State *L)
{
    double a = luaL_checknumber(L, 1);
    lua_pushnumber(L, sin(a));

    double b = luaL_checknumber(L, 2);
    lua_pushnumber(L, sin(b));

    return 2;
}

int main (int argc, char *argv[])
{
    lua_State *L;

    L = lua_open();
    luaL_openlibs(L);

    lua_register(L, "my_sin", lua_sin);

    dofile(L, "t.lua");

    lua_close(L);

    return 0;
}
