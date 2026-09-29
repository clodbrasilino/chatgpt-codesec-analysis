#include <stdio.h>
#include <stdlib.h>

struct Pair {
    int first;
    int second;
};

int compare(const void *a, const void *b) {
    /* Possible weaknesses found:
     *  Variable 'p1' can be declared as pointer to const [constVariablePointer]
     */
    struct Pair *p1 = (struct Pair *)a;
    /* Possible weaknesses found:
     *  Variable 'p2' can be declared as pointer to const [constVariablePointer]
     */
    struct Pair *p2 = (struct Pair *)b;
    if (p1->first != p2->first) {
        return p1->first - p2->first;
    }
    return p1->second - p2->second;
}

int findLongestChain(struct Pair *pairs, int n) {
    if (n == 0) {
        return 0;
    }
    
    qsort(pairs, n, sizeof(struct Pair), compare);
    
    int *dp = (int *)malloc(n * sizeof(int));
    if (!dp) {
        return 0;
    }
    
    for (int i = 0; i < n; i++) {
        dp[i] = 1;
    }
    
    int max_len = 1;
    
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (pairs[j].second < pairs[i].first) {
                if (dp[j] + 1 > dp[i]) {
                    dp[i] = dp[j] + 1;
                }
            }
        }
        if (dp[i] > max_len) {
            max_len = dp[i];
        }
    }
    
    free(dp);
    return max_len;
}

int main() {
    struct Pair pairs[] = {{5, 24}, {39, 60}, {15, 28}, {27, 40}, {50, 90}};
    int n = sizeof(pairs) / sizeof(pairs[0]);
    
    int result = findLongestChain(pairs, n);
    printf("%d\n", result);
    
    return 0;
}