#include <stdio.h>
#include <stdlib.h>

int can_be_represented(long long n);

int can_be_represented(long long n)
{
    if (n <= 0)
    {
        return 0;
    }
    if ((n % 2) == 0)
    {
        return 1;
    }
    return 0;
}

int main(void)
{
    long long number;
    int result;

    printf("Enter a number: ");
    result = scanf("%lld", &number);
    if (result != 1)
    {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (can_be_represented(number))
    {
        printf("%lld can be represented as sum of non-zero powers of 2\n", number);
    }
    else
    {
        printf("%lld cannot be represented as sum of non-zero powers of 2\n", number);
    }

    return EXIT_SUCCESS;
}