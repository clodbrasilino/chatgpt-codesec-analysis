#include <stdio.h>
#include <stdbool.h>

bool canRepresentAsSumOfNonZeroPowersOf2(long long n)
{
    if (n <= 0)
    {
        return false;
    }
    return (n % 2 == 0);
}

int main(void)
{
    long long number;

    printf("Enter a number: ");
    if (scanf("%lld", &number) != 1)
    {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }

    if (canRepresentAsSumOfNonZeroPowersOf2(number))
    {
        printf("%lld can be represented as sum of non-zero powers of 2.\n", number);
    }
    else
    {
        printf("%lld cannot be represented as sum of non-zero powers of 2.\n", number);
    }

    return 0;
}