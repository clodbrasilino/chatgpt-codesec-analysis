#include <stdio.h>
#include <stdlib.h>

int countRotations(const int arr[], int n) {
    if (arr == NULL || n <= 0) {
        return -1;
    }
    
    int low = 0;
    int high = n - 1;
    
    while (low <= high) {
        if (arr[low] <= arr[high]) {
            return low;
        }
        
        int mid = low + (high - low) / 2;
        int next = (mid + 1) % n;
        int prev = (mid + n - 1) % n;
        
        if (arr[mid] <= arr[next] && arr[mid] <= arr[prev]) {
            return mid;
        }
        
        if (arr[mid] <= arr[high]) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    
    return 0;
}

int main(void) {
    int arr[] = {15, 18, 2, 3, 6, 12};
    int n = (int)(sizeof(arr) / sizeof(arr[0]));
    
    int rotations = countRotations(arr, n);
    
    if (rotations >= 0) {
        printf("Number of rotations: %d\n", rotations);
    } else {
        printf("Invalid input\n");
    }
    
    return 0;
}