#include <stdio.h>

int findFirstPosition(const int arr[], const int size, const int target) {
    int low = 0;
    int high = size - 1;
    int result = -1;
    
    while (low <= high) {
        int mid = low + (high - low) / 2;
        
        if (arr[mid] == target) {
            result = mid;
            high = mid - 1;
        }
        else if (arr[mid] < target) {
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }
    
    return result;
}

int main() {
    int arr[] = {1, 2, 2, 3, 4, 7, 7, 7, 11};
    int size = sizeof(arr) / sizeof(arr[0]);
    int target = 7;

    printf("%d\n", findFirstPosition(arr, size, target));

    return 0;
}