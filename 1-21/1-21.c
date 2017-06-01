#include <stdio.h>
#include <string.h>

/* Exercise 1-21. Write a program entab that replaces strings of blanks by the minimum number of tabs and blanks to achieve the same spacing. Use the same tab stops as for detab. When either a tab or a single blank would suffice to reach a tab stop, which should be given preference? */

#define MAXLINE 222
#define TABSTOP 8

int getaline(char line[], int maxchars);
int detab(char line[], int maxchars);
int entab(char line[], int maxchars);

int main()
{
    char s[MAXLINE];
    int len;
    while((len = getaline(s, MAXLINE)) > 0) {
        detab(s, MAXLINE);
        printf("%s",s);
    }
    return 0;
}

int detab(char line[], int maxchars)
{
    int c;
    int i,j;
    j = 0;
    char linecopy[MAXLINE];
    strcpy(linecopy, line);
    for(i=0; i+j<=maxchars&&((c=linecopy[i])!=EOF)&&(c!='\n'); i++){
        if (c=='\t'){
            c=' ';
            while((i+j+1)%TABSTOP != 0){
                line[i+j]=c;
                j++;
            }
        }
        line[i+j]=c;
    }
    if (c=='\n'){
         line[i+j]=c;
         ++i;
    }
    line[i+j]='\0';
    return i+j;
}

int entab(char line[], int maxchars)
{
    int c;
    int i;
    for(i=0; i<=maxchars&&((c=getchar())!=EOF)&&(c!='\n'); i++){
        if (c==' '){
            c='\t';
            while((i+1)%TABSTOP != 0){
                i++;
            }
            line[i]=c;
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

int getaline(char line[], int maxchars)
{
    int c;
    int i;
    for(i=0; i<=maxchars&&((c=getchar())!=EOF)&&(c!='\n'); i++){
        line[i]=c;
    }
    if (c=='\n'){
         line[i]=c;
         ++i;
    }
    line[i]='\0';
    return i;
}
