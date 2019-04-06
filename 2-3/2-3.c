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

    // remove optional leading 0x
    if (s[0] == '0')
        if (s[1] == 'X' || s[1] == 'x')
            s += 2;

    // find the end of the string
    for (c = s; *c != '\0'; c++){}
    char *onesplace = c;

    // loop over each digit, summing the total, weighted by 16^0 for the lsd, then 16^1, 16^2, etc.
    for (c=c-1;  c>=s ; c--)
    {
        place=onesplace-c-1;
        if ('0'<=*c && *c<='9')
            digitval = *c - '0';
        else if ('a'<=*c && *c<='f')
            digitval = *c - 'a'+10;
        else if ('A'<=*c && *c<='F')
            digitval = *c - 'A'+10;
        else
            return -1;

        // do weighting
        value += (digitval * (1 << 4*place));

        // debug each digit
        printf("%d|\t%c:%x\n",place,*c, digitval);
    }
    return value;
}

int main()
{
    printf("\t\t%s:%x\n\n", "1", htoi("1"));
    printf("\t\t%s:%x\n\n", "2", htoi("2"));
    printf("\t\t%s:%x\n\n", "2", htoi("2"));
    printf("\t\t%s:%x\n\n", "20", htoi("20"));
    printf("\t\t%s:%x\n\n", "3", htoi("3"));
    printf("\t\t%s:%x\n\n", "333", htoi("333"));
    printf("\t\t%s:%x\n\n", "FF", htoi("FF"));
    printf("\t\t%s:%x\n\n", "ff", htoi("ff"));
    printf("\t\t%s:%x\n\n", "0xff", htoi("0xff"));
    printf("\t\t%s:%x\n\n", "0Xff", htoi("0Xff"));
    printf("\t\t%s:%x\n\n", "fqf", htoi("fqf"));
}
