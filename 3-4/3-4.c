#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <stdbool.h>

#define TESTREPS 1

/*
 * Exercise 3-4. In a two's complement number representation, our
 * version of itoa does not handle the largest negative number, that
 * is, the value of n equal to -(pow(2, WORDSIZE-1). Explain why not.
 * Modify it to print that value correctly, regardless of the machine
 * on which it runs.
 *
 *
 * The line:
 * n = -n
 * overflows the int
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
void itoa(int n, char s[])
{
    int i, sign;
    long ln;
    ln = n;

    if ((sign = ln) < 0)         /* record sign */
        ln = -ln;
    i = 0;

    do {                        /* generate digits in reverse order */
        s[i++] = ln % 10 + '0';  /* get next digit */
    } while ((ln /= 10) > 0);    /* delete it */
    if (sign < 0)
        s[i++] = '-';
    s[i++] = '\0';
    reverse(s);
}

void testit(int n)
{
    clock_t start, diff;
    int msec;
    start = clock();

    char s[4448];
    start = clock();
    for (int k = 1; k <= TESTREPS; k++) {
        itoa(n, s);
    }
    diff = clock() - start;
    msec = diff * 1000 / CLOCKS_PER_SEC;
    /* printf("\n %4d msec", msec); */
    printf(":%d:%s;\n", n, s);
}

int main()
{
    int wordsize = 8 * sizeof((int) 1);
    int minint = -(1 << (wordsize - 1));
    printf("%s:%s;\n", "in", "out");

    testit(1);
    testit(1455);
    testit(-1455);

    testit(minint);
}
