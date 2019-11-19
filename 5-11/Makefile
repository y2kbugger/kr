run: out
	./out 2 3 4 +
	./out 2 3 4 + =
	./out 2 3 4 + '*'
	./out 2 3 4 + '*' =
	./out 2 3 4 +extra '*dfk' 
	./out 2 3 4 +extra '*dfk' =
out: *.c
	gcc -g -Wall -lm *.c -o out
