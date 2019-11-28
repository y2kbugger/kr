#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* Exercise 5-11: Modify the programs entab and detab (written as exercises in Chapter 1) to accept a list of tab stops as arguments. Use the default tab settings if there are no arguments. */

#define MAXLINE 222
char TAB = '#';
/* char TAB = '\t'; */
int TABSTOP = 8;
int TABSTOPS[256] = { -1 };

void detab(char line[]);
void entab(char line[]);
int istabstop(int column);

int main(int argc, char **argv);

void detab(char line[])
{
    int c;
    int i, j;
    j = 0;
    char linecopy[MAXLINE];
    strcpy(linecopy, line);
    for (i = 0;
         i + j <= MAXLINE && ((c = linecopy[i]) != EOF) && (c != '\n');
         i++) {
        if (c == TAB) {
            c = ' ';
            while (!istabstop(i + j + 1 + 1)) { // one for column versus index, one for lookahead.
                line[i + j++] = c;
            }
        }
        line[i + j] = c;
    }
    if (c == '\n') {
        line[i++ + j] = c;
    }
    line[i + j] = '\0';
}

//Check based on column number, not line char index
int istabstop(int column)
{
    if (column == 0) {
        printf("Warning Checking non-existant column (0)");
        return -1;
    }
    if (column == 1) {
        /* No such thing as 1 being a useful tabstop */
        return 0;
    }

    int max_ts = 1;
    /* see if it matches a manually set tabstop */
    for (int i = 0, ts = 0; ts != -1; ts = TABSTOPS[i++]) {
        /* find the furthest right tabstop */
        if (ts > max_ts) {
            max_ts = ts;
        }
        if (column == ts) {
            return 1;
        }
    }
    if (column < max_ts)
        return 0;

    /* See if it matches an automatic tabstop,
     * Set equal spacing past furthest tabstop */
    return !((((column) - max_ts)) % TABSTOP);

}

void entab(char line[])
{
    detab(line);

    int c;
    int orig, entabbed;
    orig = entabbed = 0;

    do {
        c = line[orig++];
        line[entabbed++] = c;
        if (c == ' ' && istabstop(orig + 1)) {
            /* backtrack the spaces and replace with TAB */
            while (entabbed > 0 && ' ' == line[entabbed - 1]) {
                entabbed--;
            }
            line[entabbed++] = TAB;
        }
    } while (c != '\0');
}

#define LOUD(x) "\033[0;31m" x "\033[0m"
void compare_istabstop(int column)
{

    int via_defaults;
    int via_explicit;
    int via_semiexplicit;
    TABSTOP = 8;

    TABSTOPS[0] = -1;
    via_defaults = istabstop(column);

    TABSTOPS[0] = 9;
    TABSTOPS[1] = 17;
    TABSTOPS[2] = 25;
    TABSTOPS[3] = 33;
    TABSTOPS[4] = 41;
    TABSTOPS[5] = 49;
    TABSTOPS[6] = -1;
    via_explicit = istabstop(column);


    TABSTOPS[0] = 9;
    TABSTOPS[1] = -1;
    via_semiexplicit = istabstop(column);

    printf("%4d", column);
    printf("%8d", via_defaults);
    if ((via_defaults != via_explicit) && isatty(1))
        printf(LOUD("%13d"), via_explicit);
    else
        printf("%13d", via_explicit);
    if (via_defaults != via_semiexplicit && isatty(1))
        printf(LOUD("%12d"), via_semiexplicit);
    else
        printf("%12d", via_semiexplicit);
    printf("\n");
}

void tests(char line[])
{
    printf("Test suite ignores all stdin and command line tabstops\n");
    printf("Testing that istabstop matches defaults vs explicit\n");
    printf("Column    Defaults    Explicit    SemiExplicit\n");
    for (int i = 1; i < 45; i++)
        compare_istabstop(i);
}

int main(int argc, char **argv)
{
    char s[MAXLINE];
    /* int len; */
    void (*action_fxn)(char line[]);
    if (argc == 1) {
        printf("First argument should be either entab or detab\n");
        return 1;
    }
    argv++, argc--;
    if (**argv == 'e') {
        /* printf("running as entab\n"); */
        action_fxn = &entab;
    } else if (**argv == 'd') {
        /* printf("running as detab\n"); */
        action_fxn = &detab;
    } else if (**argv == 't') {
        /* printf("running tests\n"); */
        action_fxn = &tests;
    } else {
        printf
            ("First argument should be either entab or detab or tests\n");
        return 2;
    }

    // Read in tabstops from cli
    int tbs = 0;
    while (argc > 1) {
        argv++, argc--;
        TABSTOPS[tbs++] = atoi(*argv);
    }
    TABSTOPS[tbs] = -1;

    /* Loop until no more bytes are read */
    while (fgets(s, MAXLINE, stdin)) {
        printf("?%s", s);
        action_fxn(s);
        printf("!%s", s);
    }
    return 0;
}
