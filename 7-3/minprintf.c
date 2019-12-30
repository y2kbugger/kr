/* Exercise 7-3. Revise minprintf to handle more of the other facilities of
 * printf. */

#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

void minprintf(char *fmt, ...);

int main()
{
    minprintf("phrase is `%s`\n", "Hello world");
    minprintf("phrase is `%c`\n", 'd');
    exit(0);
}

/* minprintf:  minimal printf with variable argument list */
void minprintf(char *fmt, ...)
{
    va_list ap;                 /* points to each unnamed arg in turn */
    char *p, *sval;
    int cval;
    int ival;
    double dval;

    va_start(ap, fmt);          /* make ap point to 1st unnamed arg */
    for (p = fmt; *p; p++) {
        if (*p != '%') {
            putchar(*p);
            continue;
        }
        switch (*++p) {
            case
        'c':
            cval = va_arg(ap, int);
            printf("%c", (char) cval);
            break;
            case
        'd':
            ival = va_arg(ap, int);
            printf("%d", ival);
            break;
            case
        'f':
            dval = va_arg(ap, double);
            printf("%f", dval);
            break;
            case
        's':
            for (sval = va_arg(ap, char *); *sval; sval++)
                putchar(*sval);
            break;
        default:
            putchar(*p);
            break;
        }
    }
    va_end(ap);                 /* clean up when done */
}
