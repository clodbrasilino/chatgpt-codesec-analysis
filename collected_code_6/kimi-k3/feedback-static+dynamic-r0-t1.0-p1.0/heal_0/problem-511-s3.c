#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

int minSumFactors(int n)
{
    if (n <= 0)
    {
        return -1;
    }

    if (n == 1)
    {
        return 1;
    }

    int sum = 0;
    int temp = n;

    while ((temp % 2) == 0)
    {
        sum += 2;
        temp /= 2;
    }

    for (int i = 3; i <= temp / i; i += 2)
    {
        while ((temp % i) == 0)
        {
            sum += i;
            temp /= i;
        }
    }

    if (temp > 2)
    {
        sum += temp;
    }

    return sum;
}

int main(void)
{
    int number;
    int result;

    printf("Enter a positive integer: ");

    if (scanf("%d", &number) != 1)
    {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    result = minSumFactors(number);

    if (result == -1)
    {
        fprintf(stderr, "Number must be positive\n");
        return EXIT_FAILURE;
    }

    printf("Minimum sum of factors: %d\n", result);

    return EXIT_SUCCESS;
}