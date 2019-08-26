#include <stdio.h>
#include <string.h>

/*
 * Exercise 1-24. Write a program to check a C program for rudimentary
 * syntax errors like unbalanced parentheses, brackets and braces.
 * Don't forget about quotes, both single and double, escape
 * sequences, and comments. (This program is hard if you do it in full
 * generality.)
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
    printf("%c",'{');
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
                     *  0: doublequotes
                     *  1: comments
                     *  2: singlequotes
                     * */
    int c, b;
    int paren, square, curly;
    paren=square=curly=0;
    parsestate = -1;
    b = -1; /* previous c */
    while((c=getchar())!=EOF){
        switch (parsestate) {
            case -1:
                if(c=='"'&&b!='\\'&&b!='\'')
                    parsestate = 0;
                if(c=='*'&&b=='/')
                    parsestate = 1;
                if(c=='\''&&b!='\\')
                    parsestate = 2;
                break;
            case 0:
                if(c=='"'&&b!='\\'&&b!='\'')
                    parsestate = -1;
                break;
            case 1:
                if(c=='/'&&b=='*')
                    parsestate = -1;
                break;
            case 2:
                if(c=='\''&&b!='\\')
                    parsestate = -1;
                break;
        }
        b = c;
        if (c=='\n')
            putchar(c);
        else
            switch (parsestate) {
                case -1:
                    putchar('0');
                    break;
                case 0:
                    putchar('"');
                    break;
                case 1:
                    putchar('*');
                    break;
                case 2:
                    putchar('\'');
                    break;
            }
        if(parsestate>=0)
            continue;

        switch (c) {
            case '{':
                curly++;
                putchar(c);
                break;
            case '}':
                curly--;
                putchar(c);
                break;
            case '(':
                paren++;
                putchar(c);
                break;
            case ')':
                paren--;
                putchar(c);
                break;
            case '[':
                square++;
                putchar(c);
                break;
            case ']':
                square--;
                putchar(c);
                break;
        }
    }
    printf("{:%d, [%d, (%d", curly, square, paren);
}
