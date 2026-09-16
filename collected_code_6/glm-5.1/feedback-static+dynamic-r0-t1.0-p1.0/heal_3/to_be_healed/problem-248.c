#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 2.5928571428571425, got <no output>
  *  test case 2 failed: expected 3.547739657143682, got <no output>
  *  test case 1 failed: expected 2.083333333333333, got <no output>
  */

double harmonic_sum(unsigned int n) {
    double sum = 0.0;
    for (unsigned int i = 1; i <= n; i++) {
        sum += 1.0 / i;
    }
    return sum;
}

int main(int argc, char * const * const argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    unsigned long val = strtoul(argv[1], &endptr, 10);

    if (*endptr != '\0' || val == 0) {
        fprintf(stderr, "Error: n must be a positive integer.\n");
        return EXIT_FAILURE;
    }

    double result = harmonic_sum((unsigned int)val);
    printf("%.15f\n", result);

    return EXIT_SUCCESS;
}