all: minscanf test;

minscanf: minscanf.c
	gcc -Wall -g3 -O0 minscanf.c -o minscanf

test: minscanf
	echo test:S |./minscanf
