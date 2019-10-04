#include <stdio.h>
#include <string.h>
#include <ctype.h>
/*
 * Exercise 5-2. Write getfloat, the floating-point analog of getint. What type does the getfloat return as its function value?
 *
 * Answer: getfloat should still return int because it is used as the status of the return.
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
    /* ungetch('\n'); */
    ungets(s);
}

int getfloat(float *pn)
/* getfloat: get next float from the input into *pn */
{
    int c, sign;

    while (isspace(c = getch()))        /* skip white space */
        ;

    if (EOF == c)
        return EOF;

    if (!isdigit(c) && c != '+' && c != '-' && c != '.') {
        ungetch(c);             /* it's not a number */
        return 1;
    }

    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-') {
        c = getch();
        if (!isdigit(c)) {
            ungetch(c);
            ungetch((sign == -1) ? '-' : '+');
            return 2;
        }
    }

    for (*pn = 0.0; (isdigit(c) && c != '.'); c = getch())
        *pn = 10 * *pn + (c - '0');
    if (c == '.') {
        float scale = 1;
        c = getch();
        for (; (isdigit(c)); c = getch()) {
            *pn = 10 * *pn + (c - '0');
            scale /= 10;
        }
        *pn *= scale;
    }
    *pn *= sign;

    ungetch(c);
    return 0;
}

void testit(char s[])
{
    printf("%s;", s);
    fake_buffer(s);
    float i;
    int retval = 0;
    while (1) {
        retval = getfloat(&i);
        if (retval == 0)
            printf("float:\"%f\"", i);
        else if (retval == 1)
            putchar(getch());
        else if (retval == 2)
            putchar(getch());
        if (retval == EOF)
            break;
    }
    printf("\n");
}


int main()
{
    testit("1 2 3");
    testit("2");
    /* testit(""); */
    /* testit(" "); */
    /* testit("jkjj"); */
    testit("2");
    testit("1 2 3");
    testit("1,2,3");
    testit("22");
    testit("+22");
    testit("-22");
    testit("-p333");
    testit("3.14159");
    testit("-3.14159");
    testit(" -3.14159");
    testit("\t9993.14159");
    testit("3.");
    testit("3. ");
    testit("3.j");
    testit("3.j ");
    testit(".2");
    testit(" .2");

}
