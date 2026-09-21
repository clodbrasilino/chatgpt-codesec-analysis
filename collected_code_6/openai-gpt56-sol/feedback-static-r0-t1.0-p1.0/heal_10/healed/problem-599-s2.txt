#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>

#define INPUT_SIZE 256U

static int calculate_sum_and_average(unsigned long long n,
                                     unsigned long long *sum,
                                     long double *average)
{
    unsigned long long a;
    unsigned long long b;

    if (sum == NULL || average == NULL || n == 0ULL || n == ULLONG_MAX) {
        return -1;
    }

    a = n;
    b = n + 1ULL;

    if ((a & 1ULL) == 0ULL) {
        a /= 2ULL;
    } else {
        b /= 2ULL;
    }

    if (a != 0ULL && b > ULLONG_MAX / a) {
        return -1;
    }

    *sum = a * b;
    *average = ((long double)n + 1.0L) / 2.0L;

    return 0;
}

static int read_input(char **buffer)
{
    size_t length = 0U;
    size_t capacity = 32U;
    int ch;
    char *input;

    if (buffer == NULL) {
        return -1;
    }

    *buffer = NULL;
    input = malloc(capacity);
    if (input == NULL) {
        return -1;
    }

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length >= INPUT_SIZE - 1U) {
            while (ch != '\n' && ch != EOF) {
                ch = fgetc(stdin);
            }

            if (ch == EOF && ferror(stdin)) {
                free(input);
                return -1;
            }

            free(input);
            return 1;
        }

        if (length + 1U >= capacity) {
            size_t new_capacity;
            char *resized;

            new_capacity = capacity * 2U;
            if (new_capacity > INPUT_SIZE) {
                new_capacity = INPUT_SIZE;
            }

            resized = realloc(input, new_capacity);
            if (resized == NULL) {
                free(input);
                return -1;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ch == EOF && ferror(stdin)) {
        free(input);
        return -1;
    }

    if (ch == EOF && length == 0U) {
        free(input);
        return -1;
    }

    input[length] = '\0';
    *buffer = input;

    return 0;
}

int main(void)
{
    char *input;
    char *start;
    char *end;
    unsigned long long n;
    unsigned long long sum;
    long double average;
    int read_result;
    int status = EXIT_FAILURE;

    read_result = read_input(&input);

    if (read_result < 0) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (read_result > 0) {
        fputs("Input is too large.\n", stderr);
        return EXIT_FAILURE;
    }

    start = input;
    while (*start != '\0' && isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '-' || *start == '+') {
        fputs("Input must be a positive integer.\n", stderr);
        goto cleanup;
    }

    errno = 0;
    end = NULL;
    n = strtoull(start, &end, 10);

    if (errno == ERANGE || end == NULL || end == start) {
        fputs("Invalid input.\n", stderr);
        goto cleanup;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0' || n == 0ULL) {
        fputs("Input must be a positive integer.\n", stderr);
        goto cleanup;
    }

    if (calculate_sum_and_average(n, &sum, &average) != 0) {
        fputs("The result is outside the supported range.\n", stderr);
        goto cleanup;
    }

    if (printf("Sum: %llu\nAverage: %.2Lf\n", sum, average) < 0) {
        fputs("Failed to write output.\n", stderr);
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(input);
    return status;
}