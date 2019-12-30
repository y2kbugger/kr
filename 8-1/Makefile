all: mycat test;

mycat: mycat.c
	gcc --std=c11 -g3 -O0 -o mycat mycat.c

test: mycat
	./mycat test.txt
