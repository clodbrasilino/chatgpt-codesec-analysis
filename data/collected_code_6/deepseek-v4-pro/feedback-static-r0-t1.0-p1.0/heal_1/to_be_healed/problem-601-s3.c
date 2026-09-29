#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Pair;

int compare_pairs(const void *a, const void *b) {
    /* Possible weaknesses found:
     *  Variable 'pair_a' can be declared as pointer to const [constVariablePointer]
     */
    Pair *pair_a = (Pair *)a;
    /* Possible weaknesses found:
     *  Variable 'pair_b' can be declared as pointer to const [constVariablePointer]
     */
    Pair *pair_b = (Pair *)b;
    return pair_a->first - pair_b->first;
}

int find_longest_chain(Pair *pairs, int n) {
    if (pairs == NULL || n <= 0) {
        return 0;
    }

    qsort(pairs, n, sizeof(Pair), compare_pairs);

    int *dp = (int *)malloc(n * sizeof(int));
    if (dp == NULL) {
        return 0;
    }

    for (int i = 0; i < n; i++) {
        dp[i] = 1;
    }

    int max_chain = 1;

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (pairs[j].second < pairs[i].first && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
            }
        }
        if (dp[i] > max_chain) {
            max_chain = dp[i];
        }
    }

    free(dp);
    return max_chain;
}

int main(void) {
    Pair pairs[] = {{5, 24}, {39, 60}, {15, 28}, {27, 40}, {50, 90}};
    int n = sizeof(pairs) / sizeof(pairs[0]);

    int result = find_longest_chain(pairs, n);
    printf("%d\n", result);

    return 0;
}