#include <stdio.h>
#include <stdlib.h>

unsigned long long count_subsequences(const int *arr, int n, int k) {
    if (arr == NULL || n <= 0 || k <= 0) {
        return 0;
    }

    int z_count = 0;
    int n_nz = 0;
    int *snz = (int *)malloc((size_t)n * sizeof(int));
    
    if (snz == NULL) {
        return 0;
    }

    for (int i = 0; i < n; i++) {
        if (arr[i] == 0) {
            z_count++;
        } else {
            snz[n_nz++] = arr[i];
        }
    }

    unsigned long long v = 0;
    if (k > 1 && n_nz > 0) {
        unsigned long long *dp = (unsigned long long *)calloc((size_t)k, sizeof(unsigned long long));
        if (dp == NULL) {
            free(snz);
            return 0;
        }

        for (int j = 0; j < n_nz; j++) {
            int val = snz[j];
            for (int i = k - 1; i >= val; i--) {
                dp[i] += dp[i / val] + 1ULL;
            }
        }
        v = dp[k - 1];
        free(dp);
    }

    free(snz);

    unsigned long long p_nz = 1;
    for (int i = 0; i < n_nz; i++) {
        p_nz *= 2ULL;
    }

    unsigned long long p_z = 1;
    for (int i = 0; i < z_count; i++) {
        p_z *= 2ULL;
    }

    unsigned long long result = v;
    if (z_count > 0) {
        result += p_nz * (p_z - 1ULL);
    }

    return result;
}

int main(void) {
    int arr[] = {1, 2, 3, 4};
    int k = 10;
    int n = sizeof(arr) / sizeof(arr[0]);

    unsigned long long result = count_subsequences(arr, n, k);
    printf("%llu\n", result);

    return 0;
}