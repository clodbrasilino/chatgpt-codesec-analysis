#include <stdio.h>
#include <math.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 1.9921875, got <no output>
  *  test case 1 failed: expected 1.9375, got <no output>
  *  test case 2 failed: expected 1.99609375, got <no output>
  */

double geometric_sum(int n) {
    if (n < 0) return 0;
    if (n == 0) return 1;
    return 1 / pow(2, n) + geometric_sum(n - 1);
}

int main() {
    int n = 5;
    printf("Geometric sum: %f\n", geometric_sum(n));
    return 0;
}