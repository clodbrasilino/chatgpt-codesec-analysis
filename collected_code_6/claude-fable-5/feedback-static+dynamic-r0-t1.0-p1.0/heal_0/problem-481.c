#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool isSubsetSum(const int *set, size_t n, int sum)
{
    if (set == NULL && n > 0) {
        return false;
    }
    if (sum < 0) {
        return false;
    }

    size_t cols = (size_t)sum + 1;
    bool *dp = calloc(cols, sizeof(bool));
    if (dp == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    dp[0] = true;

    for (size_t i = 0; i < n; i++) {
        if (set[i] < 0) {
            free(dp);
            return false;
        }
        for (int j = sum; j >= set[i]; j--) {
            if (dp[(size_t)(j - set[i])]) {
                dp[(size_t)j] = true;
            }
        }
    }

    bool result = dp[(size_t)sum];
    free(dp);
    return result;
}

int main(void)
{
    int set[] = {3, 34, 4, 12, 5, 2};
    size_t n = sizeof(set) / sizeof(set[0]);
    int sum = 9;

    if (isSubsetSum(set, n, sum)) {
        if (printf("Found a subset with the given sum\n") < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (printf("No subset with the given sum\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}