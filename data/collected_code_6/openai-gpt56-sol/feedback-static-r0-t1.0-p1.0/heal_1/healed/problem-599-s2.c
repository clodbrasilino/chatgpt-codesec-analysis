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

    if (sum == NULL || average == NULL || n == 0 || n == ULLONG_MAX) {
        return -1;
    }

    a = n;
    b = n + 1;

    if ((a & 1ULL) == 0) {
        a /= 2;
    } else {
        b /= 2;
    }

    if (a != 0 && b > ULLONG_MAX / a) {
        return -1;
    }

    *sum = a * b;
    *average = (long double)b;

    if ((n & 1ULL) == 0) {
        *average = (long double)(n / 2) + 0.5L;
    }

    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int ch;
    char *end;
    unsigned long long n;
    unsigned long long sum;
    long double average;

    while ((ch = getchar()) != '\n' && ch != EOF) {
        char *resized;
        size_t new_capacity;

        if (length + 1 >= capacity) {
            if (capacity == 0) {
                new_capacity = 64;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(input);
                    fputs("Input is too large.\n", stderr);
                    return EXIT_FAILURE;
                }
                new_capacity = capacity * 2;
            }

            resized = realloc(input, new_capacity);
            if (resized == NULL) {
                free(input);
                fputs("Unable to allocate memory.\n", stderr);
                return EXIT_FAILURE;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ch == EOF && length == 0) {
        free(input);
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (length + 1 >= capacity) {
        char *resized;
        size_t new_capacity = capacity == 0 ? 1 : capacity + 1;

        resized = realloc(input, new_capacity);
        if (resized == NULL) {
            free(input);
            fputs("Unable to allocate memory.\n", stderr);
            return EXIT_FAILURE;
        }

        input = resized;
        capacity = new_capacity;
    }

    input[length] = '\0';

    errno = 0;
    end = NULL;
    n = strtoull(input, &end, 10);

    if (errno == ERANGE || end == input) {
        free(input);
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0' || n == 0) {
        free(input);
        fputs("Input must be a positive integer.\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

    if (calculate_sum_and_average(n, &sum, &average) != 0) {
        fputs("The result is outside the supported range.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("Sum: %llu\n", sum);
    printf("Average: %.2Lf\n", average);

    return EXIT_SUCCESS;
}