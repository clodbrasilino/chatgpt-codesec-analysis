#include <stdio.h>
#include <stdlib.h>
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
    for (int i = 1; i < n; i++) {
        sum += 1.0 / (double)i;
    }
    
    return sum;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    int n;

    if (argc != 2) {
        return EXIT_FAILURE;
    }

    long val = strtol(argv[1], NULL, 10);
    if (val < 0 || val > 2147483647) {
        return EXIT_FAILURE;
    }
    
    n = (int)val;

    double result = harmonic_sum(n);
    printf("%.15f\n", result);

    return EXIT_SUCCESS;
}