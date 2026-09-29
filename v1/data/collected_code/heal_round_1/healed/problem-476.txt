#include <stdio.h>

int sumOfLargestAndSmallest(const int arr[], int n) {
    int min = arr[0];
    int max = arr[0];
    
    for (int i = 1; i < n; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
        else if (arr[i] > max) {
            max = arr[i];
        }
    }
    
    return min + max;
}

int main() {
    int arr[] = {3, 7, 2, 9, -1};
    int size = sizeof(arr) / sizeof(arr[0]);
    
    int result = sumOfLargestAndSmallest(arr, size);
    
    printf("Sum of the largest and smallest value: %d\n", result);
    
    return 0;
}