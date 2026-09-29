#include <stdio.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 15, got 31
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