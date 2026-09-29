#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 3.547739657143682, got <no output>
  *  test case 1 failed: expected 2.083333333333333, got <no output>
  *  test case 0 failed: expected 2.5928571428571425, got <no output>
  */

double harmonic_sum(int n)
{
    double sum = 0.0;
    int i;

    if (n < 1) {
        return 0.0;
    }

    for (i = 1; i < n; i++) {
        sum += 1.0 / (double)i;
    }

    return sum;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    int n;
    double result;
    char *endptr;
    long val;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    val = strtol(argv[1], &endptr, 10);

    if (errno != 0 || *endptr != '\0' || endptr == argv[1]) {
        fprintf(stderr, "Invalid input: not a valid integer\n");
        return EXIT_FAILURE;
    }

    if (val < 1 || val > 2147483647L) {
        fprintf(stderr, "Invalid input: n must be >= 1\n");
        return EXIT_FAILURE;
    }

    n = (int)val;
    result = harmonic_sum(n);

    if (isnan(result) || isinf(result)) {
        fprintf(stderr, "Computation error\n");
        return EXIT_FAILURE;
    }

    printf("Harmonic sum of %d is: %.15f\n", n - 1, result);

    return EXIT_SUCCESS;
}