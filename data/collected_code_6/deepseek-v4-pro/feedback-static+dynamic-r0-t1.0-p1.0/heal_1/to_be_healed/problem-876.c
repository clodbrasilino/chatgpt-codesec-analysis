#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
 /* Possible weaknesses found:
  *  test case 0 failed: expected 12, got <no output>
  *  test case 2 failed: expected 6, got <no output>
  *  test case 1 failed: expected 255, got <no output>
  */

unsigned long long lcm(int a, int b) {
    if (a <= 0 || b <= 0) {
        return 0;
    }
    return ((unsigned long long)a / gcd(a, b)) * b;
}

int main(void) {
    int num1, num2;
    unsigned long long result;

    if (scanf("%d %d", &num1, &num2) != 2) {
        return EXIT_FAILURE;
    }

    result = lcm(num1, num2);

    if (result == 0) {
        return EXIT_FAILURE;
    }

    printf("%llu\n", result);

    return EXIT_SUCCESS;
}