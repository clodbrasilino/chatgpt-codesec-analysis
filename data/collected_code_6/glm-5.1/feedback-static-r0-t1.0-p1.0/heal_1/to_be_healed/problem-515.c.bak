#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as const array [constParameter]
 */
int check_subset_divisible(int arr[], int n, int m) {
    if (n > m) {
        return 1;
    }
    int *dp = (int *)malloc(m * sizeof(int));
    if (dp == NULL) {
        return -1;
    }
    memset(dp, 0, m * sizeof(int));
    for (int i = 0; i < n; i++) {
        int mod = arr[i] % m;
        if (mod < 0) {
            mod += m;
        }
        int *temp = (int *)malloc(m * sizeof(int));
        if (temp == NULL) {
            free(dp);
            return -1;
        }
        memcpy(temp, dp, m * sizeof(int));
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