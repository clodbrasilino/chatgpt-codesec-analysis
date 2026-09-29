#include <stdio.h>
#include <stdbool.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected True, got <no output>
  *  test case 1 failed: expected False, got <no output>
  *  test case 0 failed: expected True, got <no output>
  */

bool isSumOfPowersOfTwo(int n) {
    if (n == 0) return false;
    while (n > 1) {
        if (n % 2 == 1) n -= 1;
        n /= 2;
    }
    return n == 1;
}

int main() {
    int number = 10;
    if (isSumOfPowersOfTwo(number)) {
        printf("%d can be represented as the sum of non-zero powers of 2.\n", number);
    } else {
        printf("%d cannot be represented as the sum of non-zero powers of 2.\n", number);
    }
    return 0;
}