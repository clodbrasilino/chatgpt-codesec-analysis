#include <stdio.h>

long long sum_fourth_powers(int n) {
    if (n < 0) {
        return -1;
    }
    
    long long sum = 0;
    
    for (int i = 1; i <= n; i++) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 167366136660029 * 55109 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:411,execs:237,op:havoc,rep:14)
         * UBSan: signed integer overflow: 4398046511104 * 2097152 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:411,execs:237,op:havoc,rep:14)
         */
        long long term = (long long)i * i * i * i;
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 9221330501411758027 + 5384089619838736 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:411,execs:237,op:havoc,rep:14)
         */
        sum += term;
    }
    
    return sum;
}

int main(void) {
    int n;
    
    printf("Enter a natural number n: ");
    
    if (scanf("%d", &n) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    
    if (n < 0) {
        printf("Please enter a non-negative integer\n");
        return 1;
    }
    
    long long result = sum_fourth_powers(n);
    
    printf("Sum of fourth powers from 1 to %d = %lld\n", n, result);
    
    return 0;
}