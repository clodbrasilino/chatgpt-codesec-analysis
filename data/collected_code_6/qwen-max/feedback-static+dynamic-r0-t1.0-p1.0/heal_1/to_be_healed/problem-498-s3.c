#include <stdio.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 1, got <no output>
  *  test case 1 failed: expected 2, got <no output>
  *  test case 2 failed: expected 1, got <no output>
  */

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main() {
    int num1, num2;
    printf("Enter two positive integers: ");
    scanf("%d %d", &num1, &num2);
    if (num1 > 0 && num2 > 0) {
        printf("GCD of %d and %d is %d\n", num1, num2, gcd(num1, num2));
    } else {
        printf("Please enter positive integers.\n");
    }
    return 0;
}