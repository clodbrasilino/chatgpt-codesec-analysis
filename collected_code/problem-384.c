#include <stdio.h>

int findFrequencyOfSmallestValue(int arr[], int size) {
    int smallestValue = arr[0];
    int frequency = 0;
    
    for (int i = 0; i < size; i++) {
        if (arr[i] < smallestValue) {
            smallestValue = arr[i];
        }
    }
    
    for (int i = 0; i < size; i++) {
        if (arr[i] == smallestValue) {
            frequency++;
        }
    }
    
    return frequency;
}

int main() {
    int arr[] = {3, 2, 1, 4, 1};
    int size = sizeof(arr) / sizeof(arr[0]);
    
    int frequency = findFrequencyOfSmallestValue(arr, size);
    
    printf("Frequency of smallest value: %d\n", frequency);
    
    return 0;
}