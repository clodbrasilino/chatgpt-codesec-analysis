#include <stdio.h>

long long int sum_of_powers(int n)
{
    long long int sum = 0;
    for(int i=1; i<=n; i++)
    {
        long long int val = 2*i;
        val = val * val * val * val;
        sum += val;
    }
    return sum;
}

int main()
{
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);

    if(n < 0)
    {
        printf("Input value must not be negative.\n");
        return 1;
    }

    long long int sum = sum_of_powers(n);
    printf("Sum of the fourth power of first %d even natural numbers is %lld\n", n, sum);
    
    return 0;
}