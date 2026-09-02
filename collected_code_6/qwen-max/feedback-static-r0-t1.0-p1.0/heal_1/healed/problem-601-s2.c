#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    const int *pairA = *(const int * const *)a;
    const int *pairB = *(const int * const *)b;
    return pairA[1] - pairB[1];
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int longestChain(const int **pairs, int pairsSize, const int *pairsColSize) {
    qsort(pairs, pairsSize, sizeof(int *), compare);
    int *dp = (int *)malloc(pairsSize * sizeof(int));
    for (int i = 0; i < pairsSize; ++i) {
        dp[i] = 1;
    }
    for (int i = 1; i < pairsSize; ++i) {
        for (int j = 0; j < i; ++j) {
            if (pairs[i][0] > pairs[j][1]) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
    }
    int maxLength = 0;
    for (int i = 0; i < pairsSize; ++i) {
        if (dp[i] > maxLength) {
            maxLength = dp[i];
        }
    }
    free(dp);
    return maxLength;
}

int main() {
    int pairsSize = 4;
    const int *pairs[] = {
        (const int[]){1, 2},
        (const int[]){2, 3},
        (const int[]){3, 4},
        (const int[]){1, 4}
    };
    const int pairsColSize = 2;
    printf("The length of the longest chain is: %d\n", longestChain(pairs, pairsSize, &pairsColSize));
    return 0;
}