#include <stdio.h>
/* #include "otherfile.h" */

/*
 * Testing extern and static
 */

extern int c;

int main()
{
    c +=3;

    printf("hello ddworld %d\n", c);
}
