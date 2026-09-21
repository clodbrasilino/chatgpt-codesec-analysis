#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

int find_nth_digit(int numerator, int denominator, int n) {
    if (denominator == 0 || n <= 0) {
        return -1;
    }

    if (numerator < 0) {
        numerator = -numerator;
    }
    if (denominator < 0) {
        denominator = -denominator;
    }

    numerator = numerator % denominator;

    for (int i = 0; i < n; i++) {
        numerator *= 10;
        if (i == n - 1) {
            return numerator / denominator;
        }
        numerator = numerator % denominator;
    }

    return -1;
}

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[const]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <numerator> <denominator> <n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    errno = 0;
    long val = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || errno == ERANGE || val < INT_MIN || val > INT_MAX) {
        return EXIT_FAILURE;
    }
    int numerator = (int)val;

    errno = 0;
    val = strtol(argv[2], &endptr, 10);
    if (*endptr != '\0' || errno == ERANGE || val == 0 || val < INT_MIN || val > INT_MAX) {
        return EXIT_FAILURE;
    }
    int denominator = (int)val;

    errno = 0;
    val = strtol(argv[3], &endptr, 10);
    if (*endptr != '\0' || errno == ERANGE || val <= 0 || val > INT_MAX) {
        return EXIT_FAILURE;
    }
    int n = (int)val;

    int result = find_nth_digit(numerator, denominator, n);
    if (result == -1) {
        return EXIT_FAILURE;
    }

    printf("%d\n", result);
    return EXIT_SUCCESS;
}