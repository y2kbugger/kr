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

/* zero is no fields, otherwise it is the field number starting with 1, space
 * separated. */
int field = 0;
void extractfield(char *);

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
        /* myqsort((void **) lineptr, 0, nlines - 1, cmp); */
        mergeSort((void **) lineptr, 0, nlines - 1, cmp);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("input too big to sort\n");
        return 1;
    }
}

// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void merge(void *v[], int l, int m, int r, Comp comp)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    /* create temp arrays */
    void *L[n1], *R[n2];

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = v[l + i];
    for (j = 0; j < n2; j++)
        R[j] = v[m + 1 + j];

    /* Merge the temp arrays back into v[l..r] */
    i = 0;                      // Initial index of first subarray
    j = 0;                      // Initial index of second subarray
    k = l;                      // Initial index of merged subarray
    while (i < n1 && j < n2) {
        if (comp(L[i], R[j]) = <0) {    // need boolean compare, quicksort used lessthan, equal, or greaterthan
            v[k] = L[i];
            i++;
        } else {
            v[k] = R[j];
            j++;
        }
        k++;
    }

    /* Copy the remaining elements of L[], if there
       are any */
    while (i < n1) {
        v[k] = L[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2) {
        v[k] = R[j];
        j++;
        k++;
    }
}

/* l is for left index and r is right index of the
   sub-array of v to be sorted */
void mergeSort(void *v[], int l, int r, Comp comp)
{
    if (l < r) {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l + (r - l) / 2;

        // Sort first and second halves
        mergeSort(v, l, m, comp);
        mergeSort(v, m + 1, r, comp);

        merge(v, l, m, r, comp);
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
    extractfield(news);
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
    if (!foldem)
        return;

    while (*s != '\0') {
        *s = tolower(*s);
        s++;
    }
}


void reverse(int *result)
{
    if (reversed)
        *result *= -1;
}

void directoryorderer(char *s)
{
    if (!directoryorder)
        return;

    char *sprime = s;
    while (*s != '\0') {
        if (isalnum(*s) || (*s == ' '))
            *sprime++ = *s++;
        else
            *s++;
    }
}

char SEP = ' ';
void extractfield(char *s)
{
    if (!field)
        return;

    char *s_orig = s;           // debugging only
    char *sprime = s;
    int currentfield = 1;
    while (currentfield < field) {
        s++;
        if (*s == SEP)
            currentfield++, s++;
        if (*s == '\0')
            goto FIELDERROR;
    }
    while (currentfield == field) {
        *sprime++ = *s++;
        if (*s == SEP || *s == '\0')
            currentfield++, s++;
    }
    *sprime++ = '\0';
    return;

  FIELDERROR:
    printf("Not enough fields in input.\n");
    exit(1);
}
