#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <math.h>
#include <dirent.h>
#include <errno.h>

#include <lua.h>  
#include <lauxlib.h>  
#include <lualib.h>  

/* thread status */
#define LUA_OK          0

static int l_dir(lua_State *L)
{
    DIR *dir;
    struct dirent *entry;
    int i;

    const char *path = luaL_checkstring(L, 1);

    dir = opendir(path);
    if (dir == NULL) {
        lua_pushnil(L);
        lua_pushstring(L, strerror(errno));
        return 2;
    }

    lua_newtable(L);
    i = 1;
    while((entry = readdir(dir)) != NULL) {
        lua_pushnumber(L, i++);
        lua_pushstring(L, entry->d_name);
        lua_settable(L, -3);
    }

    closedir(dir);
    return 1;
}

static const struct luaL_Reg mylib [] = {
    {"dir", l_dir},
    {NULL, NULL}
};

int luaopen_mylib(lua_State *L)
{
    luaL_register(L, "mylib", mylib);
    return 1;
}
