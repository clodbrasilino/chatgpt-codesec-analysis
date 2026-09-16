#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 2.5928571428571425, got <no output>
  *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  *  test case 2 failed: expected 3.547739657143682, got <no output>
  *  test case 1 failed: expected 2.083333333333333, got <no output>
  */

double harmonic_sum(int n) {
    if (n <= 1) {
        return 0.0;
    }

    double sum = 0.0;
    for (int i = 1; i < n; i++) {
        sum += 1.0 / i;
    }
    return sum;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    long val = strtol(argv[1], &endptr, 10);

    /* Possible weaknesses found:
     *  each undeclared identifier is reported only once for each function it appears in
     *  'INT_MAX' undeclared (first use in this function)
     *  use of undeclared identifier 'INT_MAX'
     */
    if (endptr == argv[1] || *endptr != '\0' || val < 1 || val > INT_MAX) {
        fprintf(stderr, "Error: n must be a valid integer >= 1\n");
        return EXIT_FAILURE;
    }

    double result = harmonic_sum((int)val);
    printf("%.15f\n", result);
    return EXIT_SUCCESS;
}