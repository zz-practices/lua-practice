#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <lua.h>  
#include <lauxlib.h>  
#include <lualib.h>  

#include <readline/readline.h>
#include <readline/history.h>


int main (void)
{
    char *ptr;
    int error;
    lua_State *L = lua_open();  /* opens Lua */
    luaL_openlibs(L);
    const char *prompt = "> ";

    fprintf(stdout, "%s\n", LUA_RELEASE " Copyright (C) 2017 wall-e, zz ");
    while ((ptr = readline(prompt)) != NULL) {
       error = luaL_loadbuffer(L, ptr, strlen(ptr), "line") || lua_pcall(L, 0, 0, 0);
       if (error) {
           fprintf(stderr, "%s\n", lua_tostring(L, -1));
           lua_pop(L, 1);/* pop error message from the stack */
       } else {
           add_history(ptr);
       }
       free(ptr);
    }

    lua_close(L);
    return 0;
}
