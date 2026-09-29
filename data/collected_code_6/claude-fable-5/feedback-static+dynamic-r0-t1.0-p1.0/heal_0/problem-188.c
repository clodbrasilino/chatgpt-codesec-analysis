#include <stdio.h>
#include <stdbool.h>

static bool isProductOfTwoSquares(long long n)
{
    if (n < 0)
    {
        return false;
    }

    if (n == 0)
    {
        return true;
    }

    for (long long i = 1; i * i <= n; i++)
    {
        long long sq = i * i;

        if (n % sq == 0)
        {
            long long rem = n / sq;
            long long j = 1;

            while (j * j < rem)
            {
                j++;
            }

            if (j * j == rem)
            {
                return true;
            }
        }
    }

    return false;
}

int main(void)
{
    long long n = 0;

    printf("Enter a number: ");

    if (scanf("%lld", &n) != 1)
    {
        fprintf(stderr, "Error: invalid input.\n");
        return 1;
    }

    if (isProductOfTwoSquares(n))
    {
        printf("%lld can be represented as a product of two squares.\n", n);
    }
    else
    {
        printf("%lld cannot be represented as a product of two squares.\n", n);
    }

    return 0;
}