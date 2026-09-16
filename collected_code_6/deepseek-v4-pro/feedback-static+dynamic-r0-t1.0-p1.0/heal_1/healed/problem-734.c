#include <stdio.h>
#include <stdlib.h>

long long sum_of_products_subarrays(const int arr[], int n) {
    long long total_sum = 0;
    for (int i = 0; i < n; i++) {
        long long product = 1;
        for (int j = i; j < n; j++) {
            product *= arr[j];
            total_sum += product;
        }
    }
    return total_sum;
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) {
        return 1;
    }
    if (n <= 0) {
        return 0;
    }

    int *arr = (int *)malloc((size_t)n * sizeof(int));
    if (arr == NULL) {
        return 1;
    }

    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            free(arr);
            return 1;
        }
    }

    long long result = sum_of_products_subarrays(arr, n);
    printf("%lld\n", result);

    free(arr);
    return 0;
}