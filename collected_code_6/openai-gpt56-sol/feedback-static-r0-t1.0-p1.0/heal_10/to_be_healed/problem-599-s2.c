#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>
#include <string.h>

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

static int discard_remaining_input(void)
{
    int ch;

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    } while (ch != '\n' && ch != EOF);

    if (ch == EOF && ferror(stdin)) {
        return -1;
    }

    return 0;
}

static int read_input(char *buffer, size_t size)
{
    char *newline;

    if (buffer == NULL || size < 2U || size > (size_t)INT_MAX) {
        return -1;
    }

    if (fgets(buffer, (int)size, stdin) == NULL) {
        return -1;
    }

    newline = strchr(buffer, '\n');
    if (newline != NULL) {
        *newline = '\0';
        return 0;
    }

    if (feof(stdin)) {
        return 0;
    }

    if (discard_remaining_input() != 0) {
        return -1;
    }

    return 1;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[INPUT_SIZE];
    char *start;
    char *end;
    unsigned long long n;
    unsigned long long sum;
    long double average;
    int read_result;

    read_result = read_input(input, sizeof input);

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
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    n = strtoull(start, &end, 10);

    if (errno == ERANGE || end == NULL || end == start) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0' || n == 0ULL) {
        fputs("Input must be a positive integer.\n", stderr);
        return EXIT_FAILURE;
    }

    if (calculate_sum_and_average(n, &sum, &average) != 0) {
        fputs("The result is outside the supported range.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Sum: %llu\nAverage: %.2Lf\n", sum, average) < 0) {
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}