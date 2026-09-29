#include <stdio.h>
#include <stdlib.h>

int findInsertionPoint(const int *arr, int size, int value) {
    if (arr == NULL || size < 0) {
        return -1;
    }

    int left = 0;
    int right = size - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == value) {
            return mid + 1;
        } else if (arr[mid] < value) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return left;
}

int main(void) {
    int arr[] = {1, 3, 5, 7, 9};
    int size = sizeof(arr) / sizeof(arr[0]);
    int valuesToInsert[] = {0, 4, 9, 10};
    int numValues = sizeof(valuesToInsert) / sizeof(valuesToInsert[0]);

    for (int i = 0; i < numValues; i++) {
        int value = valuesToInsert[i];
        int pos = findInsertionPoint(arr, size, value);
        if (pos != -1) {
            printf("Value %d should be inserted at index %d\n", value, pos);
        } else {
            printf("Error finding insertion point for %d\n", value);
        }
    }

    return 0;
}