#include <stdio.h>
#include <stdlib.h>

int isSubsetSum(const int set[], int n, int sum) {
    int *subset = (int *)malloc((n + 1) * (sum + 1) * sizeof(int));
    if (subset == NULL) {
        return -1;
    }
    for (int i = 0; i <= n; i++) {
        subset[i * (sum + 1) + 0] = 1;
    }
    for (int i = 1; i <= sum; i++) {
        subset[0 * (sum + 1) + i] = 0;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= sum; j++) {
            if (j < set[i - 1]) {
                subset[i * (sum + 1) + j] = subset[(i - 1) * (sum + 1) + j];
            } else {
                if (subset[(i - 1) * (sum + 1) + j] || subset[(i - 1) * (sum + 1) + (j - set[i - 1])]) {
                    subset[i * (sum + 1) + j] = 1;
                } else {
                    subset[i * (sum + 1) + j] = 0;
                }
            }
        }
    }
    int result = subset[n * (sum + 1) + sum];
    free(subset);
    return result;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    int n;
    int *set;
    int sum;
    int result;

    if (argc < 3) {
        return 1;
    }
    n = argc - 2;
    set = (int *)malloc(n * sizeof(int));
    if (set == NULL) {
        return 1;
    }
    for (int i = 0; i < n; i++) {
        set[i] = atoi(argv[i + 1]);
    }
    sum = atoi(argv[argc - 1]);
    if (sum < 0) {
        free(set);
        return 1;
    }
    result = isSubsetSum(set, n, sum);
    printf("%d\n", result);
    free(set);
    return 0;
}