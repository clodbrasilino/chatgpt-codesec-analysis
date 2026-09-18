#include <stdio.h>

int countSetBits(int n) {
    int count = 0;
    int i = 0;
    int totalBits = sizeof(int) * 8;
    long long power = 1;
    
    while (i < totalBits && power <= n) {
        long long totalPairs = (n + 1LL) / (power * 2);
        long long remainder = (n + 1LL) % (power * 2);
        
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 2122222222 + 1061111108 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000002,time:408,execs:275,op:havoc,rep:6)
         * UBSan: signed integer overflow: 1974202368 + 658067456 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000002,time:660,execs:430,op:havoc,rep:11)
         */
        count += (int)(totalPairs * power);
        if (remainder > power) {
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: 1696790717 + 1048480399 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000002,time:408,execs:275,op:havoc,rep:6)
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