#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 33, got <no output>
  *  test case 1 failed: expected 2, got <no output>
  *  test case 2 failed: expected 28, got <no output>
  */

int64_t countSetBits(int n) {
    int64_t count = 0;
    int i = 0;
    int totalBits = sizeof(int) * CHAR_BIT;
    int64_t power = 1;
    int64_t num = (int64_t)n + 1;
    
    while (i < totalBits) {
        if (power > num) {
            break;
        }
        
        int64_t totalPairs = num / (power * 2);
        int64_t remainder = num % (power * 2);
        
        count += totalPairs * power;
        if (remainder > power) {
            count += remainder - power;
        }
        
        power <<= 1;
        i++;
    }
    
    return count;
}

int main(void) {
    int n;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[128];
    
    printf("Enter a number: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        printf("Invalid input\n");
        return 1;
    }
    
    size_t len = 0;
    while (buffer[len] != '\0') {
        if (buffer[len] == '\n') {
            buffer[len] = '\0';
            break;
        }
        len++;
        if (len >= sizeof(buffer)) {
            printf("Input too long\n");
            return 1;
        }
    }
    
    char *endptr;
    long val = strtol(buffer, &endptr, 10);
    
    if (endptr == buffer || *endptr != '\0') {
        printf("Invalid input\n");
        return 1;
    }
    
    if (val < 0 || val > INT_MAX) {
        printf("Please enter a non-negative number within range\n");
        return 1;
    }
    
    n = (int)val;
    printf("Total set bits from 1 to %d: %lld\n", n, (long long)countSetBits(n));
    
    return 0;
}