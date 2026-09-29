#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Pair;

int compare_pairs(const void *a, const void *b) {
    const Pair *pa = (const Pair *)a;
    const Pair *pb = (const Pair *)b;
    return pa->first - pb->first;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int longest_chain(Pair pairs[], int n) {
    if (n == 0) return 0;

    qsort(pairs, n, sizeof(Pair), compare_pairs);

    int *dp = (int *)malloc(n * sizeof(int));
    if (!dp) return -1;

    for (int i = 0; i < n; i++) {
        dp[i] = 1;
    }

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (pairs[j].second < pairs[i].first) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
    }

    int max_len = 0;
    for (int i = 0; i < n; i++) {
        max_len = max(max_len, dp[i]);
    }

    free(dp);
    return max_len;
}

int main(void) {
    Pair pairs[] = {
        {5, 24},
        {39, 60},
        {15, 28},
        {27, 40},
        {50, 90}
    };
    int n = sizeof(pairs) / sizeof(pairs[0]);

    int result = longest_chain(pairs, n);

    if (result < 0) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    printf("Length of longest chain: %d\n", result);

    return 0;
}