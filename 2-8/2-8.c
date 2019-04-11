#include <stdio.h>
#include <limits.h>
#include <string.h>

/*
 * Exercise 2-8. Write a function rightrot(x,n) that returns the value of the integer x rotated to the right by n bit positions.
 */

uint16_t rightrot(uint16_t x, int n)
{
    /* uint16_t l,r; */
    int ls, rs;
    int w = 16;
    rs = n%w;
    ls = w - rs;
    return x<<ls|x>>rs;

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

void testit(uint16_t x, int n)
{

    print_binary(x);
    printf(":%d\n", n);
    print_binary(rightrot(x,n));
    printf("\n\n");
}

int main()
{
    testit(1, 0);
    testit(1, 1);
    testit(1, 15);
    testit(1, 16);
    testit(0x1B6, 3);
}
