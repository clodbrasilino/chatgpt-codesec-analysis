#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 3.547739657143682, got 3.4951080781963135
  *  test case 1 failed: expected 2.083333333333333, got 1.8333333333333333
  *  test case 0 failed: expected 2.5928571428571425, got 2.4499999999999997
  */

double harmonic_sum(int n) {
    if (n < 1) {
        return 0.0;
    }
    
    double sum = 0.0;
    for (int i = 1; i <= n - 1; i++) {
        sum += 1.0 / i;
    }
    return sum;
}

int main(void) {
    int n;
    
    printf("Enter a positive integer n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (n < 1) {
        fprintf(stderr, "n must be positive\n");
        return EXIT_FAILURE;
    }
    
    double result = harmonic_sum(n);
    printf("Harmonic sum of %d-1 terms: %.10f\n", n, result);
    
    return EXIT_SUCCESS;
}