#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>

bool isSubsetSum(const int set[], int n, int sum) {
    int num_bytes = (sum + 1) * sizeof(bool);
    bool *prev = malloc(num_bytes);
    bool *curr = malloc(num_bytes);
    if (!prev || !curr) {
        free(prev);
        free(curr);
        return false;
    }
    memset(prev, true, sizeof(bool));
    for (int i = 1; i <= sum; i++) {
        prev[i] = false;
    }
    for (int i = 1; i <= n; i++) {
        curr[0] = true;
        for (int j = 1; j <= sum; j++) {
            if (j < set[i - 1]) {
                curr[j] = prev[j];
            } else {
                curr[j] = prev[j] || prev[j - set[i - 1]];
            }
        }
        bool *temp = prev;
        prev = curr;
        curr = temp;
    }
    bool result = prev[sum];
    free(prev);
    free(curr);
    return result;
}

int main(int argc, char const * const argv[]) {
    if (argc < 3) {
        return 1;
    }
    int n = argc - 2;
    int *set = malloc(n * sizeof(int));
    if (set == NULL) {
        return 1;
    }
    for (int i = 0; i < n; i++) {
        char *endptr;
        errno = 0;
        long val = strtol(argv[i + 1], &endptr, 10);
        if (errno != 0 || endptr == argv[i + 1] || *endptr != '\0' || val < INT_MIN || val > INT_MAX) {
            free(set);
            return 1;
        }
        set[i] = (int)val;
    }
    char *endptr;
    errno = 0;
    long sum_val = strtol(argv[argc - 1], &endptr, 10);
    if (errno != 0 || endptr == argv[argc - 1] || *endptr != '\0' || sum_val < 0 || sum_val > INT_MAX) {
        free(set);
        return 1;
    }
    int sum = (int)sum_val;
    bool result = isSubsetSum(set, n, sum);
    printf("%d\n", result);
    free(set);
    return 0;
}