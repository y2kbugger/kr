#include <stdio.h>
#include <limits.h>
#include <string.h>

/*
 * Exercise 2-9. In a two’s complement number system, x &= (x−1) deletes the rightmost 1-bit in x. Explain why. Use this observation to write a faster version of bitcount.
 *
 * It is cause if there are zeros on tge right side it must borrow until it finds a 1bit.
 */

/* lower: convert c to lower case; ASCII only */
int lower(int c)
{
    if (c >= 'A' && c <= 'Z')
        return c + 'a' - 'A';
    else
        return c;
}

int lower2(int c)
{
    int upper;
    upper = (c >= 'A' && c <= 'Z');
    return upper ? c + 'a' - 'A' : c;
}


const char *bit_rep[16] = {
    [0] = "0000",[1] = "0001",[2] = "0010",[3] = "0011",
    [4] = "0100",[5] = "0101",[6] = "0110",[7] = "0111",
    [8] = "1000",[9] = "1001",[10] = "1010",[11] = "1011",
    [12] = "1100",[13] = "1101",[14] = "1110",[15] = "1111",
};

void print_binary(uint16_t byte)
{
    printf("%s%s%s%s",
           bit_rep[(byte & 0xF000) >> 12],
           bit_rep[(byte & 0x0F00) >> 8],
           bit_rep[(byte & 0x00F0) >> 4], bit_rep[(byte & 0x000F) >> 0]
        );
}

/* void testit(uint16_t x) */
void testit(char x)
{

    /* print_binary(x); */
    printf("%c:%c:%c", x, lower(x), lower2(x));
    printf("\n");
}

int main()
{
    testit('a');
    testit('A');
    testit('z');
    testit('Z');
}
