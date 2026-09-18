#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

/* Possible weaknesses found:
 * ASan: stack-overflow (AFL crash: id:000001,sig:11,src:000000,time:6715,execs:2535,op:havoc,rep:11)
 */
long f(long n, long *memo) {
    if (n < 0) return 0;
    if (memo[n] != -1) return memo[n];
    long result = max(n, f(n/2, memo) + f(n/3, memo) + f(n/4, memo) + f(n/5, memo));
    memo[n] = result;
    return result;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:11,src:000000,time:11,execs:14,op:havoc,rep:15; likely memory-safety defect
  */

int main() {
    long n;
    printf("Enter a number: ");
    if (scanf("%ld", &n) != 1 || n < 0 || n > LONG_MAX) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    if (n > 1000000) {
        fprintf(stderr, "Input too large\n");
        return 1;
    }

    long *memo = (long *)calloc(n + 1, sizeof(long));
    if (memo == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    for (long i = 0; i <= n; ++i) {
        memo[i] = -1;
    }

    long result = f(n, memo);
    printf("Maximum sum: %ld\n", result);

    free(memo);
    return 0;
}