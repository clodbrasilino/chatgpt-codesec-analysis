#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int findExtraElement(const int *arr1, const int *arr2, size_t n) {
    size_t left = 0;
    size_t right = n - 1;
    
    while (left < right) {
        size_t mid = left + (right - left) / 2;
        if (arr1[mid] == arr2[mid]) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    
    return (int)left;
}

int main(void) {
    size_t n;
    
    if (scanf("%zu", &n) != 1 || n == 0 || n > SIZE_MAX / sizeof(int) - 1) {
        return EXIT_FAILURE;
    }
    
    int *arr1 = malloc(n * sizeof(int));
    if (arr1 == NULL) {
        return EXIT_FAILURE;
    }
    
    int *arr2 = malloc((n + 1) * sizeof(int));
    if (arr2 == NULL) {
        free(arr1);
        return EXIT_FAILURE;
    }
    
    for (size_t i = 0; i < n; i++) {
        if (scanf("%d", &arr1[i]) != 1) {
            free(arr1);
            free(arr2);
            return EXIT_FAILURE;
        }
    }
    
    for (size_t i = 0; i <= n; i++) {
        if (scanf("%d", &arr2[i]) != 1) {
            free(arr1);
            free(arr2);
            return EXIT_FAILURE;
        }
    }
    
    int index = findExtraElement(arr1, arr2, n);
    printf("%d\n", index);
    
    free(arr1);
    free(arr2);
    
    return EXIT_SUCCESS;
}