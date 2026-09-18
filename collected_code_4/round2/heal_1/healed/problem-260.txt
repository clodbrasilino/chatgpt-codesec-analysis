#include <stdio.h>

int nswn_prime(int n)
{
    int a = 1, b = 1, result = 1;
    if(n == 0 || n == 1)
    {
        return result;
    }
    else
    {
        for(int i = 2; i <= n; i++)
        {
            result = 2*b + a;
            a = b;
            b = result;
        }
        return result;
    }
    
    return -1;
}

int main()
{
    int number;
    printf("Enter the nth number to find the corresponding Newman–Shanks–Williams prime number:");
    scanf("%d", &number);
    if(number >= 0)
    {
        printf("%dth Newman–Shanks–Williams prime number is %d\n", number, nswn_prime(number));
    }
    else
    {
        printf("Invalid number!\n");
    }
  
    return 0;
}