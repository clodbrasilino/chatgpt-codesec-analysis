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
        uint64_t pairBits = totalPairs * power;
        
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 2138888408 + 194443264 cannot be represented in type 'int' (AFL crash: id:000002,sig:06,src:000011,time:42777,execs:25170,op:havoc,rep:4)
         * UBSan: signed integer overflow: 1777777773 + 444444432 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000004,time:1140,execs:985,op:havoc,rep:1)
         * UBSan: signed integer overflow: 1777777793 + 444444448 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000004,time:1657,execs:1404,op:havoc,rep:2)
         */
        count += (int)pairBits;
        if (remainder > power) {
            uint64_t extraBits = remainder - power;
            count += (int)extraBits;
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
    
    if (val > INT_MAX) {
        printf("Number too large\n");
        return 1;
    }
    
    n = (int)val;
    printf("Total set bits from 1 to %d: %d\n", n, countSetBits(n));
    
    return 0;
}