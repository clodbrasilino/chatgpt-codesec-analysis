#include <stdio.h>
#include <stdlib.h>

int max_segments(int n, int a, int b, int c) {
    if (n < 0 || a <= 0 || b <= 0 || c <= 0) {
        return -1;
    }

    int *dp = (int *)malloc((n + 1) * sizeof(int));
    if (dp == NULL) {
        return -1;
    }

    for (int i = 0; i <= n; i++) {
        dp[i] = -1;
    }

    dp[0] = 0;

    for (int i = 0; i <= n; i++) {
        if (dp[i] != -1) {
            if (i + a <= n && dp[i] + 1 > dp[i + a]) {
                dp[i + a] = dp[i] + 1;
            }
            if (i + b <= n && dp[i] + 1 > dp[i + b]) {
                dp[i + b] = dp[i] + 1;
            }
            if (i + c <= n && dp[i] + 1 > dp[i + c]) {
                dp[i + c] = dp[i] + 1;
            }
        }
    }

    int result = dp[n];
    free(dp);
    return result;
}

int main(void) {
    int n = 7;
    int a = 5;
    int b = 2;
    int c = 2;

    int result = max_segments(n, a, b, c);
    
    if (result != -1) {
        printf("%d\n", result);
    } else {
        printf("Error or no segments can be formed.\n");
    }

    return 0;
}