#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool isSubsetSum(int set[], int n, int sum) {
    if (sum < 0) {
        return false;
    }
    
    bool **subset = (bool **)malloc((n + 1) * sizeof(bool *));
    if (subset == NULL) {
        return false;
    }
    
    for (int i = 0; i <= n; i++) {
        subset[i] = (bool *)malloc((sum + 1) * sizeof(bool));
        if (subset[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(subset[j]);
            }
            free(subset);
            return false;
        }
    }
    
    for (int i = 0; i <= n; i++) {
        subset[i][0] = true;
    }
    
    for (int i = 1; i <= sum; i++) {
        subset[0][i] = false;
    }
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= sum; j++) {
            if (j < set[i - 1]) {
                subset[i][j] = subset[i - 1][j];
            } else {
                subset[i][j] = subset[i - 1][j] || subset[i - 1][j - set[i - 1]];
            }
        }
    }
    
    bool result = subset[n][sum];
    
    for (int i = 0; i <= n; i++) {
        free(subset[i]);
    }
    free(subset);
    
    return result;
}

int main(void) {
    int set[] = {3, 34, 4, 12, 5, 2};
    int sum = 9;
    int n = sizeof(set) / sizeof(set[0]);
    
    if (isSubsetSum(set, n, sum)) {
        printf("Found a subset with given sum\n");
    } else {
        printf("No subset with given sum\n");
    }
    
    return 0;
}