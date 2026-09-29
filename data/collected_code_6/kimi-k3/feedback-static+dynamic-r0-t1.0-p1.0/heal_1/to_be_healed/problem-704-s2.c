#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 2.083333333333333, got 1.8333333730697632
  *  test case 2 failed: expected 2.5928571428571425, got 2.4500000476837158
  *  test case 0 failed: expected 2.9289682539682538, got 2.8289682865142822
  */

double harmonic_sum(int n)
{
    double sum = 0.0;
    int i;

    if (n <= 0) {
        return 0.0;
    }

    for (i = 1; i < n; i++) {
        sum += 1.0 / i;
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

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
     */
    n = atoi(argv[1]);

    if (n <= 0) {
        fprintf(stderr, "Error: n must be a positive integer.\n");
        return EXIT_FAILURE;
    }

    result = harmonic_sum(n);
    printf("Harmonic sum of %d is: %f\n", n - 1, result);

    return EXIT_SUCCESS;
}