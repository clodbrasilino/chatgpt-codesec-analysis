#include <stdio.h>
#include <stdlib.h>

int isSubsetSum(const int arr[], int n, int sum) {
    int subset[n + 1][sum + 1];

    for (int i = 0; i <= n; i++) {
        subset[i][0] = 1;
    }

    for (int i = 1; i <= sum; i++) {
        subset[0][i] = 0;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= sum; j++) {
            if (arr[i - 1] > j) {
                subset[i][j] = subset[i - 1][j];
            } else {
                subset[i][j] = subset[i - 1][j] || subset[i - 1][j - arr[i - 1]];
            }
        }
    }

    return subset[n][sum];
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc < 4) {
        fprintf(stderr, "Usage: %s <sum> <n> <elements...>\n", argv[0]);
        return 1;
    }

    char *endptr;
    long target_sum = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || target_sum < 0 || target_sum > 2147483647) {
        fprintf(stderr, "Invalid sum\n");
        return 1;
    }

    long n = strtol(argv[2], &endptr, 10);
    if (*endptr != '\0' || n < 0 || n > 2147483647 || n != argc - 3) {
        fprintf(stderr, "Invalid n or element count mismatch\n");
        return 1;
    }

    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL && n > 0) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        long val = strtol(argv[3 + i], &endptr, 10);
        if (*endptr != '\0' || val < 0 || val > 2147483647) {
            fprintf(stderr, "Invalid element\n");
            free(arr);
            return 1;
        }
        arr[i] = (int)val;
    }

    int result = isSubsetSum(arr, (int)n, (int)target_sum);
    printf("%d\n", result);

    free(arr);
    return 0;
}