#include<stdio.h>

// Function to calculate factorial
int factorial(int n)
{
    int fact = 1;
    
    for (int i = 1; i <= n; i++)
    {
        fact *= i;
    }
    
    return fact;
}

// Function to calculate eulerian number
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

// Main function
int main()
{
    int n, m;
    
    printf("Enter the values for n and m: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'm' is initialized [premium-bughuntingUninit]
     *  Cannot determine that 'n' is initialized [premium-bughuntingUninit]
     */
    scanf("%d %d", &n, &m);
    
    printf("Eulerian number a(%d, %d) is: %d\n", n, m, eulerianNumber(n, m));
    
    return 0;
}