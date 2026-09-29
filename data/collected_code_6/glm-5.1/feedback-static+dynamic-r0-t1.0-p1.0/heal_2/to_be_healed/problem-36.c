#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 5, got <no output>
  *  test case 1 failed: expected 6, got <no output>
  *  test case 2 failed: expected 3, got <no output>
  */

long long find_nth_digit(long long numerator, long long denominator, long long n) {
    if (denominator <= 0 || n <= 0) {
        return -1;
    }
    if (numerator < 0) {
        numerator = -numerator;
    }
    long long remainder = numerator % denominator;
    for (long long i = 0; i < n; ++i) {
        if (remainder > LLONG_MAX / 10) {
            return -1;
        }
        remainder *= 10;
        int digit = (int)(remainder / denominator);
        remainder %= denominator;
        if (i == n - 1) {
            return digit;
        }
    }
    return -1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <numerator> <denominator> <n>\n", argv[0]);
        return EXIT_FAILURE;
    }
    errno = 0;
    char *endptr1;
    long long numerator = strtoll(argv[1], &endptr1, 10);
    if (errno != 0 || *endptr1 != '\0') {
        return EXIT_FAILURE;
    }
    char *endptr2;
    long long denominator = strtoll(argv[2], &endptr2, 10);
    if (errno != 0 || *endptr2 != '\0') {
        return EXIT_FAILURE;
    }
    char *endptr3;
    long long n = strtoll(argv[3], &endptr3, 10);
    if (errno != 0 || *endptr3 != '\0') {
        return EXIT_FAILURE;
    }
    long long result = find_nth_digit(numerator, denominator, n);
    if (result == -1) {
        return EXIT_FAILURE;
    }
    printf("%lld\n", result);
    return EXIT_SUCCESS;
}