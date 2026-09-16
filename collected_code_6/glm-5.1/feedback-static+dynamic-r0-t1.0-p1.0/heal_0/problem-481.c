#include <stdio.h>
#include <stdlib.h>

int isSubsetSum(int set[], int n, int sum) {
    int subset[n + 1][sum + 1];
    for (int i = 0; i <= n; i++) {
        subset[i][0] = 1;
    }
    for (int i = 1; i <= sum; i++) {
        subset[0][i] = 0;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= sum; j++) {
            if (j < set[i - 1]) {
                subset[i][j] = subset[i - 1][j];
            } else {
                if (subset[i - 1][j] || subset[i - 1][j - set[i - 1]]) {
                    subset[i][j] = 1;
                } else {
                    subset[i][j] = 0;
                }
            }
        }
    }
    return subset[n][sum];
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        return 1;
    }
    int n = argc - 2;
    int *set = (int *)malloc(n * sizeof(int));
    if (set == NULL) {
        return 1;
    }
    for (int i = 0; i < n; i++) {
        set[i] = atoi(argv[i + 1]);
    }
    int sum = atoi(argv[argc - 1]);
    if (sum < 0) {
        free(set);
        return 1;
    }
    int result = isSubsetSum(set, n, sum);
    printf("%d\n", result);
    free(set);
    return 0;
}