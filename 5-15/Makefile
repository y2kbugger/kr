run: out
	echo lex:
	./out < ./lines.txt
	echo num:
	./out -n < ./lines.txt
	echo reverse:
	./out -n -r < ./lines.txt
	echo fold/ignorecase:
	./out -f < ./linesalphanum.txt

out: input.c
	gcc -O0 -g *.c -o out
