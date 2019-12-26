.PHONY: all
all: dcl undcl;

dcl: dcl.c dclcore.o
	gcc dcl.c dclcore.c -o dcl

undcl: undcl.c dclcore.o
	gcc undcl.c dclcore.c -o undcl

testdcl: dcl
	@echo
	@echo -------------
	echo 'char **argv' | ./dcl
	@echo 'argv:  pointer to pointer to char'
	@echo
	@echo -------------
	echo 'int (*daytab)[13]' | ./dcl
	@echo 'daytab:  pointer to array[13] of int'
	@echo
	@echo -------------
	echo 'int *daytab[13]' | ./dcl
	@echo 'daytab:  array[13] of pointer to int'
	@echo
	@echo -------------
	echo 'void *comp()' | ./dcl
	@echo 'comp:  function returning pointer to void'
	@echo
	@echo -------------
	echo 'void (*comp)()' | ./dcl
	@echo 'comp:  pointer to function returning void'
	@echo
	@echo -------------
	echo 'char (*(*x())[])()' | ./dcl
	@echo 'x:  function returning pointer to array[] of pointer to function returning char'
	@echo
	@echo -------------
	echo 'char (*(*x[3])())[5]' | ./dcl
	@echo 'x:  array[3] of pointer to function returning pointer to array[5] of char'
	
	@echo 'Now for invalid inputs'
	@echo 'Missing closing paren.'
	echo 'char (*(*x[3])()[5]' | ./dcl

clean:
	rm *.o *~
