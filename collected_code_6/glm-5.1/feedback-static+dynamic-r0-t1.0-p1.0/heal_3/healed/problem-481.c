#include <stdio.h>
#include <stdlib.h>

int isSubsetSum(const int set[], int n, int sum) {
    int *prev = (int *)calloc(sum + 1, sizeof(int));
    int *curr = (int *)calloc(sum + 1, sizeof(int));
    if (!prev || !curr) {
        free(prev);
        free(curr);
        return 0;
    }
    prev[0] = 1;
    for (int i = 1; i <= n; i++) {
        curr[0] = 1;
        for (int j = 1; j <= sum; j++) {
            if (j < set[i - 1]) {
                curr[j] = prev[j];
            } else {
                curr[j] = prev[j] || prev[j - set[i - 1]];
            }
        }
        int *temp = prev;
        prev = curr;
        curr = temp;
    }
    int result = prev[sum];
    free(prev);
    free(curr);
    return result;
}

int main(int argc, char const * const * argv) {
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
    if (sum < 0 || sum > 1000000) {
        free(set);
        return 1;
    }
    int result = isSubsetSum(set, n, sum);
    printf("%d\n", result);
    free(set);
    return 0;
}