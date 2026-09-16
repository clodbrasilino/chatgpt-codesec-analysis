#include <stdio.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 14, got <no output>
  *  test case 2 failed: expected 15, got <no output>
  *  test case 1 failed: expected 14, got <no output>
  */

unsigned int setLeftMostUnsetBit(unsigned int n) {
    unsigned int bit = 1;
    while (bit && (n & bit)) {
        bit <<= 1;
    }
    if (bit == 0) {
        return n;
    }
    n |= bit;
    return n;
}

int main() {
    unsigned int num = 0b101010;
    printf("Original number: %u (in binary: %08b)\n", num, num);
    num = setLeftMostUnsetBit(num);
    printf("After setting left most unset bit: %u (in binary: %08b)\n", num, num);
    return 0;
}