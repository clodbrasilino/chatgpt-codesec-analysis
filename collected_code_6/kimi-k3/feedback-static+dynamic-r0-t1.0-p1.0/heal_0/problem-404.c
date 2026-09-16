#include <stdio.h>

int find_minimum(int a, int b);

int find_minimum(int a, int b)
{
    return (a < b) ? a : b;
}

int main(void)
{
    int num1 = 10;
    int num2 = 20;
    int result = find_minimum(num1, num2);
    
    printf("Minimum of %d and %d is: %d\n", num1, num2, result);
    
    return 0;
}