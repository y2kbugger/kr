.PHONY: all
all: dcl undcl;

dcl: dcl.c dclcore.o
	gcc dcl.c dclcore.c -o dcl

undcl: undcl.c dclcore.o
	gcc undcl.c dclcore.c -o undcl

clean:
	rm *.o *~
