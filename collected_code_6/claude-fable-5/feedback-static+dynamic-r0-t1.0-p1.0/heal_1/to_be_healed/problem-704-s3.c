#include <stdio.h>
#include <stdlib.h>

double harmonic_sum(unsigned int n);
 /* Possible weaknesses found:
  *  test case 1 failed: expected 2.083333333333333, got 1.8333333730697632
  *  test case 2 failed: expected 2.5928571428571425, got 2.4500000476837158
  *  test case 0 failed: expected 2.9289682539682538, got 2.8289682865142822
  */

double harmonic_sum(unsigned int n)
{
    double sum = 0.0;
    unsigned int i;

    if (n <= 1U) {
        return 0.0;
    }

    for (i = 1U; i <= n - 1U; i++) {
        sum += 1.0 / (double)i;
    }

    return sum;
}

int main(void)
{
    unsigned int n = 0U;
    double result;
    int scan_status;

    printf("Enter a positive integer n: ");
    scan_status = scanf("%u", &n);

    if (scan_status != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (n == 0U) {
        fprintf(stderr, "Error: n must be greater than zero.\n");
        return EXIT_FAILURE;
    }

    result = harmonic_sum(n);
    printf("Harmonic sum of %u is %f\n", n - 1U, result);

    return EXIT_SUCCESS;
}