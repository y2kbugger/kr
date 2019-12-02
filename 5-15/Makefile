run: out
	echo lex:
	./out < ./lines.txt
	echo num:
	./out -n < ./lines.txt

out: input.c
	gcc -O0 -g *.c -o out
