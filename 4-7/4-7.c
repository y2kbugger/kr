#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>             /* for atof() */
#include <stdint.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>

#include <ctype.h>

/*
 * Exercise 4-7. Write a routine ungets(s) that will push basck an entire
 * string onto the input. Should ungets know about buf and bufp, or should it
 * just use ungetch?
 */

const char *bit_rep[16] = {
    [0] = "0000",[1] = "0001",[2] = "0010",[3] = "0011",
    [4] = "0100",[5] = "0101",[6] = "0110",[7] = "0111",
    [8] = "1000",[9] = "1001",[10] = "1010",[11] = "1011",
    [12] = "1100",[13] = "1101",[14] = "1110",[15] = "1111",
};

void print_binary(uint16_t byte)
{
    printf("%s%s%s%s",
           bit_rep[(byte & 0xF000) >> 12],
           bit_rep[(byte & 0x0F00) >> 8],
           bit_rep[(byte & 0x00F0) >> 4], bit_rep[(byte & 0x000F) >> 0]
        );
}

void reverse(char s[])
/* reverse a string in place*/
{
    int c, i, j;
    for (i = 0; (c = s[i]) != '\0'; ++i) {
    }
    printf("Length: %d\n", i);
    for (j = 0; (j < i / 2); ++j) {
        c = s[i - 1 - j];
        /* printf("j,c: %d, %c\n", j, c); */
        s[i - 1 - j] = s[j];
        s[j] = c;
    }
}

#define MAXOP 100               /* max size of operand or operator */
#define NUMBER '0'              /* signal that a number was found */

int getop(char[]);
void push(double);
double pop(void);
int sp;                         /* next free stack position */
double val[];                   /* value stack */
double var[256];                /* var array */

/* reverse Polish calculator */
int calculator()
{
    int type;
    double op1;
    double op2;
    char s[MAXOP];

    while ((type = getop(s)) != EOF && type != '\0') {
        switch (type) {
        case NUMBER:
            push(atof(s));
            break;
        case '>':              /* Variables store */
            op1 = pop();
            printf("\tStoring %.8g into %c\n", op1, s[0]);
            var[(int) s[0]] = op1;
            break;
        case '@':              /* Variables use */
            op1 = var[(int) s[0]];
            printf("\tRestoring %.8g from %c\n", op1, s[0]);
            push(op1);
            break;
        case '=':              /* peek at top of stack */
            op1 = pop();
            printf("\t%.8g\n", op1);
            var[(int) '@'] = op1;       /* store in recent var '@' */
            push(op1);
            break;
        case 'd':              /* duplicate top of stack */
            op1 = pop();
            push(op2);
            push(op2);
            break;
        case 's':              /* swap top 2 stack */
            op1 = pop();
            op2 = pop();
            push(op1);
            push(op2);
            break;
        case 'c':              /* clear stack */
            sp = 0;
            break;
        case '+':
            push(pop() + pop());
            break;
        case '*':
            push(pop() * pop());
            break;
        case '-':
            op2 = pop();
            push(pop() - op2);
            break;
        case '/':
            op2 = pop();
            if (op2 != 0.0)
                push(pop() / op2);
            else
                printf("error: zero divisor\n");
            break;
        case '%':
            op2 = pop();
            push(fmod(pop(), op2));
            break;
        case 'e':              /* exp */
            push(exp(pop()));
            break;
        case 'n':              /* sin */
            push(sin(pop()));
            break;
        case 'p':              /* pow */
            op2 = pop();
            push(pow(pop(), op2));
            break;
        case '\n':
            /* pop, print, and store in recent var '@' */
            op1 = pop();
            printf("\t%.8g\n", op1);
            var[(int) '@'] = op1;       /* store in recent var '@' */
            break;
        default:
            printf("error: unknown command %s\n", s);
            break;
        }
    }
    return 0;
}

#define MAXVAL 100              /* maximum depth of val stack */

int sp = 0;                     /* next free stack position */
double val[MAXVAL];             /* value stack */

/* push: push f onto value stack */
void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("Error: stack full, can't push %g\n", f);
}

/* pop: pop and return top value from stack */
double pop(void)
{
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

int getch(void);
void ungetch(int);

/* getop: get next operator or numeric operand */
int getop(char s[])
{
    int i, c;
    while ((s[0] = c = getch()) == ' ' || c == '\t');
    if (c == '@' || c == '>') { /* variables */
        s[0] = getch();
        s[1] = '\0';
        return c;
    }

    s[1] = '\0';
    if (!isdigit(c) && c != '.' && c != '-')
        return c;               /* not a number */
    i = 0;
    if (isdigit(c) || c == '-') /* collect integer part */
        while (isdigit(s[++i] = c = getch()));
    if (c == '.')               /* collect fraction part */
        while (isdigit(s[++i] = c = getch()));
    s[i] = '\0';
    if (c != EOF)
        ungetch(c);
    return NUMBER;
}

#define BUFSIZE 200
char buf[BUFSIZE];              /* buffer for ungetch */
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
        printf("%c", i);
    }
}

void fake_buffer(char s[])
{
    /* push back the fake input */
    ungetch('\0');
    ungetch('\n');
    ungets(s);

    printf("%s;", s);
}

void testit(char s[])
{
    fake_buffer(s);
    calculator();
}

int main()
{
    printf("%s;\t\t%s\n", "in", "out");

    testit("1 1 +");
    testit("2 2 *");
    testit("2 2 2 * *");
    testit("2 2 2 2 * * *");
    testit("2 2 2 2 2 * * * *");
    testit("8 5 -");
    testit("10.8 0.5 -");
    testit("100 10 /");
    testit("100 11 /");
    testit("-5 4 +");
    testit("10 5 %");
    testit("11 5 %");
    testit("27 5 %");
    testit("11.11 3.14159 %");
    testit("9 = = =");
    testit("9 d +");            /* test duplicate */
    testit("100 10 /");         /* test swap */
    testit("100 10 s /");       /* test swap */
    testit("1 2 3 4 \n \n \n"); /* test clear stack */
    testit("1 2 3 4 c \n \n \n");       /* test clear stack */
    testit("1 e");              /* exp */
    testit("1 n");              /* sin */
    testit("3.14 n");           /* sin */
    testit("0 n");              /* sin */
    testit("0.5 n");            /* sin */
    testit("2 0.5 p");          /* pow */
    testit("2 1.0 p");          /* pow */
    testit("2 2.0 p");          /* pow */
    testit("2 8.0 p");          /* pow */
    /* @ is the 'recent' or last printed variable, >is store, @is read */
    testit("2 2 2 2 2 * >s * * @s @s +");
    testit("1 2 3 4 \n \n \n @@ @@ *");
    testit("2 \n @@ @@ * \n @@ @@ * \n @@ @@ * \n @@ @@ * \n @@ @@ * ");
    testit("1 1 +");
    testit("1 1 +");
    testit("1 1 +");
    /* calculator(); */
}
