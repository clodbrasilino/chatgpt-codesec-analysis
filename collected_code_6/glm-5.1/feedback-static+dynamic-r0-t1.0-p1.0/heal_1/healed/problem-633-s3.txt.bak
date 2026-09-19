#include <stdio.h>
#include <stdlib.h>

long long sum_of_xor_pairs(const int *arr, int n) {
    long long total = 0;
    for (int i = 0; i < 32; i++) {
        long long count = 0;
        for (int j = 0; j < n; j++) {
            if (arr[j] & (1 << i)) {
                count++;
            }
        }
        total += (count * (n - count) * (1LL << i));
    }
    return total;
}

int main(int argc, char * const argv[]) {
    if (argc < 2) {
        return 1;
    }
    int n = atoi(argv[1]);
    if (n <= 0) {
        return 1;
    }
    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        return 1;
    }
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            free(arr);
            return 1;
        }
    }
    long long result = sum_of_xor_pairs(arr, n);
    printf("%lld\n", result);
    free(arr);
    return 0;
}