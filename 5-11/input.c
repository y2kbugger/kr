#include <stdio.h>
#include <string.h>

/* Exercise 1-21. Write a program entab that replaces strings of blanks by the minimum number of tabs and blanks to achieve the same spacing. Use the same tab stops as for detab. When either a tab or a single blank would suffice to reach a tab stop, which should be given preference? */

#define MAXLINE 222
#define TABSTOP 8

int detab(char line[], int maxchars);
int entab(char line[], int maxchars);

int main()
{
    char s[MAXLINE];
    int len;
    while(fgets(s, MAXLINE, stdin)) {
        //detab(s, MAXLINE);
        //printf("%s",s);
        entab(s, MAXLINE);
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
    int i,j;
    int consecutive_blanks;
    j = 0;
    char linecopy[MAXLINE];
    detab(line, MAXLINE);
    strcpy(linecopy, line);
    for(i=0; i+j<=maxchars&&((c=linecopy[i+j])!=EOF)&&(c!='\n'); i++){
        consecutive_blanks = 0;
        while(c==' '){
            j++;
            consecutive_blanks++;
            if((i+j+1)%TABSTOP == 0){
                line[i]='\t';
                i++;
                consecutive_blanks = 0;
            }
            c=linecopy[i+j];
        }
        for(; consecutive_blanks>0; consecutive_blanks--){
            line[i]=' ';
            i++;
            j--;
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

