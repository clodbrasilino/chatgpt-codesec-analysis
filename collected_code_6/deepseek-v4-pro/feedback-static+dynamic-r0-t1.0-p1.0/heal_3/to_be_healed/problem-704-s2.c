#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 2.083333333333333, got <no output>
  *  test case 0 failed: expected 2.9289682539682538, got <no output>
  *  test case 2 failed: expected 2.5928571428571425, got <no output>
  */

double harmonic_sum(int n) {
    if (n <= 0) {
        return 0.0;
    }
    
    double sum = 0.0;
    for (int i = 1; i <= n; i++) {
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
    
    if (endptr == argv[1] || *endptr != '\0' || val <= 0 || val > 1000000000) {
        fprintf(stderr, "Error: n must be a positive integer\n");
        return EXIT_FAILURE;
    }
    
    int n = (int)val;
    double result = harmonic_sum(n);
    printf("%.10f\n", result);
    
    return EXIT_SUCCESS;
}