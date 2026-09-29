#include <stdio.h>

int maxDifference(int arr[], int size) {
    int maxDiff = 0;
    
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (arr[j] - arr[i] > maxDiff) {
                maxDiff = arr[j] - arr[i];
            }
        }
    }
    
    return maxDiff;
}

int main() {
    int arr[] = {5, 10, 2, 7, 6, 15};
    int size = sizeof(arr) / sizeof(arr[0]);
    int result = maxDifference(arr, size);
    
    printf("Maximum difference: %d\n", result);
    
    return 0;
}