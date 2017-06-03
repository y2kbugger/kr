#include <stdio.h>
#include <string.h>

/*
 * Exercise 1-23. Write a program to remove all comments from a C
 * program. Don't forget to handle quoted strings and character
 * constants properly. C comments do not nest.
 */

#define MAXLINE 222
#define FOLDLEN 20

int foldline(char line[], int maxchars);

int main()
{
    char s[MAXLINE];
    int len;
    printf("comment in string /*   lol */");
    while(fgets(s, MAXLINE, stdin)) {
        foldline(s, MAXLINE);
        printf("%s",s);
    }
    return 0;
}
void removecomments(){
    int instring; /* flag for if instring */
    int incomment;
    instring = 0;
    incomment = 0;
    while((c=getchar())!=EOF)
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


