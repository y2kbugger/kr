#include <stdio.h>
#include <limits.h>
#include <string.h>

/*
 * Exercise 2-9. In a two’s complement number system, x &= (x−1) deletes the rightmost 1-bit in x. Explain why. Use this observation to write a faster version of bitcount.
 *
 * It is cause if there are zeros on tge right side it must borrow until it finds a 1bit.
 */

/* bitcount: count 1 bits in x */
int bitcount(unsigned x)
{
    int b;
    for (b = 0; x != 0; x >>= 1)
        if (x & 01)
            b++;
    return b;
}

int bitcount2(unsigned x)
{
    int b;
    for (b = 0; x != 0; x &= x - 1)
        b++;
    return b;
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

void testit(uint16_t x)
{

    print_binary(x);
    printf(":%d:%d", bitcount(x), bitcount2(x));
    printf("\n\n");
}

int main()
{
    testit(1);
    testit(0777);
    testit(0xf);
    testit(0xaaa);
}
