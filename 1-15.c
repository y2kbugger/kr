#include <stdio.h> 

float c_to_f(float temp_c);

int main()
{
    printf("C\tF\n");
    for(float c = 300.0; c >= -50; c = c - 10)
    {
        printf("%4.0f%7.1f\n", c, c_to_f(c)); 
    }

}

float c_to_f(float temp_c){
    return temp_c * 9 / 5 + 32;
}