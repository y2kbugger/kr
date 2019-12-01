/* Exercise 5-13. Write the program tail, which prints the last n lines of its
 * input. By default, n is 10, let us say, but it can be changed by an optional
 * argument, so that  tail -n  prints the last n lines. The program should
 * behave rationally no matter how unreasonable the input or the value of n.
 * Write the program so it makes the best use of available storage; lines
 * should be stored as in the sorting program of Section 5.6, not in a
 * two-dimensional array of fixed size. */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int n = 10;

char **lines;
char **lines_start;
char **lines_end;

void putline(char *line)
{
    if (++lines >= lines_end)
        lines -= n;
    if (*lines != NULL)
        free(*lines);           // recycle line that is about to be overwritten
    *lines = line;
}

char *mygetline()
{
    char *line = NULL;
    int nchars;
    size_t len = 0;
    nchars = getline(&line, &len, stdin);
    if (nchars == -1)
        return NULL;
    *(line + nchars) = '\0';
    return line;
}

void printlines()
{
    /* No lines */
    if ((lines == lines_start) && (*lines == NULL))
        return;
    ++lines;
    /* Skip unused line slots, traversing ring buffer. */
    while (*lines == NULL)
        if (++lines >= lines_end)
            lines -= n;

    /* Print ring buffer of input lines */
    while (*lines != NULL) {
        printf("%s", *lines);
        free(*lines);
        *lines = NULL;
        lines++;
        if (lines >= lines_end)
            lines -= n;
    }
}

int main(int argc, char **argv)
{
    /* initialize ring buffer for line pointers */
    lines = malloc(n * sizeof(char *));
    lines_start = lines;
    lines_end = lines_start + n;
    while (lines < lines_end) {
        *(lines++) = NULL;
    }
    lines = lines_start;

    char *line;
    while ((line = mygetline()) != NULL) {
        putline(line);
    }
    printlines();
    return 0;
}
