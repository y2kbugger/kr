/* Exercise 7-4. Write a private version of scanf analogous to minprintf from
 * the previous section. */

#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

void minscanf(char *fmt, ...);

int main()
{
    char c = 'z';
    minscanf("test:%c", &c);
    /* scanf("test:%c", &c); */
    printf("the letter scanned was: `%c`!!!\n", c);
    exit(0);
}

void minscanf(char *fmt, ...)
{
    va_list ap;                 /* points to each unnamed arg in turn */
    char *p;
    /* char *sval; */
    int *cptrval;
    /* int ival; */
    /* double dval; */

    va_start(ap, fmt);          /* make ap point to 1st unnamed arg */
    for (p = fmt; *p; p++) {
        if (*p != '%') {
            if (*p == getchar()) {
                continue;
            } else {
                printf("failed to match pattern");
                break;
            }
        }
        switch (*++p) {
            case
        'c':
            cptrval = va_arg(ap, int *);
            *cptrval = getchar();
            break;
            /* case */
            /* 'd': */
            /*     ival = va_arg(ap, int); */
            /*     printf("%d", ival); */
            /*     break; */
            /*     case */
            /* 'f': */
            /*     dval = va_arg(ap, double); */
            /*     printf("%f", dval); */
            /*     break; */
            /*     case */
            /* 's': */
            /*     for (sval = va_arg(ap, char *); *sval; sval++) */
            /*         putchar(*sval); */
            /*     break; */
        default:
            putchar(*p);
            break;
        }
    }
    va_end(ap);                 /* clean up when done */
}
