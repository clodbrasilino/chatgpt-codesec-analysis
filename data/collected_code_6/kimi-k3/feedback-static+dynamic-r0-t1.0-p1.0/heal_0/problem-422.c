#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

double average_of_cubes(int n)
{
    if (n <= 0)
    {
        return 0.0;
    }

    double sum = 0.0;
    int i;

    for (i = 1; i <= n; i++)
    {
        sum += (double)i * i * i;
    }

    return sum / n;
}

int main(void)
{
    int n;
    double result;

    printf("Enter a positive integer: ");

    if (scanf("%d", &n) != 1)
    {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (n <= 0)
    {
        fprintf(stderr, "Number must be positive\n");
        return EXIT_FAILURE;
    }

    result = average_of_cubes(n);
    printf("Average of cubes of first %d natural numbers: %.6f\n", n, result);

    return EXIT_SUCCESS;
}