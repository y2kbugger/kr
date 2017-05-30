#include <stdio.h>

/* Exercise 1-20. Write a program detab that replaces tabs in the input with the proper number of blanks to space to the next tab stop. Assume a fixed set of tab stops, say every n columns. Should n be a variable or a symbolic parameter? */

#define MAXLINE 222
#define TABSTOP 8

int getaline(char line[], int maxchars);

int main()
{
    char s[MAXLINE];
    int len;
    while((len = getaline(s, MAXLINE)) > 0) {
        printf("%s",s);
    }
    return 0;
}

int getaline(char line[], int maxchars)
{
    int c;
    int i;
    for(i=0; i<=maxchars&&((c=getchar())!=EOF)&&(c!='\n'); i++){
        if (c=='\t'){
            c=' ';
            while((i+1)%TABSTOP != 0){
                line[i]=c;
                i++;
            }
        }
        line[i]=c;
    }
    if (c=='\n'){
         line[i]=c;
         ++i;
    }
    line[i]='\0';
    return i;
}
