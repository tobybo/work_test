OBJ=string.c
test:$(OBJ)
	gcc -std=gnu99 -fPIC -Wl,-undefined,dynamic_lookup -o $@ $^ -I/root/home/github/skynet/3rd/lua_src -L/root/home/github/skynet/3rd/lua/ -llua -lm

