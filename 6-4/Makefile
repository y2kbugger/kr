all: countwords;

countwords: countwords.c
	gcc -Wall -g3 -O0 countwords.c -o countwords

test: countwords
	cat countwords.c | ./countwords
