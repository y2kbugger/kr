#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

/*
 * Exercise 4-14. Define a macro swap(t,x,y) that interchanges two arguments of
 * type t. (Block structure will help.)
 */


void testit()
{
    swap(int, 4, 5);
}

int main()
{
    testit();
}
