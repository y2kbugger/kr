#include <stdio.h>
#include <string.h>
#include <ctype.h>
/*
 * Exercise 5-4. Write the function strend(s,t), which returns 1 if
 * the string t occurs at the end of the string s, and zero otherwise.
 */

int strend(char *s, char *t)
{
    char *s_init = s;
    char *t_init = t;

    /* find end of strings */
    while (*++s);
    while (*++t);

    printf("\n");
    /* compare t to end of s */
    while (1) {
        --t, --s;

        printf("\t\t%c:%c\n", *s, *t);

        if (*s != *t) {
            printf("There was a real char mismatch\n");
            return 0;
        }

        if (t == t_init)
            return 1;

        /* s ended before t */
        if (s == s_init) {
            printf("s ran out of chars\n");
            return 0;
        }

    }
    return 1;
}

void testit(char *s, char *t, int expected)
{
    printf("%s;%s:", s, t);
    int actual = strend(s, t);
    printf("\t\t\t%d:%d\n\n\n", actual, expected);
}


int main()
{
    testit("", "a", 0);
    testit("a", "", 0);
    testit("a", "ab", 0);
    testit("ab", "a", 0);
    testit("one", "two", 0);
    testit("taco", "bell", 0);
    testit("tacobell", "nachosbellgrande", 0);
    testit("tacobell", "bell", 1);
    testit("tacobell", "bella", 0);
    testit("bell", "bell", 1);
    testit("bell", "belb", 0);
    testit("bell", "abell", 0);
}
