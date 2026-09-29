#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_subset_divisible(const int arr[], int n, int m) {
    if (m <= 0) {
        return -1;
    }
    if (n > m) {
        return 1;
    }
    size_t dp_size = (size_t)m * sizeof(int);
    int *dp = (int *)calloc((size_t)m, sizeof(int));
    if (dp == NULL) {
        return -1;
    }
    for (int i = 0; i < n; i++) {
        int mod = arr[i] % m;
        if (mod < 0) {
            mod += m;
        }
        int *temp = (int *)malloc(dp_size);
        if (temp == NULL) {
            free(dp);
            return -1;
        }
        if (dp_size > 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(temp, dp, dp_size);
        }
        if (temp[mod] == 0) {
            dp[mod] = 1;
            if (mod == 0) {
                free(temp);
                free(dp);
                return 1;
            }
        }
        for (int j = 0; j < m; j++) {
            if (temp[j] == 1) {
                int new_mod = (j + mod) % m;
                if (dp[new_mod] == 0) {
                    dp[new_mod] = 1;
                    if (new_mod == 0) {
                        free(temp);
                        free(dp);
                        return 1;
                    }
                }
            }
        }
        free(temp);
    }
    int result = dp[0];
    free(dp);
    return result;
}

int main(void) {
    int arr[] = {3, 1, 7, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int m = 6;
    int res = check_subset_divisible(arr, n, m);
    if (res == 1) {
        printf("Yes\n");
    } else if (res == 0) {
        printf("No\n");
    } else {
        fprintf(stderr, "Allocation failed\n");
        return 1;
    }
    return 0;
}