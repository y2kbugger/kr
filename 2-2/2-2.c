#include <stdio.h>
#include <limits.h>

/*
 * Exercise 2-2 rewrite the loop without && or ||
 */

int main()
{
    int lim=5;
    char s[lim+1];
    int c;
    int i;
    for (i=0; i<lim && (c=getchar()) != '\n' && c != EOF; ++i)
        s[i] = c;
    s[i+1] = '\0';
    printf("%s\n", s);

    i=0;
    while  (c=getchar())
    {
        if (i >= lim) break;
        if (c == '\n') break;
        if (c == EOF) break;
        s[i] = c;
        i++;
    }
    s[i+1] = '\0';
    printf("%s\n", s);
}
