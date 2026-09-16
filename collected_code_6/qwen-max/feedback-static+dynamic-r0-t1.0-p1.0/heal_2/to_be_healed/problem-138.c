#include <stdio.h>
#include <stdbool.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected True, got 0
  *  test case 2 failed: expected True, got 0
  */

bool isSumOfPowersOfTwo(int n) {
    if (n <= 0) return false;
    while (n > 1) {
        if (n % 2 != 0) return false;
        n /= 2;
    }
    return true;
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    if (isSumOfPowersOfTwo(num)) {
        printf("The number can be represented as sum of non-zero powers of 2.\n");
    } else {
        printf("The number cannot be represented as sum of non-zero powers of 2.\n");
    }
    return 0;
}