#include<stdio.h>

int findIndex(int arr[], int n, int target) {
    int start = 0;
    int end = n - 1;
   
    while (start <= end) {
        int mid = start + (end - start) / 2;

        if (arr[mid] == target) {
            return mid;
        }

        if (arr[mid] < target) {
            start = mid + 1;
        }
        else {
            end = mid - 1;
        }
    }

    return -1;
}

int main() {
    int arr[] = {2, 10, 15, 30, 45, 55, 60, 90};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 30;

    int index = findIndex(arr, n, target);

    if (index != -1) {
        printf("Element %d found at index %d\n", target, index);
    }
    else {
        printf("Element %d not found in the array\n", target);
    }

    return 0;
}