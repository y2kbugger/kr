#include <stdio.h>
#include <string.h>
#include <ctype.h>
/*
 * Exercise 5-7. Rewrite readlines to store lines in an array supplied by main,
 * rather than calling alloc to maintain storage. How much faster is the
 * program

$ time (for i in {1..10}; do <words_alpha.shuffled.txt ./out > /dev/null ; done) 

Original
real    0m4.602s
user    0m4.514s
sys     0m0.097s


After
real    0m5.019s
user    0m4.962s
sys     0m0.066s

 */

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
#define MAXLINES 500000         /* max #lines to be sorted  */
#define AVERAGELEN 10
char *lineptr[MAXLINES];        /* pointers to text lines  */

int readlines(char *lineptr[], int nlines, char *linestore);
void writelines(char *lineptr[], int nlines);
void _qsort(char *lineptr[], int left, int right);

/* sort input lines  */
int main()
{
    int nlines;                 /* number of input lines read  */
    char *linestore = malloc(MAXLINES * AVERAGELEN);    /* storage for lines */

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
