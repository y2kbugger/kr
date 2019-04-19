#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#define TESTREPS 1

/*
 * Exercise 3-3. Write a function expand(s1,s2) that expands shorthand notations like a-z in the string s1 into the equivalent complete list abc...xyz in s2. Allow for letters of either case and digits, and be prepared to handle cases like a-b-c and a-z0−9 and -a-z. Arrange that a leading or trailing - is taken literally.
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
    int i = 0, j = 0;
    for (; t[i] != '\0'; i++) {
        switch (t[i]) {
        case '\n':
            s[j++] = '\\';
            s[j++] = 'n';
            break;
        case '\t':
            s[j++] = '\\';
            s[j++] = 't';
            break;
        case '\r':
            s[j++] = '\\';
            s[j++] = 'r';
            break;
        case '\f':
            s[j++] = '\\';
            s[j++] = 'f';
            break;
        case '\v':
            s[j++] = '\\';
            s[j++] = 'v';
            break;
        case '\\':
            s[j++] = '\\';
            s[j++] = '\\';
            break;
        default:
            s[j++] = t[i];
            break;
        }
        /* printf("\n%d:%c", i, t[i]); */
    }
    s[j++] = '\0';
}

void unescape(char s[], char t[])
{
    int i = 0, j = 0;
    for (; t[i] != '\0'; i++) {
        if (t[i] != '\\') {
            s[j++] = t[i];
        } else {
            switch (t[++i]) {
            case 'n':
                s[j++] = '\n';
                break;
            case 't':
                s[j++] = '\t';
                break;
            case 'r':
                s[j++] = '\r';
                break;
            case 'f':
                s[j++] = '\f';
                break;
            case 'v':
                s[j++] = '\v';
                break;
            case '\\':
                s[j++] = '\\';
                break;
            default:
                s[j++] = '?';
                break;
            }
        }
    }
    s[j++] = '\0';
}

void testit(char t[])
{
    clock_t start, diff;
    int msec;
    start = clock();

    char s[99];
    char u[99];
    start = clock();

    for (int k = 0; k <= TESTREPS; k++) {
        escape(s, t);
        unescape(u, s);
    }
    /* diff = clock() - start; */
    /* msec = diff * 1000 / CLOCKS_PER_SEC; */
    /* printf("\n %4d msec", msec); */
    printf("\n%s:%s:%s", t, s, u);
}

int main()
{
    printf("\n%s:%s:%s", "in", "escape", "unescaped");
    testit("devo");
    testit("de\tvo");
    testit("de\\vo");
}
