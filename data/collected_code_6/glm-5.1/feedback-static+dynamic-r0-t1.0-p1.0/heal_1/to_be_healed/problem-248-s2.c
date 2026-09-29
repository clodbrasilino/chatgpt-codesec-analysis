#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 2.5928571428571425, got <no output>
  *  test case 2 failed: expected 3.547739657143682, got <no output>
  *  test case 1 failed: expected 2.083333333333333, got <no output>
  */

double harmonic_sum(int n) {
    if (n <= 1) {
        return 0.0;
    }
    double sum = 0.0;
    for (int i = 2; i <= n; i++) {
        sum += 1.0 / i;
    }
    return sum;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    int n;
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    if (sscanf(argv[1], "%d", &n) != 1) {
        return EXIT_FAILURE;
    }
    if (n < 1) {
        return EXIT_FAILURE;
    }
    double result = harmonic_sum(n);
    printf("%.15f\n", result);
    return EXIT_SUCCESS;
}