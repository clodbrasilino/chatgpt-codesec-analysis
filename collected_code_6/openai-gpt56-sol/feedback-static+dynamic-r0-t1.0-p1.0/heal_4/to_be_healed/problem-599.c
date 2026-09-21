#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>

static int calculate_sum_and_average(unsigned long long n,
                                     unsigned long long *sum,
                                     long double *average)
{
    unsigned long long left;
    unsigned long long right;

    if (sum == NULL || average == NULL || n == 0ULL || n == ULLONG_MAX) {
        return -1;
    }

    if ((n & 1ULL) == 0ULL) {
        left = n / 2ULL;
        right = n + 1ULL;
    } else {
        left = n;
        right = (n / 2ULL) + 1ULL;
    }

    if (right != 0ULL && left > ULLONG_MAX / right) {
        return -1;
    }

    *sum = left * right;
    *average = ((long double)n + 1.0L) / 2.0L;

    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0U;
    size_t length = 0U;
    char *end;
    unsigned long long n;
    unsigned long long sum;
    long double average;
    int ch;
    int result = EXIT_FAILURE;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length == capacity) {
            size_t new_capacity;
            char *new_input;

            if (capacity == 0U) {
                new_capacity = 64U;
            } else {
                if (capacity > (SIZE_MAX / 2U)) {
                    goto cleanup;
                }
                new_capacity = capacity * 2U;
            }

            new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                goto cleanup;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ferror(stdin) || (ch == EOF && length == 0U)) {
        goto cleanup;
    }

    if (length == capacity) {
        char *new_input;

        if (capacity == SIZE_MAX) {
            goto cleanup;
        }

        new_input = realloc(input, capacity + 1U);
        if (new_input == NULL) {
            goto cleanup;
        }

        input = new_input;
        capacity++;
    }

    input[length] = '\0';

    errno = 0;
    end = NULL;
    n = strtoull(input, &end, 10);

    if (errno == ERANGE || end == input || n == 0ULL) {
        goto cleanup;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        goto cleanup;
    }

    if (calculate_sum_and_average(n, &sum, &average) != 0) {
        goto cleanup;
    }

    if (printf("Sum: %llu\nAverage: %.2Lf\n", sum, average) < 0) {
        goto cleanup;
    }

    result = EXIT_SUCCESS;

cleanup:
    free(input);
    return result;
}