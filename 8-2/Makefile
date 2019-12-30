all: testfopen test;

testfopen: testfopen.c
	gcc -Wall -g -O0 -o testfopen testfopen.c

test: testfopen
	./testfopen test.txt
