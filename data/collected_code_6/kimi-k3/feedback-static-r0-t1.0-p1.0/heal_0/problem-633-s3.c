#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long sumOfXorPairs(const int *arr, size_t n) {
    if (arr == NULL || n == 0) {
        return 0;
    }
    
    long long sum = 0;
    for (size_t i = 0; i < n; i++) {
        for (size_t j = i + 1; j < n; j++) {
            sum += (long long)(arr[i] ^ arr[j]);
        }
    }
    return sum;
}

int main(void) {
    size_t n;
    
    if (scanf("%zu", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (n == 0 || n > SIZE_MAX / sizeof(int)) {
        fprintf(stderr, "Invalid array size\n");
        return EXIT_FAILURE;
    }
    
    int *arr = malloc(n * sizeof(int));
    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    
    for (size_t i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            fprintf(stderr, "Invalid array element\n");
            free(arr);
            return EXIT_FAILURE;
        }
    }
    
    long long result = sumOfXorPairs(arr, n);
    printf("%lld\n", result);
    
    free(arr);
    return EXIT_SUCCESS;
}