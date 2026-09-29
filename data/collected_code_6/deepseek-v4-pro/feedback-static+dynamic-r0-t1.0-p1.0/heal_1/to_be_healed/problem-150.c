#include <stdio.h>
#include <stdbool.h>

bool is_present_in_sequence(long long n, long long target) {
    long long low = 1;
    long long high = n > target ? n : target;
    if (high < 1) high = 1;
    
    while (low <= high) {
        long long mid = low + (high - low) / 2;
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 388888888889 * 388888888890 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:598,execs:334,op:havoc,rep:3)
         */
        long long sum = (mid * (mid + 1)) / 2;
        
        if (sum == target) {
            return true;
        } else if (sum < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    
    return false;
}

int main(void) {
    long long n, target;
    
    printf("Enter the sequence limit (n): ");
    if (scanf("%lld", &n) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    
    printf("Enter the number to search: ");
    if (scanf("%lld", &target) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    
    if (n < 1) {
        printf("Sequence limit must be positive\n");
        return 1;
    }
    
    if (is_present_in_sequence(n, target)) {
        printf("%lld is present in the sequence\n", target);
    } else {
        printf("%lld is not present in the sequence\n", target);
    }
    
    return 0;
}