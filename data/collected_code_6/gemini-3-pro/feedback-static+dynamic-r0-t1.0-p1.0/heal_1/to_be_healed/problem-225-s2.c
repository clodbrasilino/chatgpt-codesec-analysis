#include <stdio.h>
#include <stdlib.h>

int findMin(int arr[], int low, int high) {
    if (high < low) {
        return arr[0];
    }
    if (high == low) {
        return arr[low];
    }

    int mid = low + (high - low) / 2;

    if (mid < high && arr[mid + 1] < arr[mid]) {
        return arr[mid + 1];
    }

    if (mid > low && arr[mid] < arr[mid - 1]) {
        return arr[mid];
    }

    if (arr[high] > arr[mid]) {
        return findMin(arr, low, mid - 1);
    }

    return findMin(arr, mid + 1, high);
}

int main() {
    int arr[] = {5, 6, 1, 2, 3, 4};
    /* Possible weaknesses found:
     *  Assignment 'n=sizeof(arr)/sizeof(arr[0])', assigned value is 6
     */
    int n = sizeof(arr) / sizeof(arr[0]);
    
    /* Possible weaknesses found:
     *  Condition 'n==0' is always false
     *  Condition 'n==0' is always false [knownConditionTrueFalse]
     */
    if (n == 0) {
        printf("Array is empty\n");
        return 1;
    }

    int minElement = findMin(arr, 0, n - 1);
    printf("The minimum element is %d\n", minElement);

    return 0;
}