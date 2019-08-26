#include <stdio.h> 

int main()
{
    float f;
    printf("C\tF\n");
    for(float i=300.0; i>=-50; i=i-10)
    {
        f = i*9/5+32;
        printf("%4.0f%7.1f\n",i,f); 
    }

}


