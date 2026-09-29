#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static bool subset_sum(const int *set, size_t n, int target)
{
    if (set == NULL && n > 0) {
        return false;
    }
    if (target < 0) {
        return false;
    }
    if (target == 0) {
        return true;
    }

    size_t width = (size_t)target + 1U;
    bool *dp = calloc(width, sizeof(bool));
    if (dp == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    dp[0] = true;

    for (size_t i = 0; i < n; i++) {
        int value = set[i];
        if (value < 0 || value > target) {
            continue;
        }
        for (int j = target; j >= value; j--) {
            if (dp[(size_t)(j - value)]) {
                dp[(size_t)j] = true;
            }
        }
    }

    bool result = dp[(size_t)target];
    free(dp);
    return result;
}

int main(void)
{
    int set[] = {3, 34, 4, 12, 5, 2};
    size_t n = sizeof(set) / sizeof(set[0]);
    int sum = 9;

    if (subset_sum(set, n, sum)) {
        if (printf("Found a subset with the given sum %d\n", sum) < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (printf("No subset with the given sum %d\n", sum) < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}