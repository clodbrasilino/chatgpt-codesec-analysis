#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 4, got 3
  *  test case 0 failed: expected 1, got 2
  *  test case 2 failed: expected 3, got 2
  */

int min_operations(int a, int b) {
    return __builtin_popcount(a ^ b);
}

int main(void) {
    int a = 2;
    int b = 6;
    
    int result = min_operations(a, b);
    
    printf("%d\n", result);
    
    return EXIT_SUCCESS;
}