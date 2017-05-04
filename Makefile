lua:
	gcc lua.c -o lua -llua -lreadline
clean:
	rm -f lua *.o
