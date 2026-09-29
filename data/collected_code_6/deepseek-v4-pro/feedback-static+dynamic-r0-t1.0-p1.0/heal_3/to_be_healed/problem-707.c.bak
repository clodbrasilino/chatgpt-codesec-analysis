#include <stdio.h>
#include <stdint.h>

int countSetBits(int n) {
    int count = 0;
    int i = 0;
    int totalBits = sizeof(int) * 8;
    uint64_t power = 1;
    uint64_t un = (uint64_t)n;
    
    while (i < totalBits && power <= un) {
        uint64_t totalPairs = (un + 1ULL) / (power * 2);
        uint64_t remainder = (un + 1ULL) % (power * 2);
        
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 2110787477 + 110624768 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000002,time:972,execs:578,op:havoc,rep:15)
         * UBSan: signed integer overflow: 2126546688 + 354424448 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000002,time:2074,execs:1153,op:havoc,rep:15)
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
    
    printf("Enter a number: ");
    if (scanf("%d", &n) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    
    if (n < 0) {
        printf("Please enter a non-negative number\n");
        return 1;
    }
    
    printf("Total set bits from 1 to %d: %d\n", n, countSetBits(n));
    
    return 0;
}