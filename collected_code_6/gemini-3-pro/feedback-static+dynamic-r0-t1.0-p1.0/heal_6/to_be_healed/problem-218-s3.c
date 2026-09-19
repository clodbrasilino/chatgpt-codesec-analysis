#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 3, got <no output>
  *  test case 1 failed: expected 4, got <no output>
  *  test case 0 failed: expected 1, got <no output>
  */

int min_operations(int num1, int num2) {
    unsigned int diff = (num1 > num2) ? ((unsigned int)num1 - (unsigned int)num2) : ((unsigned int)num2 - (unsigned int)num1);
    unsigned int ops = 0;
    
    ops += diff / 10;
    diff %= 10;
    
    ops += diff / 5;
    diff %= 5;
    
    ops += diff / 2;
    diff %= 2;
    
    ops += diff;
    
    return (int)ops;
}

int main(void) {
    int t;
    
    if (scanf("%d", &t) == 1) {
        while (t--) {
            int num1, num2;
            if (scanf("%d %d", &num1, &num2) == 2) {
                printf("%d\n", min_operations(num1, num2));
            }
        }
    }
    
    return 0;
}