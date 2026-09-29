#include <stdio.h>
#include <stdlib.h>

long long eulerian_number(int n, int m) {
    if (n == 0) {
        return m == 0 ? 1 : 0;
    }
    if (m < 0 || m >= n) {
        return 0;
    }

    long long *dp = (long long*)calloc((size_t)n + 1, sizeof(long long));
    if (dp == NULL) {
        return -1;
    }

    dp[0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = i; j >= 1; j--) {
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: 8 * 1300365805079109480 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:206,execs:168,op:havoc,rep:1)
             * UBSan: signed integer overflow: 6795622177941569380 + 4663059128687439720 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:206,execs:168,op:havoc,rep:1)
             * UBSan: signed integer overflow: 14 * 1300365805079109480 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:206,execs:168,op:havoc,rep:1)
             */
            dp[j] = (i - j) * dp[j - 1] + (j + 1) * dp[j];
        }
        dp[0] = 1;
    }

    long long result = dp[m];
    free(dp);
    return result;
}

int main(void) {
    int n, m;
    printf("Enter n and m: ");
    if (scanf("%d %d", &n, &m) != 2) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    long long result = eulerian_number(n, m);
    if (result < 0) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("A(%d, %d) = %lld\n", n, m, result);
    return EXIT_SUCCESS;
}