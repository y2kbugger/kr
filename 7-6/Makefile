all: firstdiff test;

firstdiff: firstdiff.c
	gcc -O0 -g3 firstdiff.c -o firstdiff

test: firstdiff
	./firstdiff
