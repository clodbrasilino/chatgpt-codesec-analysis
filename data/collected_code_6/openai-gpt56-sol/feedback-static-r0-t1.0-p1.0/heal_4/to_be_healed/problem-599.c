#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>

static int calculate_sum_and_average(unsigned long long n,
                                     unsigned long long *sum,
                                     long double *average)
{
    unsigned long long a;
    unsigned long long b;

    if (sum == NULL || average == NULL || n == 0ULL || n == ULLONG_MAX) {
        return -1;
    }

    if ((n & 1ULL) == 0ULL) {
        a = n / 2ULL;
        b = n + 1ULL;
    } else {
        a = n;
        b = n / 2ULL + 1ULL;
    }

    if (a != 0ULL && b > ULLONG_MAX / a) {
        return -1;
    }

    *sum = a * b;
    *average = (long double)n / 2.0L + 0.5L;

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
    int status = EXIT_FAILURE;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        char *resized;
        size_t new_capacity;

        if (length == SIZE_MAX - 1U) {
            goto cleanup;
        }

        if (length + 1U >= capacity) {
            if (capacity == 0U) {
                new_capacity = 64U;
            } else {
                if (capacity > SIZE_MAX / 2U) {
                    goto cleanup;
                }
                new_capacity = capacity * 2U;
            }

            resized = realloc(input, new_capacity);
            if (resized == NULL) {
                goto cleanup;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ferror(stdin) || (ch == EOF && length == 0U)) {
        goto cleanup;
    }

    if (length + 1U > capacity) {
        char *resized = realloc(input, length + 1U);

        if (resized == NULL) {
            goto cleanup;
        }

        input = resized;
        /* Possible weaknesses found:
         *  Value stored to 'capacity' is never read [deadcode.DeadStores]
         */
        capacity = length + 1U;
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

    status = EXIT_SUCCESS;

cleanup:
    free(input);
    return status;
}