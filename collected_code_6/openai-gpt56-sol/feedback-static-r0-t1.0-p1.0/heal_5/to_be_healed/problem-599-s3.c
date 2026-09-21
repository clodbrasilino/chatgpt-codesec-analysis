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
        return 0;
    }

    a = n;
    b = n + 1ULL;

    if ((a & 1ULL) == 0ULL) {
        a /= 2ULL;
    } else {
        b /= 2ULL;
    }

    if (a != 0ULL && b > ULLONG_MAX / a) {
        return 0;
    }

    *sum = a * b;
    *average = (long double)*sum / (long double)n;

    return 1;
}

static int read_number(unsigned long long *value)
{
    char *input = NULL;
    size_t length = 0;
    size_t capacity = 32;
    int ch;
    char *end;
    unsigned long long parsed;

    if (value == NULL) {
        return 0;
    }

    input = malloc(capacity);
    if (input == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2) {
                free(input);
                return 0;
            }

            new_capacity = capacity * 2;
            resized = realloc(input, new_capacity);
            if (resized == NULL) {
                free(input);
                return 0;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ch == EOF && ferror(stdin)) {
        free(input);
        return 0;
    }

    if (length == 0) {
        free(input);
        return 0;
    }

    input[length] = '\0';

    errno = 0;
    end = NULL;
    parsed = strtoull(input, &end, 10);

    if (errno == ERANGE || end == input || parsed == 0ULL) {
        free(input);
        return 0;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        return 0;
    }

    *value = parsed;
    free(input);
    return 1;
}

int main(void)
{
    unsigned long long n;
    unsigned long long sum;
    long double average;

    if (!read_number(&n)) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!calculate_sum_and_average(n, &sum, &average)) {
        fputs("The result is outside the supported range.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Sum: %llu\nAverage: %.2Lf\n", sum, average) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}