#include <stdio.h>
#include <stdbool.h>

int sumOfDivisors(int n)
{
    int sum = 0;
    for (int i = 1; i <= n; i++)
    {
        if (n % i == 0)
        {
            sum += i;
        }
    }
    return sum;
}

bool checkSumOfDivisors(int a, int b)
{
    return (sumOfDivisors(a) == sumOfDivisors(b)) ? true : false;
}

int main()
{
    int a,b;
    printf("Enter two numbers: ");
    scanf("%d%d",&a,&b);

    if (checkSumOfDivisors(a, b))
    {
        printf("The sum of divisors for %d and %d are the same.\n", a, b);
    }
    else
    {
        printf("The sum of divisors for %d and %d are not the same.\n", a, b);
    }
    return 0;
}