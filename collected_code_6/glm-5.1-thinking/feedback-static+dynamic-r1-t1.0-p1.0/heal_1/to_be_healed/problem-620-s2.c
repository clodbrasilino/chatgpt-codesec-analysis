#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b) {
    long long va = llabs((long long)(*(const int *)a));
    long long vb = llabs((long long)(*(const int *)b));
    if (va < vb) return -1;
    if (va > vb) return 1;
    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
int* largestDivisibleSubset(int* arr, int n, int* returnSize) {
    if (n == 0 || arr == NULL || returnSize == NULL) {
        if (returnSize) *returnSize = 0;
        return NULL;
    }
    
    int *sorted = malloc(n * sizeof(int));
    if (!sorted) {
        *returnSize = 0;
        return NULL;
    }
    for (int i = 0; i < n; i++) sorted[i] = arr[i];
    qsort(sorted, n, sizeof(int), cmp);
    
    int *dp = malloc(n * sizeof(int));
    int *prev = malloc(n * sizeof(int));
    if (!dp || !prev) {
        free(sorted);
        free(dp);
        free(prev);
        *returnSize = 0;
        return NULL;
    }
    
    for (int i = 0; i < n; i++) {
        dp[i] = 1;
        prev[i] = -1;
    }
    
    int max_idx = 0;
    int max_len = 1;
    
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (sorted[j] != 0) {
                long long vi = (long long)sorted[i];
                long long vj = (long long)sorted[j];
                if (vi % vj == 0) {
                    if (dp[j] + 1 > dp[i]) {
                        dp[i] = dp[j] + 1;
                        prev[i] = j;
                    }
                }
            }
        }
        if (dp[i] > max_len) {
            max_len = dp[i];
            max_idx = i;
        }
    }
    
    int *result = malloc(max_len * sizeof(int));
    if (!result) {
        free(sorted);
        free(dp);
        free(prev);
        *returnSize = 0;
        return NULL;
    }
    
    int curr = max_idx;
    for (int i = max_len - 1; i >= 0; i--) {
        result[i] = sorted[curr];
        curr = prev[curr];
    }
    
    free(sorted);
    free(dp);
    free(prev);
    
    *returnSize = max_len;
    return result;
}

int main() {
    int arr[] = {1, 2, 3, 4, 6, 8, 9, 12, 18, 24, 0, -4, -2};
    int n = sizeof(arr) / sizeof(arr[0]);
    int returnSize;
    int *result = largestDivisibleSubset(arr, n, &returnSize);
    
    if (result) {
        for (int i = 0; i < returnSize; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");
        free(result);
    }
    
    return 0;
}