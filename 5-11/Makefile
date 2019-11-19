run: out
	./out || echo "This is supposed to fail, because we didn't specify mode"
	cat entabtests | xargs -n2 sh -c 'cat entabtestsdata | ./out e $@ | cat -T'
out: *.c
	gcc -g -Wall -lm *.c -o out
