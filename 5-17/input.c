/* Exercise 5-17. Add a field-handling capability, so sorting may be done on
 * fields within lines, each field sorted according to an independent set of
 * options. (The index for this book was sorted with -df for the index category
 * and -n for the page numbers.)
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXLINES 5000           /* max #lines to be sorted */
char *lineptr[MAXLINES];        /* pointers to text lines */

/* zero is no fields, otherwise it is the field number starting with 1, space
 * separated. */
int field = 0;

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

typedef int (*Comp)(void *, void *);
char *precmp(char *s);
int cmp(void *, void *);
void postcmp(int *);


void myqsort(void *lineptr[], int left, int right, Comp);

int foldem = 0;
void fold(char *);

int directoryorder = 0;
void directoryorderer(char *);

int numeric = 0;                /* 1 if numeric sort */
int numcmp(char *, char *);

int reversed = 0;
void reverse(int *);

void swap(void *v[], int i, int j)
{
    void *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;

}

int mygetline(char s[], int lim)
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
        printf("%s\n", lineptr[i]);
}

/* readlines:  read input lines */
int readlines(char *lineptr[], int maxlines)
{
    int len, nlines;
    char *p, line[MAXLINES];

    nlines = 0;
    while ((len = mygetline(line, MAXLINES)) > 0)
        if (nlines >= maxlines || (p = malloc(len)) == NULL)
            return -1;
        else {
            line[len - 1] = '\0';       /* delete newline */
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    return nlines;
}

/* sort input lines */
int main(int argc, char *argv[])
{
    int nlines;                 /* number of input lines read */

    while (argc-- > 1) {
        argv++;
        if (strcmp(*argv, "-n") == 0)
            numeric = 1;
        else if (strcmp(*argv, "-r") == 0)
            reversed = 1;
        else if (strcmp(*argv, "-f") == 0)
            foldem = 1;
        else if (strcmp(*argv, "-d") == 0)
            directoryorder = 1;
        else if (strcmp(*argv, "-c") == 0) {
            argv++;
            argc--;
            field = atoi(*argv);
        } else
            printf("unknown arg: '%s'", *argv);
    }
    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        myqsort((void **) lineptr, 0, nlines - 1, cmp);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("input too big to sort\n");
        return 1;
    }
}

/* myqsort:  sort v[left]...v[right] into increasing order */
void myqsort(void *v[], int left, int right, Comp comp)
{
    int i, last;
    void swap(void *v[], int, int);

    if (left >= right)          /* do nothing if array contains */
        return;                 /* fewer than two elements */
    swap(v, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; i++)
        if ((*comp) (v[i], v[left]) < 0)
            swap(v, ++last, i);
    swap(v, left, last);
    myqsort(v, left, last - 1, comp);
    myqsort(v, last + 1, right, comp);
}

/* return mutated strings before cmp*/
char *precmp(char *s)
{
    char *news = malloc((strlen(s) + 1) * sizeof(char));
    strcpy(news, s);
    fold(news);
    directoryorderer(news);
    return news;
}

int cmp(void *left, void *right)
{
    left = precmp(left);
    right = precmp(right);
    Comp sorter = (numeric ? (Comp) numcmp : (Comp) strcmp);
    int result = sorter(left, right);
    postcmp(&result);
    return result;
}

/* numcmp:  compare s1 and s2 numerically */
int numcmp(char *s1, char *s2)
{
    double v1, v2;

    v1 = atof(s1);
    v2 = atof(s2);
    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else
        return 0;
}

/* mutate compare result */
void postcmp(int *result)
{
    reverse(result);
}

void fold(char *s)
{
    if (foldem) {
        while (*s != '\0') {
            *s = tolower(*s);
            s++;
        }
    }
}


void reverse(int *result)
{
    if (reversed)
        *result *= -1;
}

void directoryorderer(char *s)
{

    char *sprime = s;

    if (directoryorder) {
        while (*s != '\0') {
            if (isalnum(*s) || (*s == ' '))
                *sprime++ = *s++;
            else
                *s++;
        }
    }
}
