#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long delannoy_number(int n, int m) {
    if (n < 0 || m < 0) return -1;
    if (n == 0 || m == 0) return 1;

    if (n > INT_MAX / (m + 1)) return -1;

    size_t size = (size_t)(n + 1) * (m + 1);
    long long *dp = (long long *)malloc(size * sizeof(long long));
    if (dp == NULL) return -1;

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            if (i == 0 || j == 0) {
                dp[i * (m + 1) + j] = 1;
            } else {
                long long a = dp[(i - 1) * (m + 1) + j];
                long long b = dp[i * (m + 1) + j - 1];
                long long c = dp[(i - 1) * (m + 1) + j - 1];

                if (a > LLONG_MAX - b || b > LLONG_MAX - c || a > LLONG_MAX - c) return -1;

                dp[i * (m + 1) + j] = a + b + c;
            }
        }
    }

    long long result = dp[n * (m + 1) + m];
    free(dp);
    return result;
}

int main() {
    int n, m;
    printf("Enter n and m: ");
    if (scanf("%d %d", &n, &m) != 2) {
        printf("Invalid input\n");
        return 1;
    }
    long long result = delannoy_number(n, m);
    if (result == -1) {
        printf("Error calculating Delannoy number\n");
    } else {
        printf("The Delannoy number D(%d, %d) is: %lld\n", n, m, result);
    }
    return 0;
}