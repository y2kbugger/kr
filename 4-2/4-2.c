#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <stdbool.h>

#include <ctype.h>

#define TESTREPS 1

/*
 * Exercise 4-2. Extend atof to handle scientific notation of tge form 123.45e-6 where a floating-point number may be followed by e or E and an optionally signed exponent.
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

/* atof: convert string to float */
double atof2(char s[])
{
    double val, power, exponent;
    int i, sign, expsign;
    for (i = 0; isspace(s[i]); i++)     /* skip white space */
        ;
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;
    for (val = 0.0; isdigit(s[i]); i++)
        val = 10.0 * val + (s[i] - '0');
    if (s[i] == '.')
        i++;
    for (power = 1.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
        power *= 10.0;
    }
    if (s[i] == 'e' || s[i] == 'E')
        i++;
    expsign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;
    for (exponent = 0; isdigit(s[i]); i++) {
        exponent = 10.0 * exponent + (s[i] - '0');
    }
    val = sign * val / power;
    while (exponent-- > 0) {
        if (expsign > 0)
            val *= 10;
        else
            val /= 10;
    }
    return val;

}

void testit(char s[])
{
    clock_t start, diff;
    int msec;
    double i;
    start = clock();

    start = clock();
    for (int k = 1; k <= TESTREPS; k++) {
        i = atof2(s);
    }
    diff = clock() - start;
    msec = diff * 1000 / CLOCKS_PER_SEC;
    /* printf("\n %4d msec", msec); */
    printf("%s;\t%f\n", s, i);
}

int main()
{
    printf("%s;\t%s\n", "in", "out");

    testit("1");
    testit("1.0");
    testit("1.1");
    testit("9.1");
    testit("11.1");
    testit("1.");
    testit("1.9");
    testit("1.1e-3");
    testit("1.1e-2");
    testit("1.1e-1");
    testit("1.1e-0");
    testit("1.1e0");
    testit("1.1e1");
    testit("1.1e2");
    testit("1.1e3");
    testit("1.1e33");

    testit("1.1E2");
}
