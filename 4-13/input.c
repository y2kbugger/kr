#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

/*
 * Exercise 4-13. Write a recursive version of the function reverse(s), which
 * reverses the string s in place.
 */


void reverse(char s[], int i, int j)
/* reverse a string in place*/
{
    int c;

    /* reversed up to the halfway point */
    if (j >= i / 2)
        return;

    c = s[i - 1 - j];
    s[i - 1 - j] = s[j];
    s[j] = c;
    reverse(s, i, j + 1);
}

void testit(char q[])
{
    char s[100];
    strcpy(s, q);
    printf(":%s", s);
    reverse(s, strlen(s), 0);
    printf(":%s;\n", s);
}

int main()
{
    testit("abba");
    testit("a man a plan a canal panama");
    testit("zak and sara");
}
