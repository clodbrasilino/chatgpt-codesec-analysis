#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>
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
    *average = (n & 1ULL) != 0
                   ? (long double)(n / 2) + 1.0L
                   : (long double)(n / 2) + 0.5L;

    return 0;
}

int main(void)
{
    char input[INPUT_SIZE];
    char *end;
    unsigned long long n;
    unsigned long long sum;
    long double average;
    size_t length;
    int ch;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    length = 0;
    while (input[length] != '\0' && input[length] != '\n') {
        ++length;
    }

    if (input[length] == '\n') {
        input[length] = '\0';
    } else {
        ch = getchar();
        if (ch != '\n' && ch != EOF) {
            do {
                ch = getchar();
            } while (ch != '\n' && ch != EOF);

            fputs("Input is too large.\n", stderr);
            return EXIT_FAILURE;
        }
    }

    end = input;
    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end == '-' || *end == '+') {
        fputs("Input must be a positive integer.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    n = strtoull(end, &end, 10);

    if (errno == ERANGE || end == input) {
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