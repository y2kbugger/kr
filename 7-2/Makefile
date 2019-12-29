all: escape test;

upper: escape.c
	gcc -Wall -g3 -O0 escape.c -o escape

test: escape
	cat ./random | ./escape

