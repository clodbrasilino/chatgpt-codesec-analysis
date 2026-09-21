#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

int countSetBits(uint64_t n) {
    if (n == 0) return 0;
    
    uint64_t x = n;
    int highestBit = 0;
    while (x >>= 1) highestBit++;
    
    uint64_t power = 1ULL << highestBit;
    uint64_t remainder = n - power;
    
    int count = (highestBit * (int)(power >> 1)) + (int)remainder + 1 + countSetBits(remainder);
    
    return count;
}

int main(void) {
    uint64_t n;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[64];
    
    printf("Enter a number: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    
    /* Possible weaknesses found:
     * Flawfinder sscanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (sscanf(input, "%63" SCNu64, &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    int result = countSetBits(n);
    printf("Total set bits from 1 to %" PRIu64 ": %d\n", n, result);
    
    return 0;
}