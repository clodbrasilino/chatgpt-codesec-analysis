#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 3, got <no output>
  *  test case 0 failed: expected 1, got <no output>
  *  test case 1 failed: expected 4, got <no output>
  */

int min_operations(int num1, int num2) {
    int steps = 0;
    while (num2 > num1) {
        if (num2 % 2 != 0) {
            num2++;
        } else {
            num2 /= 2;
        }
        steps++;
    }
    return steps + (num1 - num2);
}

int main(void) {
    int num1, num2;
    
    if (scanf("%d %d", &num1, &num2) != 2) {
        return EXIT_FAILURE;
    }
    
    printf("%d\n", min_operations(num1, num2));
    
    return EXIT_SUCCESS;
}