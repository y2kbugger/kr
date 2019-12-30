all: testfopen test;

mycat: testfopen.c
	gcc --std=c11 -g3 -O0 -o testfopen testfopen.c

test: testfopen
	./testfopen test.txt
