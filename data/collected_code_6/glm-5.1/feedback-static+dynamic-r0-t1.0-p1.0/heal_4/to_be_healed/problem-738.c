#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 1.99609375, got 1.9921875
  *  test case 1 failed: expected 1.9375, got 1.875
  *  test case 0 failed: expected 1.9921875, got 1.984375
  */

double geometric_sum(int n) {
    if (n <= 0) {
        return 0.0;
    }
    return 2.0 - (1.0 / (1U << (n - 1)));
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
    if (*endptr != '\0' || val < 0 || val > INT_MAX) {
        return EXIT_FAILURE;
    }
    double result = geometric_sum((int)val);
    printf("%f\n", result);
    return EXIT_SUCCESS;
}