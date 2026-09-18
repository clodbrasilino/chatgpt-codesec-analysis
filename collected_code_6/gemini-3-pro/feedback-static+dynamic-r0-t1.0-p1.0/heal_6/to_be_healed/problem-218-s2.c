#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 4, got 6
  *  test case 0 failed: expected 1, got 2
  */

int min_operations(int a, int b) {
    return abs(a - b);
}

int main(void) {
    int a, b;
    
    if (scanf("%d %d", &a, &b) == 2) {
        int result = min_operations(a, b);
        printf("%d\n", result);
    }
    
    return EXIT_SUCCESS;
}