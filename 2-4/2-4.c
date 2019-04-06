#include <stdio.h>
#include <limits.h>
#include <string.h>

/*
 * Exercise 2-4. Write an alternate version of squeeze(s1,s2) that deletes
 * each character in s1 that matches any character in the string s2.
 */

void squeeze(char s1[], char s2[])
{
    int i, j, k;
    int found;
    for (i = j = 0; s1[i] != '\0'; i++)
    {
        found = 0;
        for (k = 0; s2[k] != '\0'; k++)
        {
            if (s1[i] == s2[k])
                found = 1;
        }
        if (!found)
            s1[j++] = s1[i];
    }
    s1[j] = '\0';
}

int main()
{
    char s[33];

    strcpy(s, "hello");
    printf("\t\t%s\n\n", s);
    squeeze(s, "o");
    printf("\t\t%s\n\n", s);

    strcpy(s, "hello");
    printf("\t\t%s\n\n", s);
    squeeze(s, "oh");
    printf("\t\t%s\n\n", s);
}
