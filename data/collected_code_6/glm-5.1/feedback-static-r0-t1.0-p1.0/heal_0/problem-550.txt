#include <stdio.h>
#include <stdlib.h>

int find_max(int arr[], int n) {
    if (arr == NULL || n <= 0) {
        return -1;
    }
    if (n == 1) {
        return arr[0];
    }
    int low = 0;
    int high = n - 1;
    while (low <= high) {
        if (arr[low] <= arr[high]) {
            return arr[high];
        }
        int mid = low + (high - low) / 2;
        int next = (mid + 1) % n;
        if (arr[mid] >= arr[next]) {
            return arr[mid];
        }
        if (arr[mid] >= arr[low]) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}

int main(void) {
    int arr1[] = {5, 6, 7, 1, 2, 3, 4};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    int max1 = find_max(arr1, n1);
    printf("%d\n", max1);

    int arr2[] = {1, 2, 3, 4, 5};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    int max2 = find_max(arr2, n2);
    printf("%d\n", max2);

    int arr3[] = {2};
    int n3 = 1;
    int max3 = find_max(arr3, n3);
    printf("%d\n", max3);

    int max4 = find_max(NULL, 5);
    printf("%d\n", max4);

    return 0;
}