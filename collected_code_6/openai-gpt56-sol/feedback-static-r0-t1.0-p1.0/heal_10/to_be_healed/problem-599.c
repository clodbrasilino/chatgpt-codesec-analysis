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
    *average = ((long double)n + 1.0L) / 2.0L;

    return 0;
}

static int read_line(char **line)
{
    char *buffer;
    size_t capacity = 64U;
    size_t length = 0U;

    if (line == NULL) {
        return -1;
    }

    *line = NULL;
    buffer = malloc(capacity);
    if (buffer == NULL) {
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
            if (ferror(stdin) || length == 0U) {
                free(buffer);
                return -1;
            }
            break;
        }

        if (length >= capacity - 1U) {
            char *resized;
            size_t new_capacity;

            if (capacity > SIZE_MAX / 2U) {
                free(buffer);
                return -1;
            }

            new_capacity = capacity * 2U;
            resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return -1;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[length++] = (char)(unsigned char)ch;
    }

    buffer[length] = '\0';
    *line = buffer;

    return 0;
}

int main(void)
{
    char *input = NULL;
    char *start;
    char *end;
    unsigned long long n;
    unsigned long long sum;
    long double average;
    int status = EXIT_FAILURE;

    if (read_line(&input) != 0) {
        goto cleanup;
    }

    start = input;
    while (*start != '\0' && isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '-') {
        goto cleanup;
    }

    errno = 0;
    n = strtoull(start, &end, 10);

    if (errno == ERANGE || end == start || n == 0ULL) {
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