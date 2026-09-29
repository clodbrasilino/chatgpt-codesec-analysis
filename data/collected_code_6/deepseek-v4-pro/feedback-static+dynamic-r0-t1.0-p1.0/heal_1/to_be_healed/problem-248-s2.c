#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 2.5928571428571425, got 2.4500000476837158
  *  test case 1 failed: expected 2.083333333333333, got 1.8333333730697632
  *  test case 2 failed: expected 3.547739657143682, got 3.4951081275939941
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
    double result;
    
    printf("Enter a positive integer: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    result = harmonic_sum(n);
    printf("Harmonic sum H(%d-1) = %.6f\n", n, result);
    
    return EXIT_SUCCESS;
}