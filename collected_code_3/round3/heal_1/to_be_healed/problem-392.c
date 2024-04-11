#include <stdio.h>
#include <stdlib.h>

#define MAX 1000000

long long int dp[MAX];

long long int max_sum(long long int n) {
    if (n < MAX) {
        return dp[n];
    }
    else {
        /* Possible weaknesses found:
         *  implicit declaration of function 'max' [-Wimplicit-function-declaration]
         *  previous implicit declaration of 'max' with type 'int()'
         */
        return max(n, max_sum(n/2) + max_sum(n/3) + max_sum(n/4) + max_sum(n/5));
    }
}

/* Possible weaknesses found:
 *  conflicting types for 'max'; have 'long long int(long long int,  long long int)'
 */
long long int max(long long int a, long long int b) {
    return (a > b) ? a : b;
}

int main() {
    long long int n;
    for (n = 0; n < MAX; n++) {
        if (n <= 11) {
            dp[n] = n;
        }
        else {
            dp[n] = max(n, dp[n/2] + dp[n/3] + dp[n/4] + dp[n/5]);
        }
    }
    printf("Enter a number: ");
    scanf("%lld", &n);
    printf("Maximum sum possible: %lld\n", max_sum(n));
    return 0;
}