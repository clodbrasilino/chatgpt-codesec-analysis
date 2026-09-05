#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned long long count_sequences(int n, int m) {
    if (n <= 0 || m <= 0) {
        return 0;
    }

    unsigned long long *dp_curr = (unsigned long long *)calloc((size_t)m + 1, sizeof(unsigned long long));
    unsigned long long *dp_next = (unsigned long long *)calloc((size_t)m + 1, sizeof(unsigned long long));
    unsigned long long *prefix = (unsigned long long *)calloc((size_t)m + 1, sizeof(unsigned long long));

    if (dp_curr == NULL || dp_next == NULL || prefix == NULL) {
        free(dp_curr);
        free(dp_next);
        free(prefix);
        return 0;
    }

    for (int i = 1; i <= m; i++) {
        dp_curr[i] = 1;
    }

    for (int len = 2; len <= n; len++) {
        prefix[0] = 0;
        for (int i = 1; i <= m; i++) {
            prefix[i] = prefix[i - 1] + dp_curr[i];
        }

        for (int i = 1; i <= m; i++) {
            int half = i / 2;
            if (half >= 1) {
                dp_next[i] = prefix[half];
            } else {
                dp_next[i] = 0;
            }
        }

        unsigned long long *temp = dp_curr;
        dp_curr = dp_next;
        dp_next = temp;
    }

    unsigned long long result = 0;
    for (int i = 1; i <= m; i++) {
        result += dp_curr[i];
    }

    free(dp_curr);
    free(dp_next);
    free(prefix);

    return result;
}

int main(void) {
    int n, m;

    if (scanf("%d %d", &n, &m) != 2) {
        return 1;
    }

    if (n < 1 || m < 1) {
        printf("0\n");
        return 0;
    }

    unsigned long long result = count_sequences(n, m);
    printf("%llu\n", result);

    return 0;
}