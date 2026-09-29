#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static int checked_add(long long a, long long b, long long *result)
{
    if ((b > 0 && a > LLONG_MAX - b) ||
        (b < 0 && a < LLONG_MIN - b)) {
        return 1;
    }
    *result = a + b;
    return 0;
}

static int checked_mul(long long a, long long b, long long *result)
{
    if (a > 0) {
        if (b > 0) {
            if (a > LLONG_MAX / b) {
                return 1;
            }
        } else if (b < LLONG_MIN / a) {
            return 1;
        }
    } else if (a < 0) {
        if (b > 0) {
            if (a < LLONG_MIN / b) {
                return 1;
            }
        } else if (b < 0 && b < LLONG_MAX / a) {
            return 1;
        }
    }
    *result = a * b;
    return 0;
}

long long arithmetic_progression_sum(long long first_term, long long common_difference, long long num_terms, int *error)
{
    long long step_total;
    long long last_term;
    long long total;
    long long product;

    if (error == NULL) {
        return 0;
    }

    *error = 0;

    if (num_terms <= 0) {
        *error = 1;
        return 0;
    }

    if (checked_mul(num_terms - 1, common_difference, &step_total) != 0) {
        *error = 1;
        return 0;
    }

    if (checked_add(first_term, step_total, &last_term) != 0) {
        *error = 1;
        return 0;
    }

    if (checked_add(first_term, last_term, &total) != 0) {
        *error = 1;
        return 0;
    }

    if (checked_mul(num_terms, total, &product) != 0) {
        *error = 1;
        return 0;
    }

    return product / 2;
}

int main(void)
{
    long long first_term;
    long long common_difference;
    long long num_terms;
    long long result;
    int error;

    printf("Enter the first term: ");
    if (scanf("%lld", &first_term) != 1) {
        fprintf(stderr, "Invalid input for first term.\n");
        return EXIT_FAILURE;
    }

    printf("Enter the common difference: ");
    if (scanf("%lld", &common_difference) != 1) {
        fprintf(stderr, "Invalid input for common difference.\n");
        return EXIT_FAILURE;
    }

    printf("Enter the number of terms: ");
    if (scanf("%lld", &num_terms) != 1) {
        fprintf(stderr, "Invalid input for number of terms.\n");
        return EXIT_FAILURE;
    }

    result = arithmetic_progression_sum(first_term, common_difference, num_terms, &error);

    if (error != 0) {
        fprintf(stderr, "Error: invalid parameters or arithmetic overflow.\n");
        return EXIT_FAILURE;
    }

    printf("Sum of the arithmetic progression: %lld\n", result);

    return EXIT_SUCCESS;
}