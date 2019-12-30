all: mycat test;

mycat: mycat.c
	gcc --std=c11 -g3 -O0 -o mycat mycat.c

test: mycat
	echo Know its working
	./mycat_old test.txt
	./mycat test.txt
	echo Benchmark
	time ./mycat_old bench.txt >/dev/null
	time ./mycat bench.txt >/dev/null
