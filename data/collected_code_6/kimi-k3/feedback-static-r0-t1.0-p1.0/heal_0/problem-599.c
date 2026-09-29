#include <stdio.h>
#include <errno.h>
#include <limits.h>

int calculate_sum_average(int n, long long *sum, double *average)
{
    long long total;
    int i;

    if (n < 0 || sum == NULL || average == NULL)
    {
        return -1;
    }

    total = 0;
    for (i = 1; i <= n; i++)
    {
        if (total > LLONG_MAX - i)
        {
            return -1;
        }
        total += i;
    }

    *sum = total;
    *average = (n > 0) ? ((double)total / n) : 0.0;

    return 0;
}

int main(void)
{
    int n;
    long long sum;
    double average;
    int result;

    printf("Enter a positive integer: ");
    
    if (scanf("%d", &n) != 1)
    {
        fprintf(stderr, "Error: Invalid input\n");
        return 1;
    }

    if (n < 0)
    {
        fprintf(stderr, "Error: Please enter a non-negative integer\n");
        return 1;
    }

    result = calculate_sum_average(n, &sum, &average);
    
    if (result != 0)
    {
        fprintf(stderr, "Error: Calculation failed (overflow or invalid parameters)\n");
        return 1;
    }

    printf("Sum of first %d natural numbers: %lld\n", n, sum);
    printf("Average of first %d natural numbers: %.2f\n", n, average);

    return 0;
}