#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 217, got <no output>
  *  test case 0 failed: expected 271, got <no output>
  *  test case 1 failed: expected 7, got <no output>
  */

unsigned long long centered_hexagonal(int n) {
    if (n < 1) {
        return 0;
    }
    return 3ULL * n * n - 3ULL * n + 1ULL;
}

int main(int argc, char const * const * argv) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }

    char *endptr;
    long val = strtol(argv[1], &endptr, 10);

    if (*endptr != '\0' || val < 1) {
        return EXIT_FAILURE;
    }

    unsigned long long result = centered_hexagonal((int)val);
    printf("%llu\n", result);

    return EXIT_SUCCESS;
}