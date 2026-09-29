#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

int find_nth_digit(int numerator, int denominator, int n) {
    if (denominator == 0 || n <= 0) {
        return -1;
    }

    long long num = (long long)numerator;
    long long den = (long long)denominator;

    if (num < 0) num = -num;
    if (den < 0) den = -den;

    num = num % den;

    for (int i = 0; i < n; i++) {
        num *= 10;
        if (i == n - 1) {
            return (int)(num / den);
        }
        num = num % den;
    }

    return -1;
}

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char const * const argv[const]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <numerator> <denominator> <n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    char *endptr1 = NULL;
    long val1 = strtol(argv[1], &endptr1, 10);
    if (endptr1 == argv[1] || *endptr1 != '\0' || errno == ERANGE || val1 < INT_MIN || val1 > INT_MAX) {
        fprintf(stderr, "Invalid input parameters\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    char *endptr2 = NULL;
    long val2 = strtol(argv[2], &endptr2, 10);
    if (endptr2 == argv[2] || *endptr2 != '\0' || errno == ERANGE || val2 < INT_MIN || val2 > INT_MAX || val2 == 0) {
        fprintf(stderr, "Invalid input parameters\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    char *endptr3 = NULL;
    long val3 = strtol(argv[3], &endptr3, 10);
    if (endptr3 == argv[3] || *endptr3 != '\0' || errno == ERANGE || val3 < 1 || val3 > INT_MAX) {
        fprintf(stderr, "Invalid input parameters\n");
        return EXIT_FAILURE;
    }

    int numerator = (int)val1;
    int denominator = (int)val2;
    int n = (int)val3;

    int result = find_nth_digit(numerator, denominator, n);

    if (result == -1) {
        fprintf(stderr, "Invalid calculation parameters\n");
        return EXIT_FAILURE;
    }

    printf("%d\n", result);

    return EXIT_SUCCESS;
}