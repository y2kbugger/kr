#include <stdio.h>
#include <limits.h>
#include <string.h>

/*
 * Exercise 2-6. Write a function setbits(x,p,n,y) that returns x with the n bits that begin at position p set to the rightmost n bits of y, leaving the other bits unchanged.
 */

int setbits(int x, int p, int n, int y)
{
    // x: 10101010
    // p: 3
    // n: 2
    // y: 00000010
    // move the bits of y to the correct location
    //    01234567
    // y: 00010000 // y = y << width - p
    //
    // make a bitmask
    //    00011000
    // clear bits of x
    // add bits of the shifted y
}

void testit(char s1[], char s2[])
{
    printf("%s|%s:  %d\n", s1, s2, any(s1, s2));
}

int main()
{
    testit("hello", "oh");
    testit("worldhelloit is time to get up", "zxfsz");
    testit("worldhelloit is time to get up", "z");
    testit("worldhelloit is time to get up", "");
    testit("worldhelloit is time to get up", "elz");
}
