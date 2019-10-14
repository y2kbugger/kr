#include <stdio.h>
#include <string.h>
#include <ctype.h>
/*
 * Exercise 5-4. Write the function strend(s,t), which returns 1 if
 * the string t occurs at the end of the string s, and zero otherwise.
 */


/* strcat: concatenate t to end of s; s must be big enough */

int strend(char *s, char *t)
{
    return 1;
}

void testit(char *s, char *t, int expected)
{
    printf("%s;%s:", s, t);
    int actual = strend(s, t);
    printf("|%d:%d\n", actual, expected);
}


int main()
{
    testit("", "a", 0);
    testit("a", "", 0);
    testit("one", "two", 0);
    testit("taco", "bell", 0);
    testit("tacobell", "nachosbellgrande", 0);
    testit("tacobell", "bell", 1);
    testit("tacobell", "bella", 0);
}
