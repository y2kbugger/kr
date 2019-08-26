#include <stdio.h>
#include <string.h>

/* Exercise 1-22. Write a program to fold long input lines into two or more shorter lines after the last non-blank character that occurs before the n-th column of input. Make sure your program does something intelligent with very long lines, and if there are no blanks or tabs before the specified column. */

#define MAXLINE 222
#define FOLDLEN 20

int foldline(char line[], int maxchars);

int main()
{
    char s[MAXLINE];
    int len;
    while(fgets(s, MAXLINE, stdin)) {
        foldline(s, MAXLINE);
        printf("%s",s);
    }
    return 0;
}

int foldline(char line[], int maxchars)
{
    int c;
    int in, out, column;
    in = out = column = 0;
    int lastnonblank;
    lastnonblank = -1;
    char linecopy[MAXLINE];
    strcpy(linecopy, line);
    while(out <= maxchars && ((c=linecopy[in])!='\n')){
        line[out]=c;
        if (c=='\t' || c==' '){
            lastnonblank = out;
        }
        if(c=='\t')
            while((column)%FOLDLEN != 0){
                column++;
            }
//        printf("%d, %d, %d, %c\n", column, in, lastnonblank, c);
        if((column)>=FOLDLEN){
            if(lastnonblank==-1){
                line[out]='\n';
                out++;
                column=0;
            } else{
                line[lastnonblank]='\n';
                column=in-lastnonblank;
            }
            lastnonblank = -1;
        }

        in++;
        column++;
        out++;
    }
    if (c=='\n'){
         line[out]=c;
         out++;
    }
    line[out]='\0';
    return out;
}


