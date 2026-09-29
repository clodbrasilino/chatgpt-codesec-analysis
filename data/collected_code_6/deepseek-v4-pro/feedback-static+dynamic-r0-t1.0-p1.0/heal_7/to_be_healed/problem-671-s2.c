#include <stdio.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 15, got <no output>
  *  test case 0 failed: expected 23, got <no output>
  *  test case 1 failed: expected 15, got <no output>
  */

int setRightmostUnsetBit(int n) {
    return n | (n + 1);
}

int main(void) {
    int num = 5;
    int result = setRightmostUnsetBit(num);
    printf("%d\n", result);
    return 0;
}