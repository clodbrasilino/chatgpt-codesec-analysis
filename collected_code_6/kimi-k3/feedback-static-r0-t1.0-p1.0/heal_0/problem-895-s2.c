#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int maxSumNoAdjacent(const int *arr, size_t n) {
    if (arr == NULL || n == 0) {
        return 0;
    }
    
    int incl = arr[0];
    int excl = 0;
    
    for (size_t i = 1; i < n; i++) {
        int new_excl = (incl > excl) ? incl : excl;
        
        if (excl > INT_MAX - arr[i]) {
            incl = INT_MAX;
        } else if (excl < INT_MIN - arr[i]) {
            incl = INT_MIN;
        } else {
            incl = excl + arr[i];
        }
        
        excl = new_excl;
    }
    
    return (incl > excl) ? incl : excl;
}

int main(void) {
    int arr[] = {5, 5, 10, 100, 10, 5};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    
    int result = maxSumNoAdjacent(arr, n);
    
    if (printf("Maximum sum: %d\n", result) < 0) {
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}