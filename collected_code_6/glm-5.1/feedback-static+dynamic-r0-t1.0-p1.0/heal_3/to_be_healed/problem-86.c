#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 217, got 225
  *  test case 1 failed: expected 7, got 8
  *  test case 0 failed: expected 271, got 280
  */

unsigned long long centered_hexagonal(int n) {
    if (n < 1) {
        return 0;
    }
    return (unsigned long long)(3 * n - 2) * n;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
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