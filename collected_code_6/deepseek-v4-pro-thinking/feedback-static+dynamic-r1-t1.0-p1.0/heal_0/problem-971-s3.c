#include <stdio.h>
#include <stdlib.h>

int maxSegments(int n, int a, int b, int c) {
    int lengths[3];
    int *dp;
    int result;
    int i;
    int j;

    if (n < 0) {
        return -1;
    }

    if (n == 0) {
        return 0;
    }

    lengths[0] = a;
    lengths[1] = b;
    lengths[2] = c;

    dp = (int *)malloc((size_t)(n + 1) * sizeof(int));
    if (dp == NULL) {
        return -1;
    }

    dp[0] = 0;

    for (i = 1; i <= n; i++) {
        dp[i] = -1;

        for (j = 0; j < 3; j++) {
            int len = lengths[j];

            if (len > 0 && i >= len && dp[i - len] != -1) {
                int cand = dp[i - len] + 1;

                if (cand > dp[i]) {
                    dp[i] = cand;
                }
            }
        }
    }

    result = dp[n];
    free(dp);

    return result;
}

int main(void) {
    int n;
    int a;
    int b;
    int c;
    int result;

    if (scanf("%d %d %d %d", &n, &a, &b, &c) != 4) {
        return 1;
    }

    if (n < 0 || a <= 0 || b <= 0 || c <= 0) {
        return 1;
    }

    result = maxSegments(n, a, b, c);
    printf("%d\n", result);

    return 0;
}