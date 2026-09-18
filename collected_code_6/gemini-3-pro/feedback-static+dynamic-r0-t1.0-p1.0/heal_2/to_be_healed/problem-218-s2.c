#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 3, got 2
  *  test case 1 failed: expected 4, got 3
  *  test case 0 failed: expected 1, got 2
  */

int min_operations(int a, int b) {
    int xor_val = a ^ b;
    int count = 0;
    while (xor_val > 0) {
        count += xor_val & 1;
        xor_val >>= 1;
    }
    return count;
}

int main(void) {
    int a = 2;
    int b = 6;
    
    int result = min_operations(a, b);
    
    printf("%d\n", result);
    
    return EXIT_SUCCESS;
}