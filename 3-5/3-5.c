#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <stdbool.h>

#define TESTREPS 1

/*
 * Exercise 3-5. Write the function itob(n,s,b) that converts the
 * integer n into a base b character representation in the string s. In
 * particular, itob(n,s,16) formats n as a hexadecimal integer in s.
 */

char digitchars[128];

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
    /* printf("Length: %d\n", i); */
    for (j = 0; (j < i / 2); ++j) {
        c = s[i - 1 - j];
        /* printf("j,c: %d, %c\n", j, c); */
        s[i - 1 - j] = s[j];
        s[j] = c;
    }
}

/* expands shorthand notations like a-z in the string s1 into the equivalent
 * complete list abc...xyz in s2. */
void expand(char s1[], char s2[])
{
    int i1 = 0, i2 = 0;
    char last = '\0', current, next;
    for (i1 = 0; s1[i1] != '\0'; i1++) {
        current = s1[i1];
        next = s1[i1 + 1];

        if (s1[i1] == '-') {
            /* Literal hyphens */
            if (last == '\0' || next == '\0') {
                s2[i2++] = '-';
                continue;
            }

            /* replace the hyphen with the full range of chars */
            while (last < next - 1) {
                s2[i2++] = ++last;
            }
        } else {
            /* normal chars */
            s2[i2++] = s1[i1];
        }

        last = current;
    }
    s2[i2++] = '\0';
}



void itob(int n, char s[], int b)
{
    int i, sign;
    long ln;
    ln = n;

    if ((sign = ln) < 0)        /* record sign */
        ln = -ln;
    i = 0;

    do {                        /* generate digits in reverse order */
        s[i++] = digitchars[ln % b];    /* get next digit */
    } while ((ln /= b) > 0);    /* delete it */
    if (sign < 0)
        s[i++] = '-';
    s[i++] = '\0';
    reverse(s);
}

void testit(int n, int b)
{
    clock_t start, diff;
    int msec;
    start = clock();

    char s[4448];
    start = clock();
    for (int k = 1; k <= TESTREPS; k++) {
        itob(n, s, b);
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
    expand("0-9A-Z", digitchars);
    printf("%s\n", digitchars);
    printf("%s:%s;\n", "in", "out");

    testit(1, 10);
    testit(1455, 10);
    testit(-1455, 10);

    testit(minint, 10);

    testit(0x555, 2);

    testit(0xAAA, 2);
    testit(0xAAA, 8);
    testit(0xAAA, 10);
    testit(0xAAA, 16);

    testit(0xFFF, 2);
    testit(0xFFF, 8);
    testit(0xFFF, 10);
    testit(0xFFF, 16);
    testit(-0xFFF, 16);
}
