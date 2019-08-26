#include <stdio.h>
#include <string.h>

/*
 * Exercise 1-23. Write a program to remove all comments from a C
 * program. Don't forget to handle quoted strings and character
 * constants properly. C comments do not nest.
 */

#define MAXLINE 222
#define FOLDLEN 20

void removecomments();

int main()
{
    char s[MAXLINE];
    int len;
    removecomments();
    return 0;
}

void deadcode(){
    printf("%c",'"');
    printf("comment in string /*   lol */");
    int foobar;     /* flag for what kind of region */
                    /* single flag because comments */
                    /* mutually exclusive. */
}

void removecomments(){
    int parsestate; /* flag for what kind of region we are in.  use
                     * single flag because comments and strings are
                     * mutually exclusive.
                     * -1: normal code
                     *  0: strings
                     *  1: comments
                     * */
    int c, b;
    parsestate = -1;
    b = -1; /* previous c */
    while((c=getchar())!=EOF){
        switch (parsestate) {
            case -1:
                if(c=='"'&&b!='\\'&&b!='\'')
                    parsestate = 0;
                if(c=='*'&&b=='/')
                    parsestate = 1;
                break;
            case 0:
                if(c=='"'&&b!='\\'&&b!='\'')
                    parsestate = -1;
                break;
            case 1:
                if(c=='/'&&b=='*')
                    parsestate=b=c=-1;
                break;
        }
        if(parsestate<1 && b!=-1)
            putchar(b);
        b = c;
    }
    if(parsestate<1 && b!=-1)
        putchar(b);
}
