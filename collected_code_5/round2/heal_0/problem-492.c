#include<stdio.h>

int binarySearch(int arr[], int low, int high, int element) {
    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] == element)
            return mid;

        if (arr[mid] < element)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}

int main(void) {
    int arr[] = {2, 3, 4, 10, 40};
    int size = sizeof(arr)/sizeof(arr[0]);
    int element = 10;
    int result = binarySearch(arr, 0, size-1, element);
    if(result == -1) 
        printf("Element is not present in array\n");
    else
        printf("Element is present at index %d\n", result);
    return 0;
}