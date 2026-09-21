#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 7, got <no output>
  *  test case 2 failed: expected 217, got <no output>
  *  test case 0 failed: expected 271, got <no output>
  */

unsigned long long centered_hexagonal(unsigned int n) {
    return 1ULL + (unsigned long long)n * (n - 1) * 3;
}

int main(int argc, char * const * const argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return 1;
    }

    char *endptr;
    unsigned long val = strtoul(argv[1], &endptr, 10);

    if (*endptr != '\0' || val < 1 || val > UINT_MAX) {
        fprintf(stderr, "Invalid input. n must be a positive integer.\n");
        return 1;
    }

    unsigned int n = (unsigned int)val;
    unsigned long long result = centered_hexagonal(n);

    printf("%llu\n", result);
    fflush(stdout);
    return 0;
}