#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int find_frequency_difference(const int *arr, size_t size) {
    if (arr == NULL || size == 0) {
        return -1;
    }
    
    int min_val = INT_MAX;
    int max_val = INT_MIN;
    
    for (size_t i = 0; i < size; i++) {
        if (arr[i] < min_val) min_val = arr[i];
        if (arr[i] > max_val) max_val = arr[i];
    }
    
    size_t range = (size_t)(max_val - min_val) + 1;
    int *freq = calloc(range, sizeof(int));
    if (freq == NULL) {
        return -1;
    }
    
    for (size_t i = 0; i < size; i++) {
        freq[arr[i] - min_val]++;
    }
    
    int max_freq = 0;
    int min_freq = INT_MAX;
    
    for (size_t i = 0; i < range; i++) {
        if (freq[i] > 0) {
            if (freq[i] > max_freq) max_freq = freq[i];
            if (freq[i] < min_freq) min_freq = freq[i];
        }
    }
    
    free(freq);
    return max_freq - min_freq;
}

int main(void) {
    int arr[] = {1, 2, 2, 3, 3, 3, 4, 4, 4, 4};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    
    int result = find_frequency_difference(arr, size);
    if (result >= 0) {
        printf("Difference: %d\n", result);
    } else {
        fprintf(stderr, "Error: Invalid input or memory allocation failed\n");
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}