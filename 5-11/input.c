#include <stdio.h>
#include <string.h>

/* Exercise 1-21. Write a program entab that replaces strings of blanks by the minimum number of tabs and blanks to achieve the same spacing. Use the same tab stops as for detab. When either a tab or a single blank would suffice to reach a tab stop, which should be given preference? */

#define MAXLINE 222
char TAB = '#';
/* char TAB = '\t'; */
int TABSTOP = 8;
int TABSTOPS[] = { 2, 4, 7, -1 };

int detab(char line[]);
int entab(char line[]);

int main(int argc, char **argv);

int detab(char line[])
{
    int c;
    int i, j;
    j = 0;
    char linecopy[MAXLINE];
    strcpy(linecopy, line);
    for (i = 0;
         i + j <= MAXLINE && ((c = linecopy[i]) != EOF) && (c != '\n');
         i++) {
        if (c == '\t') {
            c = ' ';
            while ((i + j + 1) % TABSTOP != 0) {
                line[i + j] = c;
                j++;
            }
        }
        line[i + j] = c;
    }
    if (c == '\n') {
        line[i + j] = c;
        ++i;
    }
    line[i + j] = '\0';
    return i + j;
}

int istabstop(int column)
{
    /* return !(i % TABSTOP); */
    for (int i = 0, ts = 0; ts != -1; ts = TABSTOPS[i++]) {
        if (column == ts) {
            return 1;
        }
    }
    return 0;
}

int entab(char line[])
{
    detab(line);

    int c;
    int orig, entabbed;
    orig = entabbed = 0;

    do {
        c = line[orig++];
        line[entabbed++] = c;
        if (c == ' ' && istabstop(orig)) {
            printf("found usable tabstop: %d\n", orig);
            /* backtrack the spaces and replace with TAB */
            while (entabbed > 0 && ' ' == line[entabbed - 1]) {
                entabbed--;
                printf("entabbed: %d\n", entabbed);
                ;
            }
            printf("putting tab at: %d\n", entabbed + 1);
            line[entabbed++] = TAB;
        }
    } while (c != '\0');

    return entabbed;
}

int main(int argc, char **argv)
{
    char s[MAXLINE];
    /* int len; */
    int (*action_fxn)(char line[]);
    if (argc == 1) {
        printf("First argument should be either entab or detab\n");
        return 1;
    }
    argv++, argc--;
    if (**argv == 'e') {
        printf("running as entab\n");
        action_fxn = &entab;
    } else if (**argv == 'd') {
        printf("running as detab\n");
        action_fxn = &detab;
    } else {
        printf("First argument should be either entab or detab\n");
        return 2;
    }

    /* Loop until no more bytes are read */
    while (fgets(s, MAXLINE, stdin)) {
        printf("?%s", s);
        action_fxn(s);
        printf("!%s", s);
    }
    return 0;
}
