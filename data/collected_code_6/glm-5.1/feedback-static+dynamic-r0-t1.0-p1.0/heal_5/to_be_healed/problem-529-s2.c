#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 17, got <no output>
  *  test case 0 failed: expected 31, got <no output>
  *  test case 1 failed: expected 5, got <no output>
  */

unsigned long long jacobsthal_lucas(int n) {
    if (n < 0) {
        exit(EXIT_FAILURE);
    }
    if (n == 0) {
        return 2;
    }
    if (n == 1) {
        return 1;
    }
    unsigned long long a = 2;
    unsigned long long b = 1;
    for (int i = 2; i <= n; i++) {
        unsigned long long c = b + 2 * a;
        a = b;
        b = c;
    }
    return b;
}

int main(int argc, char const * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *endptr;
    long n_long = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || n_long < 0 || n_long > INT_MAX) {
        return EXIT_FAILURE;
    }
    int n = (int)n_long;
    unsigned long long result = jacobsthal_lucas(n);
    printf("%llu\n", result);
    return EXIT_SUCCESS;
}