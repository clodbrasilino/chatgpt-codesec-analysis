#include <stdio.h>

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int main(void)
{
    int num1 = 10;
    int num2 = 20;
    
    printf("Maximum of %d and %d is %d\n", num1, num2, max(num1, num2));
    
    return 0;
}