#include <stdio.h>
#include <stdlib.h>

long long *memo;
long long memo_size;

long long max(long long a, long long b) {
    return a > b ? a : b;
}

long long f(long long n) {
    if (n == 0) return 0;
    if (n < 12) return n;
    
    if (memo[n] != -1) return memo[n];
    
    long long result = max(n, f(n/2) + f(n/3) + f(n/4) + f(n/5));
    memo[n] = result;
    return result;
}

int main() {
    long long n;
    
    printf("Enter a number: ");
    if (scanf("%lld", &n) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    
    if (n < 0) {
        printf("Please enter a non-negative number\n");
        return 1;
    }
    
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 9223372036854775807 + 1 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000000,time:9224,execs:982,op:havoc,rep:8)
     */
    memo_size = n + 1;
    memo = (long long*)malloc(memo_size * sizeof(long long));
    if (memo == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    
    for (long long i = 0; i < memo_size; i++) {
        memo[i] = -1;
    }
    
    if (n >= memo_size) {
        free(memo);
        printf("Input too large\n");
        return 1;
    }
    
    long long result = f(n);
    printf("Maximum sum: %lld\n", result);
    
    free(memo);
    return 0;
}