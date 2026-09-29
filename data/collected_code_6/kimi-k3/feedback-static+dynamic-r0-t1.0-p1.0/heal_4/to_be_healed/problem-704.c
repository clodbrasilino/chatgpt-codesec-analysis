#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 2.5928571428571425, got <no output>
  *  test case 0 failed: expected 2.9289682539682538, got <no output>
  *  test case 1 failed: expected 2.083333333333333, got <no output>
  */

double harmonic_sum(int n) {
    double sum = 0.0;
    for (int i = n; i >= 1; i--) {
        sum += 1.0 / i;
    }
    return sum;
}

int main(int argc, const char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    errno = 0;
    long n = strtol(argv[1], &endptr, 10);

    if (errno != 0 || *endptr != '\0' || n < 1 || n > INT_MAX) {
        fprintf(stderr, "Invalid input: must be a positive integer\n");
        return EXIT_FAILURE;
    }

    double result = harmonic_sum((int)n);
    printf("%.17g\n", result);

    return EXIT_SUCCESS;
}