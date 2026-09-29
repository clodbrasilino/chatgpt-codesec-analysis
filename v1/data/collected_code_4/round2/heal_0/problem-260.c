#include <stdio.h>

int nswn_prime(int n)
{
    int result;
    if(n == 0)
    {
        return 1;
    }
    else if(n == 1)
    {
        return 1;
    }
    else
    {
        int a = 1, b = 1;
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