#include <stdio.h>
#include <string.h>
#include <ctype.h>
/*
 * Exercise 5-7. Rewrite readlines to store lines in an array supplied by main,
 * rather than calling alloc to maintain storage. How much faster is the
 * program

$ time <words_alpha.shuffled.txt ./out >fil3
Original
real    0m0.520s

After
 */

#define MAXLINES 500000         /* max #lines to be sorted  */

#define ALLOCSIZE 10000000      /* size of available space  */
static char allocbuf[ALLOCSIZE];        /* storage for alloc */
static char *allocp = allocbuf; /* next free position */

char *alloc(int n)
{                               /* return pointer to n characters */
    if (allocbuf + ALLOCSIZE - allocp >= n) {   /* it fits */
        allocp += n;
        return allocp - n;      /* old p */
    } else                      /* not enough room */
        return 0;
}

void afree(char *p)
{                               /* free storage pointed to by p */
    if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
        allocp = p;
}

/* getline:  read a line into s, return length */
int _getline(char s[], int lim)
{
    int c, i;
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

/* writelines:  write output lines  */
void writelines(char *lineptr[], int nlines)
{
    int i;
    for (i = 0; i < nlines; i++)
        printf("&%s\n", lineptr[i]);
}


/* ========================= */

#define MAXLEN 100
char *lineptr[MAXLINES];        /* pointers to text lines  */

int readlines(char *lineptr[], int nlines, char *linestore);
void writelines(char *lineptr[], int nlines);
void _qsort(char *lineptr[], int left, int right);

/* sort input lines  */
int main()
{
    int nlines;                 /* number of input lines read  */
    char *linestore = malloc(MAXLINES * MAXLEN);        /* storage for lines */

    if ((nlines = readlines(lineptr, MAXLINES, linestore)) >= 0) {
        _qsort(lineptr, 0, nlines - 1);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("error: input too big to sort\n");
        return 1;
    }
}

/* max length of any input line */
int _getline(char s[], int);
char *alloc(int);

/* readlines:  read input lines */
int readlines(char *lineptr[], int maxlines, char *linestore)
{
    int len, nlines;

    nlines = 0;
    while ((len = _getline(linestore, MAXLEN)) > 0)
        if (nlines >= maxlines)
            return -1;
        else {
            linestore[len - 1] = '\0';  /* delete newline  */
            linestore += len;   /* move to next availble slot */
            lineptr[nlines++] = linestore;;
        }
    return nlines;
}

/* qsort:  sort v[left]...v[right] into increasing order */
void _qsort(char *v[], int left, int right)
{
    int i, last;
    void swap(char *v[], int i, int j);
    if (left >= right)          /* do nothing if array contains */
        return;                 /* fewer than two elements */
    swap(v, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; i++)
        if (strcmp(v[i], v[left]) < 0)
            swap(v, ++last, i);
    swap(v, left, last);
    _qsort(v, left, last - 1);
    _qsort(v, last + 1, right);
}

/* swap:  interchange v[i] and v[j] */
void swap(char *v[], int i, int j)
{
    char *temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}
