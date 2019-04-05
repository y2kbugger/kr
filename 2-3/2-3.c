#include <stdio.h>
#include <limits.h>
#include <string.h>

/*
 * Exercise 2-3 write htoi(s) convert hex to int
 */

int htoi(char s[])
{
    unsigned long value = 0;
    unsigned int digitval, place;
    char *c;
    for (c = s; *c != '\0'; c++){}
    char *onesplace = c;
    for (c=c-1;  c>=s ; c--)
    {
        place=onesplace-c-1;
        digitval = *c - 48;
        value += (digitval * (1 << 4*place));

        printf("%d|\t%c:%x\n",place,*c, digitval);
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
    printf("%d\n", 16<<1);
    printf("\t\t%s:%x\n\n", "1", htoi("1"));
    printf("\t\t%s:%x\n\n", "2", htoi("2"));
    printf("\t\t%s:%x\n\n", "2", htoi("2"));
    printf("\t\t%s:%x\n\n", "20", htoi("20"));
    printf("\t\t%s:%x\n\n", "3", htoi("3"));
    printf("\t\t%s:%x\n\n", "333", htoi("333"));
    printf("\t\t%s:%x\n\n", "FF", htoi("FF"));
}
