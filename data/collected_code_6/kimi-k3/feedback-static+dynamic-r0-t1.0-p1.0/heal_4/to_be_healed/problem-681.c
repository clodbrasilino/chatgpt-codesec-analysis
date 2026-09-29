#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 31, got <no output>
  *  test case 1 failed: expected 5, got <no output>
  *  test case 0 failed: expected 2, got <no output>
  */

int smallest_prime_divisor(int n) {
    if (n < 2) {
        return -1;
    }
    if (n % 2 == 0) {
        return 2;
    }
    for (int i = 3; i <= n / i; i += 2) {
        if (n % i == 0) {
            return i;
        }
    }
    return n;
}

int main(void) {
    int num;
    if (scanf("%d", &num) != 1) {
        return EXIT_FAILURE;
    }
    int result = smallest_prime_divisor(num);
    printf("%d\n", result);
    return EXIT_SUCCESS;
}