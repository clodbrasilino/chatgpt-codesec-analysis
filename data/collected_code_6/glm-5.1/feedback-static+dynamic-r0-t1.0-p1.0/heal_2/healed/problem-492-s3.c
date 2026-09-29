#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool binary_search(const int *arr, size_t size, int target) {
    if (arr == NULL || size == 0) {
        return false;
    }

    size_t left = 0;
    size_t right = size;

    while (left < right) {
        size_t mid = left + (right - left) / 2;

        if (arr[mid] == target) {
            return true;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }

    return false;
}

int main(void) {
    int arr[] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20};
    size_t size = sizeof(arr) / sizeof(arr[0]);

    int target1 = 12;
    bool result1 = binary_search(arr, size, target1);

    if (result1) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    int target2 = 5;
    bool result2 = binary_search(arr, size, target2);

    if (result2) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    return 0;
}