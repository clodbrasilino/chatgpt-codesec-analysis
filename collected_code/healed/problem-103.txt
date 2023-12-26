#include<stdio.h>

int factorial(int n)
{
    int fact = 1;
    
    for (int i = 1; i <= n; i++)
    {
        fact *= i;
    }
    
    return fact;
}

int eulerianNumber(int n, int m)
{
    int num1, num2, num3;
    
    if (m >= n || n == 0)
        return 0;
    
    num1 = (n - m - 1) * (factorial(n - 1) / factorial(n - m));
    
    if (m % 2 == 0)
    {
        num2 = m * num1;
        num3 = factorial(m + 1) / factorial(m / 2);
    } 
    else
    {
        num2 = -m * num1;
        num3 = -factorial(m + 1) / factorial(m / 2);
    }
    
    return num2 * num3;
}

int main()
{
    int n = 0, m = 0;
    
    printf("Enter the values for n and m: ");
    scanf("%d %d", &n, &m);
    
    printf("Eulerian number a(%d, %d) is: %d\n", n, m, eulerianNumber(n, m));
    
    return 0;
}