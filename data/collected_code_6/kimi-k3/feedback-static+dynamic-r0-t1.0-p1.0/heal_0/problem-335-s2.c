#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

int sum_arithmetic_progression(long long first_term, long long common_diff, long long num_terms, long long *result)
{
    long long sum;
    long long last_term;

    if (result == NULL || num_terms < 0)
    {
        return -1;
    }

    if (num_terms == 0)
    {
        *result = 0;
        return 0;
    }

    if (num_terms > 1)
    {
        if (common_diff > 0 && (num_terms - 1) > LLONG_MAX / common_diff)
        {
            return -1;
        }
        if (common_diff < 0 && (num_terms - 1) < LLONG_MIN / common_diff)
        {
            return -1;
        }
    }

    last_term = first_term + common_diff * (num_terms - 1);

    if (num_terms % 2 == 0)
    {
        if ((first_term > 0 && last_term > 0 && first_term > LLONG_MAX - last_term) ||
            (first_term < 0 && last_term < 0 && first_term < LLONG_MIN - last_term))
        {
            return -1;
        }
        if (num_terms / 2 > LLONG_MAX / (first_term + last_term) ||
            num_terms / 2 < LLONG_MIN / (first_term + last_term))
        {
            return -1;
        }
        sum = (num_terms / 2) * (first_term + last_term);
    }
    else
    {
        if ((first_term > 0 && last_term > 0 && first_term > LLONG_MAX - last_term) ||
            (first_term < 0 && last_term < 0 && first_term < LLONG_MIN - last_term))
        {
            return -1;
        }
        if (num_terms > LLONG_MAX / ((first_term + last_term) / 2) ||
            num_terms < LLONG_MIN / ((first_term + last_term) / 2))
        {
            return -1;
        }
        sum = num_terms * ((first_term + last_term) / 2);
    }

    *result = sum;
    return 0;
}

int main(void)
{
    long long first_term;
    long long common_diff;
    long long num_terms;
    long long result;
    int scan_result;

    printf("Enter first term: ");
    scan_result = scanf("%lld", &first_term);
    if (scan_result != 1)
    {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    printf("Enter common difference: ");
    scan_result = scanf("%lld", &common_diff);
    if (scan_result != 1)
    {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    printf("Enter number of terms: ");
    scan_result = scanf("%lld", &num_terms);
    if (scan_result != 1)
    {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (sum_arithmetic_progression(first_term, common_diff, num_terms, &result) != 0)
    {
        fprintf(stderr, "Error: invalid parameters or arithmetic overflow\n");
        return EXIT_FAILURE;
    }

    printf("Sum of arithmetic progression: %lld\n", result);

    return EXIT_SUCCESS;
}