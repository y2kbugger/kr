#include <stdio.h>
#include <limits.h>

/*
 * Exercise 2-1. Write a program to determine the ranges of char, short, int, and
 * long variables, both signed and unsigned, by printing appropriate values from
 * standard headers and by direct computation. Harder if you compute them:
 * determine the ranges of the various floating-point types.
 */
/*
SCHAR_MAX
SHRT_MAX 
INT_MAX  
LONG_MAX 

SCHAR_MIN
SHRT_MIN
INT_MIN
LONG_MIN

UCHAR_MAX
USHRT_MAX
UINT_MAX
ULONG_MAX
*/

int main(){

    unsigned char my_uchar;
    my_uchar = 0;
    printf("uchar\n");
    printf("%d:%d\n", 0, UCHAR_MAX);
    while(my_uchar < ++my_uchar){}
    printf("%u:%u (calculated)\n\n", my_uchar, --my_uchar);
    signed char my_schar;
    my_schar = 0;
    printf("schar\n");
    printf("%d:%d\n", SCHAR_MIN, SCHAR_MAX);
    while(my_schar < ++my_schar){}
    printf("%d:%d (calculated)\n\n", my_schar, --my_schar);

    unsigned short my_ushrt;
    my_ushrt = 0;
    printf("ushrt\n");
    printf("%u:%u\n", 0, USHRT_MAX);
    while(my_ushrt < ++my_ushrt){}
    printf("%u:%u (calculated)\n\n", my_ushrt, --my_ushrt);
    signed short my_sshrt;
    my_sshrt = 0;
    printf("sshrt\n");
    printf("%d:%d\n", SHRT_MIN, SHRT_MAX);
    while(my_sshrt < ++my_sshrt){}
    printf("%d:%d (calculated)\n\n", my_sshrt, --my_sshrt);

    /*
    unsigned int my_uint;
    my_uint = 0;
    printf("uint\n");
    printf("%u:%u\n", 0, UINT_MAX);
    while(my_uint < ++my_uint){}
    printf("%u:%u (calculated)\n\n", my_uint, --my_uint);
    signed int my_sint;
    my_sint = 0;
    printf("sint\n");
    printf("%d:%d\n", INT_MIN, INT_MAX);
    while(my_sint < ++my_sint){}
    printf("%d:%d (calculated)\n\n", my_sint, --my_sint);
    */


    unsigned long my_ulong;
    my_ulong = 0;
    printf("ulong\n");
    printf("%lu:%lu\n", 0, ULONG_MAX);
    //while(my_ulong < ++my_ulong){}
    //my_ulong = ((1 << (sizeof(my_ulong)*8 - 2) - 1) * 2) + 2;
    printf("%lu:%lu (calculated)\n\n", my_ulong, --my_ulong);
    signed long my_slong;
    my_slong = 0;
    printf("slong\n");
    printf("%ld:%ld\n", LONG_MIN, LONG_MAX);
    //while(my_slong < ++my_slong){}
    my_slong = ((1 << (sizeof(my_slong)*8 - 0) - 1) * 2) ;
    printf("%ld:%ld (calculated)\n\n", my_slong, --my_slong);

    float my_float;
    my_float = 0;
    printf("float\n");
    printf("%f:%f\n", FLT_MIN, FLT_MAX);
    //my_float = ((1 << (sizeof(my_ulong)*8 - 2) - 1) * 2) + 2;
    printf("%f:%f (calculated)\n\n", my_float, --my_float);


}


