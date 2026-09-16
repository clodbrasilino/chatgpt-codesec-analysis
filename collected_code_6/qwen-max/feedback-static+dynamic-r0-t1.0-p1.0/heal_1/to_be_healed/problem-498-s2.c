#include <stdio.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 1, got <no output>
  *  test case 1 failed: expected 2, got <no output>
  *  test case 2 failed: expected 1, got <no output>
  */

int gcd(int a, int b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

int main() {
    int num1 = 56;
    int num2 = 98;
    printf("GCD of %d and %d is %d\n", num1, num2, gcd(num1, num2));
    return 0;
}