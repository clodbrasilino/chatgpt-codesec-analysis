#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 2.9289682539682538, got <no output>
  *  test case 2 failed: expected 2.5928571428571425, got <no output>
  *  test case 1 failed: expected 2.083333333333333, got <no output>
  */

double harmonic_sum(int n) {
    if (n <= 1) {
        return 0.0;
    }
    double sum = 0.0;
    int i;
    for (i = 1; i < n; i++) {
        sum += 1.0 / (double)i;
    }
    return sum;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || val < 0 || val > INT_MAX) {
        fprintf(stderr, "Invalid input: must be a non-negative integer within range\n");
        return EXIT_FAILURE;
    }
    double result = harmonic_sum((int)val);
    printf("%.15f\n", result);
    return EXIT_SUCCESS;
}