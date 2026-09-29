#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 33, got <no output>
  *  test case 1 failed: expected 2, got <no output>
  *  test case 2 failed: expected 28, got <no output>
  */

int countSetBits(uint64_t n) {
    if (n == 0) return 0;
    
    uint64_t x = n;
    int highestBit = 0;
    while (x >>= 1) highestBit++;
    
    uint64_t power = 1ULL << highestBit;
    uint64_t remainder = n - power;
    
    int count = (int)(highestBit * (power >> 1)) + (int)remainder + 1;
    if (remainder > 0) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: -2110091719 + -571574823 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000001,time:4756,execs:1544,op:havoc,rep:11)
         */
        count += countSetBits(remainder);
    }
    
    return count;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000000,time:172,execs:73,op:havoc,rep:5; likely memory-safety defect
  */

int main(void) {
    uint64_t n;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[64];
    
    printf("Enter a number: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    /* Possible weaknesses found:
     * Flawfinder sscanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (sscanf(buffer, "%" SCNu64, &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    int result = countSetBits(n);
    printf("Total set bits from 1 to %" PRIu64 ": %d\n", n, result);
    
    return 0;
}