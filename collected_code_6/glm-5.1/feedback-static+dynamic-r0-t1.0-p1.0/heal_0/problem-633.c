#include <stdio.h>
#include <stdlib.h>

unsigned long long sum_of_xor_pairs(int *arr, size_t n) {
    unsigned long long sum = 0;
    for (size_t i = 0; i < n; i++) {
        for (size_t j = i + 1; j < n; j++) {
            sum += (unsigned long long)(arr[i] ^ arr[j]);
        }
    }
    return sum;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        return 1;
    }
    size_t n = (size_t)(argc - 1);
    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        return 1;
    }
    for (size_t i = 0; i < n; i++) {
        arr[i] = atoi(argv[i + 1]);
    }
    unsigned long long result = sum_of_xor_pairs(arr, n);
    printf("%llu\n", result);
    free(arr);
    return 0;
}