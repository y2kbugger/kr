#include <stdio.h> 

int main()
{
    float c;
    printf("F\tC\n");
    for(float i=40.0; i<=300; i=i+10)
    {
        c = (5.0/9.0)*(i-32.0);
        printf("%4.0f%7.1f\n",i,c); 
    }

}


