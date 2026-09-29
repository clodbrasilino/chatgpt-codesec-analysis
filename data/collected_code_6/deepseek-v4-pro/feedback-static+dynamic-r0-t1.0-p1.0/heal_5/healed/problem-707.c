#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>
#include <string.h>

int64_t countSetBits(int n) {
    int64_t count = 0;
    int totalBits = sizeof(int) * CHAR_BIT;
    int64_t power = 1;
    int64_t num = (int64_t)n + 1;
    
    for (int i = 0; i < totalBits; i++) {
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
    }
    
    return count;
}

int main(void) {
    char buffer[128] = {0};
    int n;
    
    printf("Enter a number: ");
    if (fgets(buffer, (int)sizeof(buffer) - 1, stdin) == NULL) {
        printf("Invalid input\n");
        return 1;
    }
    
    buffer[sizeof(buffer) - 1] = '\0';
    
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
        len--;
    }
    
    if (len == 0) {
        printf("Invalid input\n");
        return 1;
    }
    
    char *endptr = NULL;
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