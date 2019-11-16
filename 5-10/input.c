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
 * Exercise 5-10. Write the program expr, which evaluates a reverse Polish expression from the command line, where each operator or operand is a separate argument. For example,
 *
 *      expr 2 3 4 + *
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

int getop(int argc, char *arg, char s[]);
void push(double);
double pop(void);
int sp;                         /* next free stack position */
double val[];                   /* value stack */
double var[256];                /* var array */

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


/* getop: get next operator or numeric operand */
int getop(int argc, char *arg, char s[])
{
    int i = 0;
    char c;

    if (arg == NULL) {
        return s[0] = s[1] = '\0';
    }

    c = *arg;

    /* variables */
    if (c == '@' || c == '>') {
        s[0] = s[1] = '\0';
        if (*(arg + 1) != '\0')
            printf("Ignoring remaining part of variable: %s\n", arg + 1);
        return c;
    }

    s[1] = '\0';
    if (!isdigit(c) && c != '.' && c != '-') {
        if (*(arg + 1) != '\0')
            printf("Ignoring remaining part of operator: %s\n", arg + 1);
        return c;               /* not a number */
        i = 0;
    }
    if (isdigit(c) || c == '-') /* collect integer part */
        while (isdigit(s[i++] = c = *(arg++)));
    if (c == '.')               /* collect fraction part */
        while (isdigit(s[i++] = c = *(arg++)));
    s[i] = '\0';
    if (*(--arg) != '\0')
        printf("Ignoring remaining part of number: %s\n", arg);
    printf("I think i found a number: %s\n", s);
    return NUMBER;
}

#define BUFSIZE 200
int buf[BUFSIZE];               /* buffer for ungetch */
int bufp = 0;                   /* next free position in buf */

int main(int argc, char **argv)
{
    int type;
    double op1;
    double op2;
    char s[MAXOP];

    while ((type = getop(--argc, *++argv, s)) != '\0') {
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
