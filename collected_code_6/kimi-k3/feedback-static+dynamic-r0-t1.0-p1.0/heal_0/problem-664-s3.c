#include <stdio.h>
#include <stdlib.h>

double average_of_evens(int limit);

int main(void)
{
    int limit = 0;
    double result = 0.0;
    int scan_result = 0;

    printf("Enter an even number: ");
    scan_result = scanf("%d", &limit);

    if (scan_result != 1)
    {
        fprintf(stderr, "Error: Invalid input.\n");
        return EXIT_FAILURE;
    }

    if (limit < 2 || (limit % 2) != 0)
    {
        fprintf(stderr, "Error: Input must be a positive even number.\n");
        return EXIT_FAILURE;
    }

    result = average_of_evens(limit);
    printf("Average of even numbers up to %d: %.2f\n", limit, result);

    return EXIT_SUCCESS;
}

double average_of_evens(int limit)
{
    long long sum = 0;
    long long count = 0;
    int i = 0;

    for (i = 2; i <= limit; i += 2)
    {
        sum += i;
        count++;
    }

    if (count == 0)
    {
        return 0.0;
    }

    return (double)sum / (double)count;
}