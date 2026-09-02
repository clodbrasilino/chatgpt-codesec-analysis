#include <stdio.h>

int findSmallestMissing(const int arr[], int size) {
    int left = 0;
    int right = size - 1;
    int expected = 0;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == mid) {
            left = mid + 1;
            expected = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return expected;
}

int main(void) {
    int arr1[] = {0, 1, 2, 3, 4, 5};
    int arr2[] = {0, 1, 2, 4, 5, 6};
    int arr3[] = {1, 2, 3, 4, 5};
    int arr4[] = {0, 1, 2, 3, 5};
    int arr5[] = {0, 2, 3, 4, 5};
    int arr6[] = {0};

    printf("arr1: %d\n", findSmallestMissing(arr1, 6));
    printf("arr2: %d\n", findSmallestMissing(arr2, 6));
    printf("arr3: %d\n", findSmallestMissing(arr3, 5));
    printf("arr4: %d\n", findSmallestMissing(arr4, 5));
    printf("arr5: %d\n", findSmallestMissing(arr5, 5));
    printf("arr6: %d\n", findSmallestMissing(arr6, 1));

    return 0;
}