#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

int sum_arithmetic_progression(long long first_term, long long common_diff, long long num_terms, long long *result)
{
    long long sum;
    long long last_term;
    long long term_sum;
    long long half_terms;
    long long half_sum;

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

    if (common_diff > 0 && first_term > LLONG_MAX - common_diff * (num_terms - 1))
    {
        return -1;
    }
    if (common_diff < 0 && first_term < LLONG_MIN - common_diff * (num_terms - 1))
    {
        return -1;
    }

    last_term = first_term + common_diff * (num_terms - 1);

    if ((first_term > 0 && last_term > 0 && first_term > LLONG_MAX - last_term) ||
        (first_term < 0 && last_term < 0 && first_term < LLONG_MIN - last_term))
    {
        return -1;
    }
    term_sum = first_term + last_term;

    if (num_terms % 2 == 0)
    {
        half_terms = num_terms / 2;
        if (term_sum > 0 && half_terms > LLONG_MAX / term_sum)
        {
            return -1;
        }
        if (term_sum < 0 && half_terms < LLONG_MIN / term_sum)
        {
            return -1;
        }
        if (term_sum > 0 && half_terms < LLONG_MIN / term_sum)
        {
            return -1;
        }
        if (term_sum < 0 && half_terms > LLONG_MAX / term_sum)
        {
            return -1;
        }
        sum = half_terms * term_sum;
    }
    else
    {
        if (term_sum % 2 == 0)
        {
            half_sum = term_sum / 2;
            if (half_sum > 0 && num_terms > LLONG_MAX / half_sum)
            {
                return -1;
            }
            if (half_sum < 0 && num_terms < LLONG_MIN / half_sum)
            {
                return -1;
            }
            if (half_sum > 0 && num_terms < LLONG_MIN / half_sum)
            {
                return -1;
            }
            if (half_sum < 0 && num_terms > LLONG_MAX / half_sum)
            {
                return -1;
            }
            sum = num_terms * half_sum;
        }
        else
        {
            if (term_sum > 0 && num_terms > LLONG_MAX / term_sum)
            {
                return -1;
            }
            if (term_sum < 0 && num_terms < LLONG_MIN / term_sum)
            {
                return -1;
            }
            if (term_sum > 0 && num_terms < LLONG_MIN / term_sum)
            {
                return -1;
            }
            if (term_sum < 0 && num_terms > LLONG_MAX / term_sum)
            {
                return -1;
            }
            sum = num_terms * term_sum;
            if (sum % 2 != 0)
            {
                return -1;
            }
            sum = sum / 2;
        }
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