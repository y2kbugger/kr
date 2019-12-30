/* Exercise 7-2. Write a program that will print arbitrary input in a sensible
 * way. As a minimum, it should print non-graphic characters in octal or
 * hexadecimal according to local custom, and break long text lines. */

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#define MAXCOLS 80

int main()
{
    int c;
    int column = 0;
    char buffer[5];
    FILE *outfile = (FILE *) stdout;
    while ((c = getc(stdin)) != EOF) {
        if (c == '\n') {
            column = 0;
            putc(c, outfile);
            continue;
        }

        if (c == '\\') {
            column += 2;
            sprintf(buffer, "\\%c", c);
        } else if (isgraph(c)) {
            column += 1;
            sprintf(buffer, "%c", c);
        } else {
            column += 4;
            sprintf(buffer, "\\x%.2X", c);
        }
        if (column > MAXCOLS) {
            column -= MAXCOLS;
            putc('\n', outfile);
        }
        fprintf(outfile, "%s", buffer);
    }
    putc('\n', outfile);
    exit(0);
}
