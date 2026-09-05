#include <stdio.h>
#include <stdlib.h>

long long count_odd_xor_pairs(const int *arr, int n) {
    long long even = 0;
    long long odd = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] % 2 == 0) {
            even++;
        } else {
            odd++;
        }
    }
    return even * odd;
}

int main(int argc, char * const argv[]) {
    if (argc < 2) {
        return 1;
    }
    int n = atoi(argv[1]);
    if (n < 0) {
        return 1;
    }
    if (n == 0) {
        printf("%lld\n", 0LL);
        return 0;
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
    long long result = count_odd_xor_pairs(arr, n);
    printf("%lld\n", result);
    free(arr);
    arr = NULL;
    return 0;
}