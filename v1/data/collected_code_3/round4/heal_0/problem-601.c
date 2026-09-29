#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int dp[MAX];

int max(int a, int b) {
    return (a > b) ? a : b;
}

int findLongestChain(int pairs[MAX][2], int n) {
    for (int i = 0; i < n; i++) {
        dp[i] = 1;
    }

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (pairs[j][1] < pairs[i][0]) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
    }

    int maxChain = 0;
    for (int i = 0; i < n; i++) {
        if (maxChain < dp[i]) {
            maxChain = dp[i];
        }
    }

    return maxChain;
}

int main() {
    int n;
    printf("Enter the number of pairs: ");
    scanf("%d", &n);

    int pairs[MAX][2];
    printf("Enter the pairs: \n");
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &pairs[i][0], &pairs[i][1]);
    }

    int longestChain = findLongestChain(pairs, n);
    printf("The longest chain that can be formed is of length: %d\n", longestChain);

    return 0;
}