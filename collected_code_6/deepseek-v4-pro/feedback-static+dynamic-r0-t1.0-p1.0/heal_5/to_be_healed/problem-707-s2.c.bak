#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 2, got <no output>
  *  test case 0 failed: expected 33, got <no output>
  *  test case 2 failed: expected 28, got <no output>
  */

int countSetBits(uint64_t n) {
    if (n == 0) return 0;
    
    uint64_t x = n;
    int highestBit = 0;
    while (x >>= 1) highestBit++;
    
    uint64_t power = 1ULL << highestBit;
    uint64_t highestPower = power;
    uint64_t remainder = n - highestPower;
    
    int count = (highestBit * (highestPower >> 1)) + (int)remainder + 1 + countSetBits(remainder);
    
    return count;
}

int main(void) {
    uint64_t n;
    
    printf("Enter a number: ");
    if (scanf("%" SCNu64, &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    int result = countSetBits(n);
    printf("Total set bits from 1 to %" PRIu64 ": %d\n", n, result);
    
    return 0;
}