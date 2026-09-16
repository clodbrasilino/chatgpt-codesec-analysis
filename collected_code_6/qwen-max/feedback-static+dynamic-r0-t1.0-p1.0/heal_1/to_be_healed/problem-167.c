#include <stdio.h>
#include <stdint.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 8, got <no output>
  *  test case 2 failed: expected 32, got <no output>
  *  test case 0 failed: expected 1, got <no output>
  */

uint32_t next_power_of_2(uint32_t n) {
    n--;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    n++;
    return n;
}

int main() {
    uint32_t n = 10;
    uint32_t result = next_power_of_2(n);
    printf("The smallest power of 2 greater than or equal to %u is %u\n", n, result);
    return 0;
}