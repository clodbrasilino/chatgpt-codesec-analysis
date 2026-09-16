#include <stdio.h>

int median_of_three(int a, int b, int c)
{
    if ((a >= b && a <= c) || (a <= b && a >= c))
    {
        return a;
    }
    else if ((b >= a && b <= c) || (b <= a && b >= c))
    {
        return b;
    }
    else
    {
        return c;
    }
}

int main(void)
{
    int num1, num2, num3;
    int result;
    
    if (scanf("%d %d %d", &num1, &num2, &num3) != 3)
    {
        return 1;
    }
    
    result = median_of_three(num1, num2, num3);
    printf("%d\n", result);
    
    return 0;
}