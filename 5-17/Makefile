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
	echo two fields \(First field only\)
	cat ./linestwofields.txt | ./out -n -c 1
	echo two fields \(second field only\)
	cat ./linestwofields.txt | ./out -n -c 2
	echo two fields \(Both fields, different settings\)
	cat ./linestwofields.txt |  ./out -r -c 2 | ./out -n -c 1

out: input.c
	gcc -O0 -g *.c -o out
