#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <stdbool.h>

#define TESTREPS 1

/*
 * Exercise 4-1. Write the function strrindex(s,t), which returns the position of the rightmost occurrence of t in s, or -1 if there is none.
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
int strrindex(char t, char s[])
{
    int i = -1;
    int j = -1;
    char c;
    while ((c=s[++j]))
        if (c == t)
            i = j;
    return i;
}

void testit(char t, char s[])
{
    clock_t start, diff;
    int msec, i;
    start = clock();

    start = clock();
    for (int k = 1; k <= TESTREPS; k++) {
        i = strrindex(t, s);
    }
    diff = clock() - start;
    msec = diff * 1000 / CLOCKS_PER_SEC;
    /* printf("\n %4d msec", msec); */
    printf("%c:%s;\t%d\n", t, s, i);
}

int main()
{
    printf("%s;\t%s\n", "in:in", "out");

    testit('z', "hello world");
    testit('z', "zello world");
    testit('z', "hello zorld");
    testit('z', "zello zorld");
    testit('z', "hezzo zorld");
    testit('z', "hezzo zorlz");
    testit('z', "");
}
