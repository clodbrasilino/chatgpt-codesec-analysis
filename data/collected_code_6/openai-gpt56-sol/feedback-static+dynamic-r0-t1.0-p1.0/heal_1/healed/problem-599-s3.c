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

    if (a > ULLONG_MAX / b) {
        return 0;
    }

    *sum = a * b;
    *average = (long double)(*sum) / (long double)n;
    return 1;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0U;
    size_t length = 0U;
    int ch;
    char *end;
    unsigned long long n;
    unsigned long long sum;
    long double average;

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        char *resized;

        if (length == capacity) {
            size_t new_capacity = capacity == 0U ? 64U : capacity * 2U;

            if (new_capacity <= capacity) {
                free(input);
                fputs("Input is too long.\n", stderr);
                return EXIT_FAILURE;
            }

            resized = realloc(input, new_capacity);
            if (resized == NULL) {
                free(input);
                fputs("Failed to allocate memory.\n", stderr);
                return EXIT_FAILURE;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ferror(stdin)) {
        free(input);
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (length == 0U && ch == EOF) {
        free(input);
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (length == capacity) {
        char *resized;

        if (capacity == SIZE_MAX) {
            free(input);
            fputs("Input is too long.\n", stderr);
            return EXIT_FAILURE;
        }

        resized = realloc(input, capacity + 1U);
        if (resized == NULL) {
            free(input);
            fputs("Failed to allocate memory.\n", stderr);
            return EXIT_FAILURE;
        }

        input = resized;
    }

    input[length] = '\0';

    errno = 0;
    end = NULL;
    n = strtoull(input, &end, 10);

    if (errno == ERANGE || end == input || n == 0ULL) {
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