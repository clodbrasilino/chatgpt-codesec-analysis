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
    char input[32];
    
    printf("Enter a number: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    
    if (sscanf(input, "%" SCNu64, &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    int result = countSetBits(n);
    printf("Total set bits from 1 to %" PRIu64 ": %d\n", n, result);
    
    return 0;
}