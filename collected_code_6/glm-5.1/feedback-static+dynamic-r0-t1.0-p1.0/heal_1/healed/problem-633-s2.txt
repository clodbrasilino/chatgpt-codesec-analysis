#include <stdio.h>
#include <stdlib.h>

long long sum_of_xor_pairs(const int *arr, int n) {
    long long total_sum = 0;
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            total_sum += (long long)(arr[i] ^ arr[j]);
        }
    }
    return total_sum;
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