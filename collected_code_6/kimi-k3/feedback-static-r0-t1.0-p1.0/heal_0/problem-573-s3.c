#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

long long calculate_unique_product(const int *arr, size_t size) {
    if (arr == NULL || size == 0) {
        return 0;
    }

    long long product = 1;
    bool found_any = false;

    for (size_t i = 0; i < size; i++) {
        bool is_duplicate = false;
        
        for (size_t j = 0; j < i; j++) {
            if (arr[i] == arr[j]) {
                is_duplicate = true;
                break;
            }
        }
        
        if (!is_duplicate) {
            if (arr[i] != 0) {
                if (product > LLONG_MAX / llabs((long long)arr[i]) || 
                    product < LLONG_MIN / llabs((long long)arr[i])) {
                    return 0;
                }
            }
            product *= arr[i];
            found_any = true;
        }
    }

    return found_any ? product : 0;
}

int main(void) {
    int arr[] = {2, 3, 2, 4, 5, 3};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    
    long long result = calculate_unique_product(arr, size);
    
    if (printf("Product of unique numbers: %lld\n", result) < 0) {
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}