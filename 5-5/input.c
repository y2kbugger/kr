#include <stdio.h>
#include <string.h>
#include <ctype.h>
/*
 * Exercise 5-5. Write versions of the library functions strncpy, strncat, and
 * strncmp, which operate on at most the first n characters of their argument
 * strings. For example, strncpy(s,t,n) copies at most n characters of t to s.
 * Full descriptions are in Appendix B.
 */

/* copy at most n characters of string ct to s;
 * Pad with ′\0′s if it has fewer than n characters. */
void *_strncpy(char *s, char *ct, int n)
{

    for (int i = 0; i < n; i++)
        *s++ = (*ct == '\0') ? '\0' : *ct++;
}

/* concatenate at most n characters of string ct to string s,
 * terminate s with ′\0′*/
void *_strncat(char *s, char *ct, int n)
{
    while (*s++)
        putchar(*s);

    _strncpy(--s, ct, n);
    *(s + n) = '\0';
}

/* compare at most n characters of string cs to string ct;
 * return <0 if cs<ct, 0 if cs==ct, or >0 if cs>ct. */
int _strncmp(char *s, char *ct, int n)
{
    return 0;
}

void testit(char *s, char *t, int n)
{
    printf("%s;%s;%d:\n", s, t, n);
    char si[200];
    char ti[200];

    /* strncpy */
    /* Make a backup to prevent functions from affection one another */
    strcpy(si, s);
    strcpy(ti, t);
    _strncpy(si, ti, n);
    printf("\tcpy:\t%s;%s\n", si, ti);

    /* strncat */
    strcpy(si, s);
    strcpy(ti, t);
    _strncat(si, ti, n);
    printf("\tcat:\t%s;%s\n", si, ti);

    /* strncmp */
    strcpy(si, s);
    strcpy(ti, t);
    _strncmp(si, ti, n);
    printf("\tcmp:\t%s;%s\n", si, ti);
}


int main()
{
    testit("", "", 0);
    testit("", "", 1);
    testit("", "", 2);
    testit("helloworld", "tacobell", 0);
    testit("helloworld", "tacobell", 1);
    testit("helloworld", "tacobell", 2);
    testit("helloworld", "tacobell", 50);

    for (int i = 0; i < 12; i++)
        testit("hello1", "hello2", i);

    for (int i = 0; i < 12; i++)
        testit("hello", "hello", i);

    for (int i = 0; i < 12; i++)
        testit("hello2", "hello1", i);
}
