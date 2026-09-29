#include <stdio.h>
#include <stdlib.h>

long long sum_of_products(int *arr, int n) {
    long long result = 0;
    for (int i = 0; i < n; ++i) {
        long long product = 1;
        for (int j = i; j < n; ++j) {
            product *= arr[j];
            result += product;
        }
    }
    return result;
}

int main() {
    int n;
    printf("Enter the size of the array: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("Enter %d elements of the array: ", n);
    for (int i = 0; i < n; ++i) {
        if (scanf("%d", &arr[i]) != 1) {
            fprintf(stderr, "Invalid input\n");
            free(arr);
            return EXIT_FAILURE;
        }
    }

    long long result = sum_of_products(arr, n);
    printf("Sum of products of all possible subarrays: %lld\n", result);

    free(arr);
    return EXIT_SUCCESS;
}