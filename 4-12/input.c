#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <stdbool.h>

#define TESTREPS 1

/*
 * Exercise 4-12. Adapt the ideas of printd to write a recursive version of
 * itoa; that is, convert an integer into a string by calling a recursive
 * routine.
 *
 *
 */

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

void reverse(char s[])
/* reverse a string in place*/
{
    int c, i, j;
    for (i = 0; (c = s[i]) != '\0'; ++i) {
    }
    printf("Length: %d\n", i);
    for (j = 0; (j < i / 2); ++j) {
        c = s[i - 1 - j];
        /* printf("j,c: %d, %c\n", j, c); */
        s[i - 1 - j] = s[j];
        s[j] = c;
    }
}

/* itoa: convert n to characters in a s */
int itoa(long n, char s[], int i)
{
    printf("entering itoa, %ld, %s, %d\n", n, s, i);
    if (n < 0) {
        n = -n;
        s[i++] = '-';
    }

    char c = n % 10 + '0';      /* get next digit */
    if ((n /= 10) > 0)          /* delete it */
        i = itoa(n, s, i);
    s[i++] = c;
    s[i + 1] = '\0';
    return i;
}


void testit(long n)
{
    char s[100];
    itoa(n, s, 0);
    printf(":%ld:%s;\n", n, s);
}

int main()
{
    int wordsize = 8 * sizeof((int) 1);
    int minint = -(1 << (wordsize - 1));
    printf("%s:%s;\n", "in", "out");

    testit(1L);
    testit(1455L);
    testit(-1455L);

    testit(minint);
}
