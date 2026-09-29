#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 4, got 3
  *  test case 2 failed: expected 3, got 2
  *  test case 0 failed: expected 1, got 3
  */

int min_operations(int a, int b) {
    if (a == b) {
        return 0;
    }
    
    int diff = abs(a - b);
    int step = 0;
    int sum = 0;
    
    while (sum < diff || (sum - diff) % 2 != 0) {
        step++;
        if (INT_MAX - sum < step) {
            return -1; 
        }
        sum += step;
    }
    
    return step;
}

int main(void) {
    int a = 2;
    int b = 6;
    
    int result = min_operations(a, b);
    
    if (result != -1) {
        printf("%d\n", result);
    } else {
        printf("Integer overflow occurred.\n");
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}