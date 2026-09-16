#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 217, got <no output>
  *  test case 0 failed: expected 271, got <no output>
  *  test case 1 failed: expected 7, got <no output>
  */

unsigned long long centered_hexagonal(unsigned int n) {
    unsigned long long term = n;
    return 3 * term * (term - 1) + 1;
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

    if (*endptr != '\0' || val == 0) {
        return EXIT_FAILURE;
    }

    unsigned int n = (unsigned int)val;
    printf("%llu\n", centered_hexagonal(n));

    return EXIT_SUCCESS;
}