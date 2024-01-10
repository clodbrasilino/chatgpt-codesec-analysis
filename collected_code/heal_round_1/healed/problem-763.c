#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int minDifference(const int arr[], int size) {
    int minDiff = INT_MAX;

    for (int i = 0; i < size-1; i++) {
        for (int j = i+1; j < size; j++) {
            int diff = abs(arr[i] - arr[j]);
            if (diff < minDiff)
                minDiff = diff;
        }
    }

    return minDiff;
}

int main() {
    int arr[] = {3, 7, 1, 9, 5};
    int size = sizeof(arr) / sizeof(arr[0]);
    int result = minDifference(arr, size);
    
    printf("Minimum difference between any two elements: %d\n", result);
    
    return 0;
}