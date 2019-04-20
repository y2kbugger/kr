#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#define TESTREPS 1

/*
 * Exercise 3-3. Write a function expand(s1,s2) that expands shorthand
 * notations like a-z in the string s1 into the equivalent complete list
 * abc...xyz in s2. Allow for letters of either case and digits, and be
 * prepared to handle cases like a-b-c and a-z0−9 and -a-z. Arrange that a
 * leading or trailing - is taken literally.
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

void expand(char s1[], char s2[])
{
    int i = 0, j = 0;
    for (; s2[i] != '\0'; i++) {
        switch (s1[i]) {
        case '-':
            s2[j++] = s1[i];
            putchar('*');
            break;
        default:
            s2[j++] = s1[i];
            break;
        }
    }
    s2[j++] = '\0';
}

void testit(char s1[])
{
    clock_t start, diff;
    int msec;
    start = clock();

    char s2[256];
    start = clock();
    for (int k = 0; k <= TESTREPS; k++) {
        expand(s1, s2);
    }
    /* diff = clock() - start; */
    /* msec = diff * 1000 / CLOCKS_PER_SEC; */
    /* printf("\n %4d msec", msec); */
    printf("\n%s:%s", s1, s2);
}

int main()
{
    printf("\n%s:%s", "in", "out");
    testit("a");
    testit("b");
    testit("-a");               /* leading */
    testit("a-");               /* trailing */
    testit("a-b");
    testit("1");
    testit("2");
    testit("0");
    testit("A");
    testit("B");
    testit("AB");
    testit("A-B");
    testit("A-B");
    testit("a-b-c");
    testit("a-z0−9");
    testit("-a-z.");
}
