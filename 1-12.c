#include <stdio.h>

#define IN 1
#define OUT 0


/* make a histogram of word lengths */
/* words up to length 255 */
/* zero length is whitespace */
/* test using man rsync | ./out */

int main()
{
    int c, state, len;
    int lenmax;
    int nmax;
    int nlen[255];
    int i, j;

    i = j = c = 0;
    state = OUT;
    lenmax = len = nmax = 0;

    for (i = 0; i<= 255; i++)
        nlen[i] = 0;

    while (c != EOF) {
        c = getchar(); 
        if (c == ' ' || c == '\n' || c == '\t' || c == EOF) {
            ++nlen[len];   /* count the word length */
            ++nlen[0];     /* count the whitespace */
            state = OUT;
            len = 0;
        }
        else if (state == OUT) {
            state = IN;
            ++len;
        }
        else {
            ++len;
        }

    }
    
    --nlen[0]; /* EOF isn't actually whitespace */

    /* find the max word length */
    for (i = 1; i<= 255; i++) {
        if (nlen[i] != 0)
            lenmax = i;
        if (nlen[i] > nmax)
            nmax = nlen[i];
    }
    
    /* print the histogram */
    /* normalize the max bar length to 72 */
    for (i = 1; i<=lenmax; i++) {
        printf("\n");
        for(j=0; j<(72*nlen[i]/nmax); j++)
            putchar('#');
    }
    printf("\n");
    printf("whitespace: %d\n", nlen[0]);
    printf("nmax: %d\n", nmax);
    printf("lenmax: %d\n", lenmax);

    return 0;

}
