#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int findFrequencyDifference(const int arr[], int size) {
    if (arr == NULL || size <= 0) {
        return -1;
    }

    int max_val = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max_val) {
            max_val = arr[i];
        } else if (arr[i] < 0) {
            return -1;
        }
    }

    int *freq = (int *)calloc(max_val + 1, sizeof(int));
    if (freq == NULL) {
        return -1;
    }

    for (int i = 0; i < size; i++) {
        freq[arr[i]]++;
    }

    int highest = 0;
    int least = INT_MAX;

    for (int i = 0; i <= max_val; i++) {
        if (freq[i] > 0) {
            if (freq[i] > highest) highest = freq[i];
            if (freq[i] < least) least = freq[i];
        }
    }

    free(freq);
    return highest - least;
}

int main(void) {
    int arr[] = {1, 2, 2, 3, 3, 3, 4, 4, 4, 4};
    int size = sizeof(arr) / sizeof(arr[0]);

    int result = findFrequencyDifference(arr, size);
    
    if (result != -1) {
        printf("Difference between highest and least frequency: %d\n", result);
    } else {
        printf("Error: Invalid array or memory allocation failure.\n");
    }

    return 0;
}