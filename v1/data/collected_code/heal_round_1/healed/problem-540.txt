#include <stdio.h>

int findMax(const int arr[], int size) {
    int max = arr[0];
    for(int i = 1; i < size; i++) {
        if(arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

int findMin(const int arr[], int size) {
    int min = arr[0];
    for(int i = 1; i < size; i++) {
        if(arr[i] < min) {
            min = arr[i];
        }
    }
    return min;
}

int findDifference(const int arr[], int size) {
    int maxVal = findMax(arr, size);
    int minVal = findMin(arr, size);
    int maxCount = 0;
    int minCount = 0;
    
    for(int i = 0; i < size; i++) {
        if(arr[i] == maxVal) {
            maxCount++;
        }
        if(arr[i] == minVal) {
            minCount++;
        }
    }
    
    return maxCount - minCount;
}

int main() {
    int arr[] = {2, 2, 3, 4, 4, 4, 5, 5, 5, 5};
    int size = sizeof(arr) / sizeof(arr[0]);
    
    int difference = findDifference(arr, size);
    printf("Difference between highest and least frequencies: %d", difference);
    
    return 0;
}