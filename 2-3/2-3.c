#include <stdio.h>
#include <limits.h>
#include <string.h>

/*
 * Exercise 2-3 write htoi(s) convert hex to int
 */

int htoi(char s[])
{
    long value = 0;
    char *c;
    for (c = s; *c !='\0'; c++)
    {
        value += *c - 48;
        putchar(*c);
        putchar('\n');
    }
    return value;
}

int main()
{
    /* int lim=99; */
    /* char s[lim+1]; */
    /* strcpy(s, "0xFF"); //255 */
    /* int c; */
    /* c = htoi(s); */
    printf("%s:%x\n", "1", htoi("1"));
    printf("%s:%x\n", "2", htoi("2"));
    printf("%s:%x\n", "3", htoi("3"));
    printf("%s:%x\n", "333", htoi("333"));
    printf("%s:%x\n", "FF", htoi("FF"));
}
