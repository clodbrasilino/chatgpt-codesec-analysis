#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 56.0, got <no output>
  *  test case 0 failed: expected 35.0, got <no output>
  *  test case 2 failed: expected 84.0, got <no output>
  */

unsigned long long tetrahedral_number(unsigned int n) {
    unsigned long long term = (unsigned long long)n;
    return term * (term + 1) * (term + 2) / 6;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }

    char *endptr;
    unsigned long val = strtoul(argv[1], &endptr, 10);

    if (*endptr != '\0' || val > 2147483647) {
        return EXIT_FAILURE;
    }

    unsigned int n = (unsigned int)val;
    unsigned long long result = tetrahedral_number(n);
    printf("%llu\n", result);

    return EXIT_SUCCESS;
}