#include <stdio.h>
#include <stdbool.h>
#include <math.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected False, got <no output>
  *  test case 1 failed: expected True, got <no output>
  *  test case 0 failed: expected False, got <no output>
  */

bool isPerfectSquare(int num) {
    if (num < 0) {
        return false;
    }
    
    int root = (int)sqrt((double)num);
    return (root * root == num);
}

int main(void) {
    int testValues[] = {0, 1, 4, 9, 16, 25, 36, 49, 64, 81, 100, 2, 3, 5, 7, 10, -4, -16, 2147483647};
    int numTests = sizeof(testValues) / sizeof(testValues[0]);
    
    for (int i = 0; i < numTests; i++) {
        int value = testValues[i];
        bool result = isPerfectSquare(value);
        printf("%d is %sa perfect square\n", value, result ? "" : "not ");
    }
    
    return 0;
}