SRC=$(wildcard src/*.c)

all:
	gcc -oFast $(SRC) -o chess -Iinclude 

debug:
	gcc $(SRC) -o chess -Iinclude 