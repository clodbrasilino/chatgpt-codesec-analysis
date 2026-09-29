#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 17, got <no output>
  *  test case 0 failed: expected 31, got <no output>
  *  test case 1 failed: expected 5, got <no output>
  */

long long jacobsthal_lucas(int n) {
    if (n < 0) {
        exit(EXIT_FAILURE);
    }
    if (n == 0) {
        return 2;
    }
    if (n == 1) {
        return 1;
    }
    long long a = 2;
    long long b = 1;
    for (int i = 2; i <= n; i++) {
        long long c = 2 * a - b;
        a = b;
        b = c;
    }
    return b;
}

int main(int argc, char const * const argv[]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    char *endptr;
    errno = 0;
    long val = strtol(argv[1], &endptr, 10);
    if (errno != 0 || endptr == argv[1] || *endptr != '\0' || val < 0 || val > INT_MAX) {
        return EXIT_FAILURE;
    }
    int n = (int)val;
    long long result = jacobsthal_lucas(n);
    printf("%lld\n", result);
    return EXIT_SUCCESS;
}