#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long f(long n, long *memo) {
    if (n < 2) return n;
    if (memo[n] != -1) return memo[n];
    
    long a = f(n / 2, memo);
    long b = f(n / 3, memo);
    long c = f(n / 4, memo);
    long d = f(n / 5, memo);
    
    long sum = a + b + c + d;
    if (sum > INT_MAX || sum < INT_MIN) sum = n;
    
    memo[n] = (sum > n) ? sum : n;
    return memo[n];
}

int main() {
    int n;
    scanf("%d", &n);
    
    long *memo = (long *)malloc((n + 1) * sizeof(long));
    for (int i = 0; i <= n; i++) {
        memo[i] = -1;
    }
    
    long result = f(n, memo);
    printf("%ld\n", result);
    
    free(memo);
    return 0;
}