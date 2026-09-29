#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

int isSubsetSum(const int set[], int n, int sum) {
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

int main(int argc, char * const argv[]) {
    if (argc < 3) {
        return 1;
    }
    int n = argc - 2;
    int *set = (int *)malloc(n * sizeof(int));
    if (set == NULL) {
        return 1;
    }
    char *endptr;
    for (int i = 0; i < n; i++) {
        errno = 0;
        long val = strtol(argv[i + 1], &endptr, 10);
        if (errno != 0 || endptr == argv[i + 1] || *endptr != '\0' || val < INT_MIN || val > INT_MAX) {
            free(set);
            return 1;
        }
        set[i] = (int)val;
    }
    errno = 0;
    long sum_val = strtol(argv[argc - 1], &endptr, 10);
    if (errno != 0 || endptr == argv[argc - 1] || *endptr != '\0' || sum_val < 0 || sum_val > INT_MAX) {
        free(set);
        return 1;
    }
    int sum = (int)sum_val;
    int result = isSubsetSum(set, n, sum);
    printf("%d\n", result);
    free(set);
    return 0;
}