#include <stdio.h>
#include <string.h>
#include <ctype.h>
/*
 * Exercise 5-3. Write a pointer version of the function strcat that we showed
 * in Chapter 2: strcat(s,t) copies the string t to the end of s.
 */


/* strcat: concatenate t to end of s; s must be big enough */
void strcat_ch2(char s[], char t[])
{
    int i, j;

    i = j = 0;
    while (s[i] != '\0')        /* find end of s */
        i++;
    while ((s[i++] = t[j++]) != '\0')   /* copy t */
        ;
}

void strcat_new(char *s, char *t)
{
    while (*++s)                /* find end of s */
        ;

    while ((*s++ = *t++))       /* copy t */
        ;
}

void testit(char *si, char *t)
{
    printf("%s;%s:", si, t);

    char s[333];
    strcpy(s, si);

    /* old version */
    strcat_ch2(s, t);
    printf("%s", s);

    /* new version */
    strcpy(s, si);
    strcat_new(s, t);
    printf("|%s\n", s);
}


int main()
{
    testit("one", "two");
    testit("taco", "bell");
}
