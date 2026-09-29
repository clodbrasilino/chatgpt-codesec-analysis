#include <stdio.h>
#include <stdlib.h>

long long sumXorPairs(int *arr, int n) {
    long long result = 0;
    for (int bit = 0; bit < 31; bit++) {
        long long count_ones = 0;
        for (int i = 0; i < n; i++) {
            if (arr[i] & (1 << bit)) {
                count_ones++;
            }
        }
        long long count_zeros = n - count_ones;
        result += (count_ones * count_zeros) * (1LL << bit);
    }
    return result;
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1 || n <= 0) {
        return 1;
    }
    int *arr = malloc((size_t)n * sizeof(int));
    if (arr == NULL) {
        return 1;
    }
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            free(arr);
            return 1;
        }
    }
    long long answer = sumXorPairs(arr, n);
    printf("%lld\n", answer);
    free(arr);
    return 0;
}