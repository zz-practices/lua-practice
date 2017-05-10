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

int main (int argc, char *argv[])
{
    lua_State *L;

    L = lua_open();
    luaL_openlibs(L);

    lua_register(L, "dir", l_dir);

    dofile(L, "t.lua");

    lua_close(L);

    return 0;
}
