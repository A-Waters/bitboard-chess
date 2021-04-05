SRC=$(wildcard src/*.c)

all:
	gcc -oFast $(SRC) -o chess -Iinclude -Wall

debug:
	gcc $(SRC) -o chess -Iinclude -Wall