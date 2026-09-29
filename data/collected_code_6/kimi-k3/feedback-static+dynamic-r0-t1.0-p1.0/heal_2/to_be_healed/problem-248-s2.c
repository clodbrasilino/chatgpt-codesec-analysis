#include <stdio.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 3.547739657143682, got <no output>
  *  test case 1 failed: expected 2.083333333333333, got <no output>
  *  test case 0 failed: expected 2.5928571428571425, got <no output>
  */

double harmonic_sum(int n) {
    double sum = 0.0;
    int i;
    
    if (n < 1) {
        return 0.0;
    }
    
    for (i = 1; i <= n; i++) {
        sum += 1.0 / i;
    }
    
    return sum;
}

int main(void) {
    int n;
    double result;
    
    if (scanf("%d", &n) != 1) {
        return 1;
    }
    
    if (n < 1) {
        return 1;
    }
    
    result = harmonic_sum(n);
    printf("%.15f\n", result);
    
    return 0;
}