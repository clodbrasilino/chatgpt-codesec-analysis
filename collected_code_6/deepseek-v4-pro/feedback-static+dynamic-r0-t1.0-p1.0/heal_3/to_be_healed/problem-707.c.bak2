#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>

int countSetBits(int n) {
    int count = 0;
    int i = 0;
    int totalBits = sizeof(int) * CHAR_BIT;
    uint64_t power = 1;
    uint64_t limit = (uint64_t)n + 1;
    
    while (i < totalBits) {
        if (power > limit) {
            break;
        }
        
        uint64_t totalPairs = limit / (power * 2);
        uint64_t remainder = limit % (power * 2);
        
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: -1674115755 + -837057880 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000002,time:347,execs:206,op:havoc,rep:2)
         * UBSan: signed integer overflow: 1842981532 + 307163584 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000002,time:374,execs:219,op:havoc,rep:1)
         */
        count += (int)(totalPairs * power);
        if (remainder > power) {
            count += (int)(remainder - power);
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
    printf("Total set bits from 1 to %d: %d\n", n, countSetBits(n));
    
    return 0;
}