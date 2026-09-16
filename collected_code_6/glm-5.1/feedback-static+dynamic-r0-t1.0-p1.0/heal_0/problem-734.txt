#include <stdio.h>
#include <stdlib.h>

long long sum_of_products(int *arr, int n) {
    long long total = 0;
    long long current = 1;
    for (int i = 0; i < n; i++) {
        current *= arr[i];
        total += current;
    }
    return total;
}

int main() {
    int n;
    if (scanf("%d", &n) != 1 || n <= 0) {
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
    long long result = sum_of_products(arr, n);
    printf("%lld\n", result);
    free(arr);
    return 0;
}