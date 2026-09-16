#include <stdio.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 15, got <no output>
  *  test case 0 failed: expected 23, got <no output>
  *  test case 1 failed: expected 15, got <no output>
  */

int setRightmostUnsetBit(int n) {
    return n | (~n & (n + 1));
}

int main(void) {
    printf("%d\n", setRightmostUnsetBit(5));
    printf("%d\n", setRightmostUnsetBit(13));
    printf("%d\n", setRightmostUnsetBit(14));
    return 0;
}