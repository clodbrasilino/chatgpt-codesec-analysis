#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 3, got <no output>
  *  test case 0 failed: expected 924, got <no output>
  *  test case 1 failed: expected 2, got <no output>
  */

long long rencontres_number(int n) {
    if (n < 0) {
        return -1;
    }
    if (n == 0) {
        return 1;
    }
    if (n == 1) {
        return 0;
    }

    long long *dp = (long long *)malloc((n + 1) * sizeof(long long));
    if (dp == NULL) {
        return -1;
    }

    dp[0] = 1;
    dp[1] = 0;

    for (int i = 2; i <= n; i++) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: -5784077728986054255 + -5188895624805881368 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000000,time:19,execs:26,op:havoc,rep:3)
         * UBSan: signed integer overflow: 20 * 939765362752547227 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000000,time:19,execs:26,op:havoc,rep:3)
         */
        dp[i] = (i - 1) * (dp[i - 1] + dp[i - 2]);
    }

    long long result = dp[n];
    free(dp);
    return result;
}

int main(void) {
    int n;
    printf("Enter n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    long long result = rencontres_number(n);
    if (result < 0) {
        fprintf(stderr, "Error computing rencontres number\n");
        return 1;
    }

    printf("D_%d = %lld\n", n, result);
    return 0;
}