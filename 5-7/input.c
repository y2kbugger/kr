#include <stdio.h>
#include <string.h>
#include <ctype.h>
/*
 * Exercise 5-5. Rewrite readlines to store lines in an array supplied by main,
 * rather than calling alloc to maintain storage. How much faster is the
 * program?
 */

/* max #lines to be sorted */
#define MAXLINES 5000

char  *lineptr[MAXLINES];

/* pointers to text lines  */
int  readlines(char  *lineptr[],  int  nlines);
void  writelines(char  *lineptr[],  int  nlines);
void  qsort(char  *lineptr[],  int  left,  int  right);   /* sort input lines  */

voic main()
{
    /* number of input lines read  */
    int  nlines;
        if ((nlines =  readlines(lineptr,  MAXLINES)) >=  0)
          {
                qsort(lineptr,  0,  nlines - 1);
                writelines(lineptr,  nlines);
                return  0;
        } else {
        printf("error: input too big to sort\n");
        return  1;
    }
}

#define MAXLEN 1000
/* max length of any input line */
int  getline(char  *,   int);
char  *alloc(int);
/* readlines:  read input lines */
int  readlines(char  *lineptr[],  int  maxlines)
{
    int  len,  nlines;
        char  *p,  line[MAXLEN];
        nlines ? ? =  0;
        while  ((len ? ? =  getline(line,  MAXLEN)) ? ? > 0)
                if  (nlines ? ? >= maxlines ?
                              ? ¦¦ (p ? ? =  alloc(len)) ? ? ==  NULL)
                        return  −1;
        else
              {
                        line[len ? ? ? 1] ? ? =  ′\0 ? ? ?;
              /* delete newline  */             strcpy(p,
                                                                        line);
                        lineptr[nlines++] ? ? =  p;
                    }
        return  nlines;
}                               /* writelines:  write output lines  */

void  writelines(char  *lineptr[],  int  nlines)
{
        int  i;
        for  (i ? ? =  0;  i ? ? < nlines;  i++)
                printf("%s\n",  lineptr[i]);
}

void testit(char *s, char *t, int n)
{
    printf("%s;%s;%d:\n", s, t, n);
    char si[200];
    char ti[200];

    /* strncpy */
    /* Make a backup to prevent functions from affection one another */
    strcpy(si, s);
    strcpy(ti, t);
    _strncpy(si, ti, n);
    printf("\tcpy:\t%s;%s\n", si, ti);

    /* strncat */
    strcpy(si, s);
    strcpy(ti, t);
    _strncat(si, ti, n);
    printf("\tcat:\t%s;%s\n", si, ti);

    /* strncmp */
    strcpy(si, s);
    strcpy(ti, t);
    int cmp_result = _strncmp(si, ti, n);
    printf("\tcmp:\t%d\n", cmp_result);
}


int main()
{
    testit("", "", 0);
}
