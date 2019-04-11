#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define TESTREPS 750000
/* #define SHOWFINDS */

/*
 * Exercise 3-1. Our binary search makes two tests inside the loop, when one would suffice (at the price of more tests outside). Write a version with only one test inside the loop and measure the difference in run-time.
 */

/* binsearch: find x in v[0] <= v[1] <= ... <= v[n−1] */

int binsearch(int x, int v[], int n)
{
    int low, high, mid;
    low = 0;
    high = n - 1;
    while (low <= high) {
        mid = (low + high) / 2;
        if (x < v[mid])
            high = mid - 1;
        else if (x > v[mid])
            low = mid + 1;
        else                    /* found match */
            return mid;
    }
    return -1;
    /* no match */
}

int binsearch2(int x, int v[], int n)
{
    int low, high, mid;
    low = 0;
    high = n - 1;
    while (low <= high) {
        mid = (low + high) / 2;
        if (x < v[mid])
            high = mid - 1;
        else
            low = mid + 1;
    }
    if (x == v[mid])
/* found match */
        return mid;
    else
        /* no match */
        return -1;
}


const char *bit_rep[16] = {
    [0] = "0000",[1] = "0001",[2] = "0010",[3] = "0011",
    [4] = "0100",[5] = "0101",[6] = "0110",[7] = "0111",
    [8] = "1000",[9] = "1001",[10] = "1010",[11] = "1011",
    [12] = "1100",[13] = "1101",[14] = "1110",[15] = "1111",
};

void print_binary(uint16_t byte)
{
    printf("%s%s%s%s",
           bit_rep[(byte & 0xF000) >> 12],
           bit_rep[(byte & 0x0F00) >> 8],
           bit_rep[(byte & 0x00F0) >> 4], bit_rep[(byte & 0x000F) >> 0]
        );
}

/* void testit(uint16_t x) */
void testit(int n)
{
    int *v = malloc(sizeof(int) * n);
    int j = 0;
    int x;

    /* j=0; */
    /* initialize monotonic array
     * skipping some ints */
    for (int i = 0; i < n; ++i) {
        /* skip a rand 75% of ints */
        while (rand() % 4 != 0)
            j++;
        v[i] = j;
    }

    printf("%-10d | ", n);
    clock_t start, diff;
    start = clock();
    for (int k = 0; k < TESTREPS; k++) {
        /* find a random int in the correct range */
        x = rand() % n;
#ifdef SHOWFINDS
        putchar(binsearch(x, v, n) >= 0 ? '$' : 'x');
#else
        binsearch(x, v, n);
#endif

    }
    int msec;
    diff = clock() - start;
    msec = diff * 1000 / CLOCKS_PER_SEC;
    printf(" %4d msec", msec);

    /* optimized version */
    start = clock();
    for (int k = 0; k < TESTREPS; k++) {
        /* find a random int in the correct range */
        x = rand() % n;
#ifdef SHOWFINDS
        putchar(binsearch2(x, v, n) >= 0 ? '$' : 'x');
#else
        binsearch2(x, v, n);
#endif

    }
    diff = clock() - start;
    msec = diff * 1000 / CLOCKS_PER_SEC;
    printf(" %4d msec", msec);
    printf("\n");
}

int main()
{
    testit(10);
    testit(100);
    testit(10000);
    testit(100000);
    testit(1000000);
    testit(1000000);
    testit(10000000);
    testit(100000000);
}
