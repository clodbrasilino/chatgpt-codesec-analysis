#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

double find_average_of_even_numbers(unsigned long long limit)
{
    unsigned long long count;
    unsigned long long sum;

    if (limit == 0ULL || (limit % 2ULL) != 0ULL)
    {
        return 0.0;
    }

    count = limit / 2ULL;

    if (count > 0ULL && (count + 1ULL) > (ULLONG_MAX / count))
    {
        return 0.0;
    }

    sum = count * (count + 1ULL);

    return (double)sum / (double)count;
}

int main(void)
{
    unsigned long long limit;
    double average;

    printf("Enter an even number: ");

    if (scanf("%llu", &limit) != 1)
    {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     *  Assuming that condition 'limit==0ULL' is not redundant
     */
    if (limit == 0ULL || (limit % 2ULL) != 0ULL)
    {
        fprintf(stderr, "The number must be a positive even number.\n");
        return EXIT_FAILURE;
    }

    average = find_average_of_even_numbers(limit);

    /* Possible weaknesses found:
     *  Condition 'limit>0ULL' is always true
     *  Condition 'limit>0ULL' is always true [knownConditionTrueFalse]
     */
    if (average == 0.0 && limit > 0ULL)
    {
        fprintf(stderr, "Error calculating average.\n");
        return EXIT_FAILURE;
    }

    printf("Average of even numbers till %llu is: %.2f\n", limit, average);

    return EXIT_SUCCESS;
}