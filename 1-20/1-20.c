#include <stdio.h>

/* Exercise 1-20. Write a program detab that replaces tabs in the input with the proper number of blanks to space to the next tab stop. Assume a fixed set of tab stops, say every n columns. Should n be a variable or a symbolic parameter? */

#define MAXLINE 222

void getaline(char line[], int maxchars);

int main()
{
    putchar('h');
    char s[MAXLINE];
    getaline(s, MAXLINE);
    putchar('h');
    return 0;
}

void getaline(char line[], int maxchars)
{
    int c;
    int i;
    for(i=1; (c=getchar())!=EOF; i++){
        putchar(c);
    }
}
