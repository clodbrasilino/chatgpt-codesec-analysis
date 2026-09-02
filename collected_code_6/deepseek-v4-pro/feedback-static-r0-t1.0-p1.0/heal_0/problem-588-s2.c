#include <stdio.h>
#include <limits.h>

int find_difference(const int arr[], int size) {
    if (size <= 0) {
        return 0;
    }
    
    int min = INT_MAX;
    int max = INT_MIN;
    
    for (int i = 0; i < size; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    
    return max - min;
}

int main(void) {
    int arr[] = {5, 2, 9, 1, 7, 3, 8};
    int size = sizeof(arr) / sizeof(arr[0]);
    
    int diff = find_difference(arr, size);
    printf("Difference between largest and smallest: %d\n", diff);
    
    return 0;
}