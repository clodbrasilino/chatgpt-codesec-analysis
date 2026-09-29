#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int countSetBits(int n) {
    int count = 0;
    int i = 0;
    int totalBits = sizeof(int) * CHAR_BIT;
    long long power = 1;
    
    while (i < totalBits) {
        if (power > (long long)n + 1) {
            break;
        }
        
        long long totalPairs = ((long long)n + 1) / (power * 2);
        long long remainder = ((long long)n + 1) % (power * 2);
        
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 1569325056 + 784662528 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000004,time:10223,execs:3516,op:havoc,rep:2)
         * UBSan: signed integer overflow: 1724130190 + 862065092 cannot be represented in type 'int' (AFL crash: id:000002,sig:06,src:000012,time:30544,execs:10122,op:havoc,rep:2)
         * UBSan: signed integer overflow: 1848304526 + 924152260 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000002,time:652,execs:284,op:havoc,rep:1)
         */
        count += (int)(totalPairs * power);
        if (remainder > power) {
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: 1634608287 + 774562703 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000002,time:652,execs:284,op:havoc,rep:1)
             * UBSan: signed integer overflow: 1733361671 + 495583233 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000004,time:10223,execs:3516,op:havoc,rep:2)
             */
            count += (int)(remainder - power);
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
    char buffer[32];
    
    printf("Enter a number: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        printf("Invalid input\n");
        return 1;
    }
    
    char *endptr;
    long val = strtol(buffer, &endptr, 10);
    
    if (endptr == buffer || *endptr != '\n' && *endptr != '\0') {
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