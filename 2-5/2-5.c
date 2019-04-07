#include <stdio.h>
#include <limits.h>
#include <string.h>

/*
 * Exercise 2-5. Write the function any(s1,s2), which returns the first location in the string s1 where any charter from the string s2 occurs, or -1 if s1 contains no characters from s2. (standard library function strpbrk does the same job but returns a pointer to the location.)
 */

int any(char s1[], char s2[])
{
    int i, j, k;
    int found;
    for (i = j = 0; s1[i] != '\0'; i++)
    {
        found = 0;
        for (k = 0; s2[k] != '\0'; k++)
        {
            if (s1[i] == s2[k])
                return i;
        }
    }
    return -1;
}

void testit(char s1[], char s2[])
{
    printf("%s|%s:  %d\n", s1, s2, any(s1, s2));
}

int main()
{
    testit("hello", "oh");
    testit("worldhelloit is time to get up", "zxfsz");
    testit("worldhelloit is time to get up", "z");
    testit("worldhelloit is time to get up", "");
    testit("worldhelloit is time to get up", "elz");
}
