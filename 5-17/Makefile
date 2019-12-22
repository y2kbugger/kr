run: out
	echo lex:
	./out < ./lines.txt
	echo num:
	./out -n < ./lines.txt
	echo reverse:
	./out -n -r < ./lines.txt
	echo fold/ignorecase:
	./out -f < ./linesalphanum.txt
	echo directory order alpha numeric + ' ' only
	./out -d < ./linesalphanum.txt
	echo two fields
	cat ./linestwofields.txt | ./out -n -c1 | ./out -r -c2

out: input.c
	gcc -O0 -g *.c -o out
