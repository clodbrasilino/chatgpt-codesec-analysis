#include <stdio.h>
#include <stdlib.h>

int product_of_non_repeated(const int *arr, size_t size, long long *result) {
    if (arr == NULL || result == NULL) {
        return -1;
    }
    if (size == 0) {
        return -2;
    }
    
    int *counts = (int *)calloc(size, sizeof(int));
    if (counts == NULL) {
        return -3;
    }
    
    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++) {
            if (arr[i] == arr[j]) {
                counts[i]++;
            }
        }
    }
    
    long long product = 1;
    int has_non_repeated = 0;
    
    for (size_t i = 0; i < size; i++) {
        if (counts[i] == 1) {
            product *= arr[i];
            has_non_repeated = 1;
        }
    }
    
    free(counts);
    
    if (!has_non_repeated) {
        return -4;
    }
    
    *result = product;
    return 0;
}

int main() {
    int arr[] = {2, 3, 4, 5, 2, 6, 3};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    long long result = 0;
    
    int status = product_of_non_repeated(arr, size, &result);
    
    if (status == 0) {
        printf("%lld\n", result);
    } else {
        printf("Error code: %d\n", status);
    }
    
    return 0;
}