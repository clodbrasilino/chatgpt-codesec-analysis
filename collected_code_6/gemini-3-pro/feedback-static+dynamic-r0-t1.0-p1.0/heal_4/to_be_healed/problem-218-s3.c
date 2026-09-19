#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 3, got <no output>
  *  test case 1 failed: expected 4, got <no output>
  *  test case 0 failed: expected 1, got <no output>
  */

int min_operations(int num1, int num2) {
    int diff = abs(num1 - num2);
    int ops = 0;
    
    if (diff == 0) return 0;
    
    ops += diff / 10;
    diff %= 10;
    
    ops += diff / 5;
    diff %= 5;
    
    ops += diff / 2;
    diff %= 2;
    
    ops += diff;
    
    return ops;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000004,time:38677,execs:15803,op:havoc,rep:4; likely memory-safety defect
  */

int main(void) {
    int num1, num2;
    
    if (scanf("%d %d", &num1, &num2) == 2) {
        printf("%d\n", min_operations(num1, num2));
    }
    
    return 0;
}