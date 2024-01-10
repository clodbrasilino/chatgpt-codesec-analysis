#include<stdio.h>

int findLastPosition(const int arr[], int n, int element) {
    int low = 0;
    int high = n-1;
    int result = -1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
  
        if (arr[mid] == element) {
            result = mid;
            low = mid + 1;
        }
        else if (arr[mid] < element) {
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }

    return result;
}

int main() {
    int arr[] = {2, 6, 8, 10, 10, 13, 16};
    int n = sizeof(arr) / sizeof(arr[0]);
    int element = 10;
    int lastPosition = findLastPosition(arr, n, element);

    if (lastPosition != -1) {
        printf("Last position of element %d is %d\n", element, lastPosition);
    }
    else {
        printf("Element %d not found in the array\n", element);
    }

    return 0;
}