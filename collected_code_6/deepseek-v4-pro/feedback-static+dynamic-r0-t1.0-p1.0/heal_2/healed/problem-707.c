#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>

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
    char buffer[32];
    
    printf("Enter a number: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        printf("Invalid input\n");
        return 1;
    }
    
    char *endptr;
    long val = strtol(buffer, &endptr, 10);
    
    if (endptr == buffer || (*endptr != '\n' && *endptr != '\0')) {
        printf("Invalid input\n");
        return 1;
    }
    
    if (val < 0) {
        printf("Please enter a non-negative number\n");
        return 1;
    }
    
    n = (int)val;
    printf("Total set bits from 1 to %d: %lld\n", n, countSetBits(n));
    
    return 0;
}