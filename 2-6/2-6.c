#include <stdio.h>
#include <limits.h>
#include <string.h>

/*
 * Exercise 2-6. Write a function setbits(x,p,n,y) that returns x with the n bits that begin at position p set to the rightmost n bits of y, leaving the other bits unchanged.
 */

unsigned int setbits(unsigned int x, int p, int n, int y)
{
    // x: 10101010
    // p: 3
    // n: 2
    // y: 00000010

    // move the bits of y to the correct location
    //    76543210
    // y: 00001000
    y = y << (p+1-n);
    // make a bitmask
    //    00001100
    // clear bits of x
    unsigned m;
    m = ~0;
    // m: 11111111
    m = m << (p+1 - n);
    // m: 11111100
    m = ~m;
    // m: 00000011
    m = m << n;
    // m: 00001100
    return (x&~m)|(y&m);

    // add bits of the shifted y
}

void testit(char s1[], char s2[])
{
    printf("%d\n", setbits(0, 3, 2, 0777));
    printf("%d\n", setbits(07777, 3, 2, 0));
}

int main()
{
    testit("hello", "oh");
}
