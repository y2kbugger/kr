#include <stdio.h>
/*
 * Exercise 4-14. Define a macro swap(t,x,y) that interchanges two arguments of
 * type t. (Block structure will help.)
 */

#define swap(t,x,y) { t z; z = x; x = y; y = z; }

int main()
{
    int a = 2;
    int b = 7;
    printf("a:%d, b:%d\n", a, b);
    swap(int, a, b);
    printf("a:%d, b:%d\n", a, b);
    swap(int, a, b);
    printf("a:%d, b:%d\n", a, b);
    /* printf("z:%d", z); */// I was double checking that the curlys kept the z out of scope

}
