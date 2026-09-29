#include <stdio.h>
#include <stdlib.h>

long long *memo;

long long f(long long n) {
    if (n == 0) return 0;
    if (n < 12) return n;
    if (memo[n] != -1) return memo[n];
    long long sum = f(n / 2) + f(n / 3) + f(n / 4) + f(n / 5);
    memo[n] = (sum > n) ? sum : n;
    return memo[n];
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:15168,execs:412,op:havoc,rep:2; likely memory-safety defect
  */

int main() {
    long long n;
    printf("Enter n: ");
    if (scanf("%lld", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    if (n < 0) {
        fprintf(stderr, "n must be non-negative\n");
        return 1;
    }
    memo = (long long *)malloc((n + 1) * sizeof(long long));
    if (memo == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    for (long long i = 0; i <= n; i++) {
        memo[i] = -1;
    }
    printf("%lld\n", f(n));
    free(memo);
    return 0;
}