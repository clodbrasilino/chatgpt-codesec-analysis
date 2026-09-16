#include <stdio.h>
#include <stdlib.h>

long long find_sum_of_products(const int *arr, int n) {
    if (arr == NULL || n <= 0) {
        return 0;
    }

    long long total_sum = 0;

    for (int i = 0; i < n; i++) {
        long long current_product = 1;
        for (int j = i; j < n; j++) {
            if (arr[j] == 0) {
                current_product = 0;
            } else {
                current_product *= arr[j];
            }
            total_sum += current_product;
            if (current_product == 0) {
                break;
            }
        }
    }

    return total_sum;
}

int main() {
    int n;

    if (scanf("%d", &n) != 1) {
        return 1;
    }

    if (n <= 0) {
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

    long long result = find_sum_of_products(arr, n);
    printf("%lld\n", result);

    free(arr);

    return 0;
}