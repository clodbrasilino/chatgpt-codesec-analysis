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
        return 0;
    }

    a = n;
    b = n + 1ULL;

    if ((a & 1ULL) == 0ULL) {
        a /= 2ULL;
    } else {
        b /= 2ULL;
    }

    if (b != 0ULL && a > ULLONG_MAX / b) {
        return 0;
    }

    *sum = a * b;
    *average = (long double)(n + 1ULL) / 2.0L;

    return 1;
}

static int read_line(char **buffer)
{
    size_t capacity = 64U;
    size_t length = 0U;
    char *input;

    if (buffer == NULL) {
        return 0;
    }

    *buffer = NULL;
    input = malloc(capacity);
    if (input == NULL) {
        return 0;
    }

    for (;;) {
        int ch;

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);

        if (ch == '\n') {
            break;
        }

        if (ch == EOF) {
            if (ferror(stdin) || length == 0U) {
                free(input);
                return 0;
            }
            break;
        }

        if (length > SIZE_MAX - 2U) {
            free(input);
            return 0;
        }

        if (length + 1U >= capacity) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2U) {
                free(input);
                return 0;
            }

            new_capacity = capacity * 2U;
            resized = realloc(input, new_capacity);
            if (resized == NULL) {
                free(input);
                return 0;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)(unsigned char)ch;
    }

    input[length] = '\0';
    *buffer = input;

    return 1;
}

int main(void)
{
    char *input = NULL;
    char *start;
    char *end;
    unsigned long long n;
    unsigned long long sum;
    long double average;

    if (!read_line(&input)) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    start = input;
    while (*start != '\0' && isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '-' || *start == '+') {
        free(input);
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    n = strtoull(start, &end, 10);

    if (errno == ERANGE || end == start || n == 0ULL) {
        free(input);
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

    if (!calculate_sum_and_average(n, &sum, &average)) {
        fputs("The result is outside the supported range.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Sum: %llu\nAverage: %.2Lf\n", sum, average) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}