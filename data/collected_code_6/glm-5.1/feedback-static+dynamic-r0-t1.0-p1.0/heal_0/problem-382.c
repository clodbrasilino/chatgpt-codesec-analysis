#include <stdio.h>
#include <stdlib.h>

int find_rotations(int *arr, int n) {
    if (arr == NULL || n <= 0) {
        return -1;
    }
    if (n == 1) {
        return 0;
    }
    int low = 0;
    int high = n - 1;
    while (low <= high) {
        if (arr[low] <= arr[high]) {
            return low;
        }
        int mid = low + (high - low) / 2;
        int prev = (mid - 1 + n) % n;
        int next = (mid + 1) % n;
        if (arr[mid] <= arr[prev] && arr[mid] <= arr[next]) {
            return mid;
        }
        if (arr[mid] <= arr[high]) {
            high = mid - 1;
        } else if (arr[mid] >= arr[low]) {
            low = mid + 1;
        }
    }
    return 0;
}

int main(void) {
    int arr1[] = {8, 9, 10, 2, 5, 6};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    int res1 = find_rotations(arr1, n1);
    printf("%d\n", res1);

    int arr2[] = {1, 2, 3, 4, 5};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    int res2 = find_rotations(arr2, n2);
    printf("%d\n", res2);

    int arr3[] = {2, 1};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    int res3 = find_rotations(arr3, n3);
    printf("%d\n", res3);

    int *arr4 = NULL;
    int res4 = find_rotations(arr4, 0);
    printf("%d\n", res4);

    return 0;
}