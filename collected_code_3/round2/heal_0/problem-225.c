#include <stdio.h>

int findMin(int arr[], int low, int high) {
    if (high < low) return arr[0];
    if (high == low) return arr[low];
    int mid = low + (high - low)/2;
    if (mid < high && arr[mid+1] < arr[mid]) return arr[mid+1];
    if (mid > low && arr[mid] < arr[mid - 1]) return arr[mid];
    if (arr[high] > arr[mid]) return findMin(arr, low, mid-1);
    return findMin(arr, mid+1, high);
}

int main() {
    int arr1[] =  {5, 6, 1, 2, 3, 4};
    int n1 = sizeof(arr1)/sizeof(arr1[0]);
    printf("The minimum element is %d\n", findMin(arr1, 0, n1-1));
    int arr2[] =  {1, 2, 3, 4};
    int n2 = sizeof(arr2)/sizeof(arr2[0]);
    printf("The minimum element is %d\n", findMin(arr2, 0, n2-1));
    int arr3[] =  {1};
    int n3 = sizeof(arr3)/sizeof(arr3[0]);
    printf("The minimum element is %d\n", findMin(arr3, 0, n3-1));
    return 0;
}