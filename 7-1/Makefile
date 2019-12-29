all: upper lower test;

upper: upperlower.c
	gcc -Wall -g3 -O0 upperlower.c -o upper

lower: upperlower.c
	gcc -Wall -g3 -O0 upperlower.c -o lower

test: upper lower
	echo HelloMars | ./upper
	echo HelloMars | ./lower

