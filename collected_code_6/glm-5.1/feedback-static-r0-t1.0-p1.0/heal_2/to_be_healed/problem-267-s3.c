#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'UINT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

unsigned long long sum_of_squares_of_odds(unsigned int n) {
    unsigned long long max_n = (unsigned long long)((1ULL << 63) - 1) / 4ULL;
    if (n > max_n) {
        return 0;
    }
    return (unsigned long long)n * (2ULL * n - 1ULL) * (2ULL * n + 1ULL) / 3ULL;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }

    char *endptr;
    unsigned long long val = strtoull(argv[1], &endptr, 10);

    /* Possible weaknesses found:
     *  each undeclared identifier is reported only once for each function it appears in
     *  use of undeclared identifier 'UINT_MAX'
     *  'UINT_MAX' undeclared (first use in this function)
     */
    if (*endptr != '\0' || val > UINT_MAX) {
        return EXIT_FAILURE;
    }

    unsigned int n = (unsigned int)val;

    unsigned long long result = sum_of_squares_of_odds(n);

    if (result == 0 && val != 0) {
        return EXIT_FAILURE;
    }

    printf("%llu\n", result);

    return EXIT_SUCCESS;
}