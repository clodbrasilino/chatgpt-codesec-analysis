#include <stdio.h>
#include <stdlib.h>

int find_min(const int arr[], int n) {
    if (n <= 0) {
        return -1;
    }

    int low = 0;
    int high = n - 1;

    while (low < high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] > arr[high]) {
            low = mid + 1;
        } else if (arr[mid] < arr[high]) {
            high = mid;
        } else {
            high--;
        }
    }

    return arr[low];
}

int main() {
    int arr1[] = {5, 6, 1, 2, 3, 4};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    printf("%d\n", find_min(arr1, n1));

    int arr2[] = {1, 2, 3, 4};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("%d\n", find_min(arr2, n2));

    int arr3[] = {1};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    printf("%d\n", find_min(arr3, n3));

    int arr4[] = {2, 1};
    int n4 = sizeof(arr4) / sizeof(arr4[0]);
    printf("%d\n", find_min(arr4, n4));

    int arr5[] = {3, 3, 1, 3};
    int n5 = sizeof(arr5) / sizeof(arr5[0]);
    printf("%d\n", find_min(arr5, n5));

    return 0;
}