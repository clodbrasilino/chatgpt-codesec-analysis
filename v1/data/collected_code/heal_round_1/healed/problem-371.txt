#include <stdio.h>

int findSmallestMissingElement(const int arr[], int size) {
    int low = 0;
    int high = size - 1;

    if (arr[low] != 0) {
        return 0;
    }

    while (low <= high) {
        int mid = low + (high - low) / 2;
      
        if (arr[mid] - arr[low] > 1) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
  
    return arr[low] - 1;
}

int main() {
    const int arr[] = {0, 1, 2, 3, 5, 6};
    int size = sizeof(arr) / sizeof(arr[0]);

    int smallest = findSmallestMissingElement(arr, size);

    printf("The smallest missing element is %d\n", smallest);
  
    return 0;
}