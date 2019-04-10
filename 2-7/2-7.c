#include <stdio.h>
#include <limits.h>
#include <string.h>

/*
 * Exercise 2-7. Write a function invert(x,p,n) that returns x with the n bits that begin at position p inverted (i.e., 1 changed into 0 and vice versa), leaving the others unchanged.
 */

uint16_t invert(uint16_t x, int p, int n)
{
    // x: 10101010
    // p: 3
    // n: 2
    //    76543210
    // make a bitmask
    //    00011000
    uint16_t m;
    m = ~((~0 << n)) << (p+1-n);
    uint16_t y, xx;
    y = ~x & m;
    x = x & ~m;
    return y|x;

}
const char *bit_rep[16] = {
    [ 0] = "0000", [ 1] = "0001", [ 2] = "0010", [ 3] = "0011",
    [ 4] = "0100", [ 5] = "0101", [ 6] = "0110", [ 7] = "0111",
    [ 8] = "1000", [ 9] = "1001", [10] = "1010", [11] = "1011",
    [12] = "1100", [13] = "1101", [14] = "1110", [15] = "1111",
};

void print_binary(uint16_t byte)
{
    printf("%s%s%s%s",
        bit_rep[(byte & 0xF000) >> 12],
        bit_rep[(byte & 0x0F00) >>  8],
        bit_rep[(byte & 0x00F0) >>  4],
        bit_rep[(byte & 0x000F) >>  0]
        );
}

void testit(uint16_t x, int p, int n)
{

    print_binary(x);
    printf(";%d;%d: ", p,n);
    print_binary(invert(x,p,n));
    printf("\n");
}

int main()
{
    testit(077777, 3, 2);
    testit(077777, 6, 2);
}
