#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>
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

    if (left > ULLONG_MAX / right) {
        return -1;
    }

    *sum = left * right;
    *average = ((long double)n + 1.0L) / 2.0L;

    return 0;
}

static int read_line(char **buffer, size_t *length)
{
    size_t capacity = 64U;
    size_t used = 0U;
    char *data;

    if (buffer == NULL || length == NULL) {
        return -1;
    }

    *buffer = NULL;
    *length = 0U;

    data = malloc(capacity);
    if (data == NULL) {
        return -1;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = fgetc(stdin);

        if (ch == '\n') {
            break;
        }

        if (ch == EOF) {
            if (ferror(stdin) || used == 0U) {
                free(data);
                return -1;
            }
            break;
        }

        if (used == capacity - 1U) {
            size_t new_capacity;
            char *new_data;

            if (capacity > SIZE_MAX / 2U) {
                free(data);
                return -1;
            }

            new_capacity = capacity * 2U;
            new_data = realloc(data, new_capacity);
            if (new_data == NULL) {
                free(data);
                return -1;
            }

            data = new_data;
            capacity = new_capacity;
        }

        data[used++] = (char)ch;
    }

    data[used] = '\0';
    *buffer = data;
    *length = used;

    return 0;
}

int main(void)
{
    char *input = NULL;
    char *end = NULL;
    size_t length = 0U;
    unsigned long long n;
    unsigned long long sum;
    long double average;
    int result = EXIT_FAILURE;

    if (read_line(&input, &length) != 0) {
        goto cleanup;
    }

    errno = 0;
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