all: app mylib.so
app:lua.c
	gcc lua.c -o app -llua -lm

mylib.so:mylib.c
	gcc mylib.c -fPIC -shared -o mylib.so
clean:
	rm -f app *.o *.so
