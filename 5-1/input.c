#include <stdio.h>
#include <string.h>
#include <ctype.h>
/*
 * Exercise 5-1. As written, getint treats a + or - not followed by a digit as
 * a valid representation of zero. Fix it to push such a character back on the
 * input.
 */




#define BUFSIZE 200
int buf[BUFSIZE];               /* buffer for ungetch */
int bufp = 0;                   /* next free position in buf */

int getch(void)
{                               /* get a (possibly pushed back) character */
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{                               /* push character back on input */
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

void ungets(char s[])
{                               /* push string back on input */
    for (int i = strlen(s) - 1; i >= 0; i--) {
        ungetch(s[i]);
    }
}


void fake_buffer(char s[])
{

    /* push back the fake input */
    ungetch(EOF);
    ungetch('\n');
    ungets(s);

}

int getint(int *pn)
/* getint: get next integer fro the input into *pn */
{
    int c, sign;

    while (isspace(c = getch()))        /* skip white space */
        ;

    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetch(c);             /* it's not a number */
        return 1;
    }
    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-')
        c = getch();
    if (!isdigit(c)) {
        ungetch(c);
        return 1;
    }
    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + (c - '0');
    *pn *= sign;
    if (c != EOF)
        ungetch(c);
    return 0;
}

void testit(char s[])
{
    printf("%s;", s);
    fake_buffer(s);
    int i;
    if (!getint(&i))
        printf("int found:%d", i);
    else
        printf("no int found.");
    printf("\n");
}


int main()
{
    testit("");
    testit("2");
    testit("22");
    testit("+22");
    testit("-22");
    testit("-p333");

}
