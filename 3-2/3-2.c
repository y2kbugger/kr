#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define TESTREPS 1

/*
 *Exercise 3-2. Write a function escape(s,t) that converts characters like newline and tab into visible escape sequences like \n and \t as it copies the string t to s. Use a switch. Write a function for the other direction as well, converting escape sequences into the real characters.
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

void escape(char s[], char t[])
{
    int i;
    for (i = 0; t[i] != '\0'; i++) {
        s[i] = t[i];
        /* printf("\n%d:%c", i, t[i]); */
    }
    s[i] = '\0';
}

void testit(char t[])
{
    clock_t start, diff;
    int msec;
    start = clock();

    char s[99];
    start = clock();

    for (int k = 0; k < TESTREPS; k++) {
        escape(s, t);
    }
    diff = clock() - start;
    msec = diff * 1000 / CLOCKS_PER_SEC;
    printf(" %4d msec", msec);
    printf(" %s:%s", t, s);
}

int main()
{
    testit("devo");
}
