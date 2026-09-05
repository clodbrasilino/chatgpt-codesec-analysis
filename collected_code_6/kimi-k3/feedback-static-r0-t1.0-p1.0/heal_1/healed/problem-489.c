#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int findMaxFrequency(const int arr[], int size) {
    if (arr == NULL || size <= 0) {
        return -1;
    }

    int max = INT_MIN;
    int frequency = 0;

    for (int i = 0; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
            frequency = 1;
        } else if (arr[i] == max) {
            frequency++;
        }
    }

    return frequency;
}

int main(void) {
    int arr[] = {4, 2, 8, 8, 3, 8, 1};
    int size = sizeof(arr) / sizeof(arr[0]);
    
    int result = findMaxFrequency(arr, size);
    
    if (result != -1) {
        printf("Frequency of largest value: %d\n", result);
    } else {
        printf("Invalid input\n");
    }
    
    return 0;
}