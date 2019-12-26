all: out;

out: input.c
	gcc -O0 -g *.c -o out

test: out
	cat *.c | ./out
