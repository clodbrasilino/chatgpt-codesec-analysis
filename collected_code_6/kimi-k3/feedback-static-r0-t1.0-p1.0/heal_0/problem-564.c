#include <stdio.h>
#include <stdlib.h>

size_t count_unequal_pairs(const int *arr, size_t n) {
    size_t count = 0;
    size_t i, j;
    
    if (arr == NULL || n == 0) {
        return 0;
    }
    
    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (arr[i] != arr[j]) {
                count++;
            }
        }
    }
    
    return count;
}

int main(void) {
    int arr[] = {1, 2, 3, 2, 1};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    size_t result;
    
    result = count_unequal_pairs(arr, n);
    
    printf("Number of unequal element pairs: %zu\n", result);
    
    return 0;
}