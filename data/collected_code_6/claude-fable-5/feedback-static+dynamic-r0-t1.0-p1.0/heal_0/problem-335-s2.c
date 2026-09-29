#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long arithmetic_progression_sum(long long first_term, long long common_difference, long long num_terms, int *error)
{
    long long last_term;
    long long total;

    if (error == NULL) {
        return 0;
    }

    *error = 0;

    if (num_terms <= 0) {
        *error = 1;
        return 0;
    }

    if (common_difference != 0) {
        if ((num_terms - 1) > (LLONG_MAX / (common_difference > 0 ? common_difference : -common_difference))) {
            *error = 1;
            return 0;
        }
    }

    last_term = first_term + (num_terms - 1) * common_difference;

    if ((first_term > 0 && last_term > LLONG_MAX - first_term) ||
        (first_term < 0 && last_term < LLONG_MIN - first_term)) {
        *error = 1;
        return 0;
    }

    total = first_term + last_term;

    if (total != 0 && num_terms > LLONG_MAX / (total > 0 ? total : -total)) {
        *error = 1;
        return 0;
    }

    return (num_terms * total) / 2;
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