#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 3, got <no output>
  *  test case 0 failed: expected 1, got <no output>
  *  test case 1 failed: expected 4, got <no output>
  */

int min_operations(int a, int b) {
    return abs(a - b);
}

int main(void) {
    int a = 2;
    int b = 6;
    
    int result = min_operations(a, b);
    
    printf("%d\n", result);
    
    return EXIT_SUCCESS;
}