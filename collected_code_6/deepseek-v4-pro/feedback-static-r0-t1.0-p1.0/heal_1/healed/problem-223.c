#include <stdio.h>
#include <stdlib.h>

int isMajorityElement(const int arr[], int n, int x) {
    if (arr == NULL || n <= 0) {
        return 0;
    }

    int first = -1;
    int left = 0, right = n - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == x) {
            first = mid;
            right = mid - 1;
        } else if (arr[mid] < x) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    if (first == -1) {
        return 0;
    }

    if (first + n / 2 < n && arr[first + n / 2] == x) {
        return 1;
    }

    return 0;
}

int main(void) {
    int arr1[] = {1, 2, 3, 3, 3, 3, 10};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    int x1 = 3;

    if (isMajorityElement(arr1, n1, x1)) {
        printf("%d is a majority element\n", x1);
    } else {
        printf("%d is not a majority element\n", x1);
    }

    int arr2[] = {1, 1, 2, 2, 2, 2, 3};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    int x2 = 2;

    if (isMajorityElement(arr2, n2, x2)) {
        printf("%d is a majority element\n", x2);
    } else {
        printf("%d is not a majority element\n", x2);
    }

    int arr3[] = {1, 2, 3, 4, 5};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    int x3 = 3;

    if (isMajorityElement(arr3, n3, x3)) {
        printf("%d is a majority element\n", x3);
    } else {
        printf("%d is not a majority element\n", x3);
    }

    if (isMajorityElement(NULL, 5, 1)) {
        printf("1 is a majority element\n");
    } else {
        printf("1 is not a majority element\n");
    }

    return 0;
}