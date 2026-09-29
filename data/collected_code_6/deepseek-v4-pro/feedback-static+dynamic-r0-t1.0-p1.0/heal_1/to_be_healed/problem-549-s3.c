#include <stdio.h>

long long sum_of_fifth_power_odd(int n) {
    long long sum = 0;
    int odd_num = 1;
    
    for (int i = 0; i < n; i++) {
        long long odd_squared = (long long)odd_num * odd_num;
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 3037001881 * 3037001881 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000003,time:573,execs:332,op:havoc,rep:1)
         */
        long long odd_fourth = odd_squared * odd_squared;
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 1486232107925761 * 6209 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000003,time:573,execs:332,op:havoc,rep:1)
         * UBSan: signed integer overflow: 9193544662653210225 + 50490757668511951 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000003,time:573,execs:332,op:havoc,rep:1)
         */
        sum += odd_fourth * odd_num;
        odd_num += 2;
    }
    
    return sum;
}

int main(void) {
    int n;
    
    printf("Enter the value of n: ");
    if (scanf("%d", &n) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    
    if (n < 0) {
        printf("n must be non-negative\n");
        return 1;
    }
    
    printf("Sum of fifth powers of first %d odd natural numbers: %lld\n", 
           n, sum_of_fifth_power_odd(n));
    
    return 0;
}