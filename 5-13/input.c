/* Exercise 5-13. Write the program tail, which prints the last n lines of its
 * input. By default, n is 10, let us say, but it can be changed by an optional
 * argument, so that  tail -n  prints the last n lines. The program should
 * behave rationally no matter how unreasonable the input or the value of n.
 * Write the program so it makes the best use of available storage; lines
 * should be stored as in the sorting program of Section 5.6, not in a
 * two-dimensional array of fixed size. */

#include <stdio.h>
#include <stdlib.h>

int n = 10;

char **lines;
char **lines_start;
char **lines_end;

int BUFFERSIZE = 512;
char *BUFFER_write;
char *BUFFER_read;
char *BUFFER_start;
char *BUFFER_end;


void putline(char *line)
{
    /* if (line != 500) */
    *(lines++) = line;
    if (lines >= lines_end)
        lines -= n;
}

void putchar_buffer(char c)
{
    *(BUFFER_write++) = c;
    if (BUFFER_write >= BUFFER_end)
        BUFFER_write -= BUFFERSIZE;
}

void printline(char *line)
{
    while (*line != '\0') {
        putchar(*line);
        line++;
        if (line >= BUFFER_end)
            line -= BUFFERSIZE;
    }
    putchar('\n');
}

char *mygetline()
{
    int c;
    char *line = BUFFER_write;
    while ((c = getchar()) != '\n') {
        if (c == EOF) {
            putchar_buffer('\0');
            return NULL;
        }
        putchar_buffer(c);
    }
    putchar_buffer('\0');
    return line;
}

void printlines()
{
    /* No lines */
    if ((lines == lines_start) && (*lines == NULL))
        return;

    /* Skip unused line slots, traversing ring buffer. */
    while (*lines == NULL)
        if (++lines >= lines_end)
            lines -= n;

    /* Print ring buffer of input lines */
    while (*lines != NULL) {
        printline(*lines);
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

    BUFFER_write = malloc(BUFFERSIZE * sizeof(char));
    BUFFER_read = BUFFER_write;
    BUFFER_start = BUFFER_write;
    BUFFER_end = BUFFER_write + BUFFERSIZE;

    char *line;
    while ((line = mygetline()) != NULL) {
        putline(line);
    }
    printlines();
    return 0;
}
