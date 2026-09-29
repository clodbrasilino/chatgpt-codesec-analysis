#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>

#define INPUT_SIZE 256

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
    *average = (long double)n / 2.0L + 0.5L;

    return 0;
}

static int read_input(char *buffer, size_t size)
{
    size_t length;
    int ch;

    if (buffer == NULL || size < 2 || fgets(buffer, size, stdin) == NULL) {
        return -1;
    }

    length = 0;
    while (buffer[length] != '\0' && buffer[length] != '\n') {
        ++length;
    }

    if (buffer[length] == '\n') {
        buffer[length] = '\0';
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    ch = fgetc(stdin);
    if (ch == '\n' || ch == EOF) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
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
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '-' || *start == '+') {
        fputs("Input must be a positive integer.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    n = strtoull(start, &end, 10);

    if (errno == ERANGE || end == start) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0' || n == 0) {
        fputs("Input must be a positive integer.\n", stderr);
        return EXIT_FAILURE;
    }

    if (calculate_sum_and_average(n, &sum, &average) != 0) {
        fputs("The result is outside the supported range.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("Sum: %llu\n", sum);
    printf("Average: %.2Lf\n", average);

    return EXIT_SUCCESS;
}