#include <stdio.h>
#include <limits.h>

double average_of_odd_numbers(int limit);

int main(void)
{
    int limit;
    double result;

    printf("Enter an odd number: ");
    if (scanf("%d", &limit) != 1)
    {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    if (limit < 1 || limit % 2 == 0)
    {
        fprintf(stderr, "Input must be a positive odd number\n");
        return 1;
    }

    result = average_of_odd_numbers(limit);
    printf("Average of odd numbers till %d: %.2f\n", limit, result);

    return 0;
}

double average_of_odd_numbers(int limit)
{
    if (limit < 1 || limit % 2 == 0)
    {
        return 0.0;
    }

    long long sum = 0;
    int count = 0;
    int i;

    for (i = 1; i <= limit; i += 2)
    {
        if (sum > LLONG_MAX - i)
        {
            return -1.0;
        }
        sum += i;
        count++;
    }

    if (count == 0)
    {
        return 0.0;
    }

    return (double)sum / count;
}