#include <stdio.h>
#include <string.h>

#include <lua.h>  
#include <lauxlib.h>  
#include <lualib.h>  

int main (int argc, char *argv[])
{
    lua_State *L;
    char *line;

    L = lua_open();
    luaL_openlibs(L);

    line = "print('hello, world')";
    luaL_loadbuffer(L, line, strlen(line), "line");
    lua_pcall(L, 0, 0, 0);

    lua_close(L);

    return 0;
}
