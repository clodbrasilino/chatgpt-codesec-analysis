#include <stdio.h>
#include <stdlib.h>

int binary_search(const int *arr, size_t size, int target) {
    if (arr == NULL || size == 0) {
        return 0;
    }

    size_t left = 0;
    size_t right = size;

    while (left < right) {
        size_t mid = left + (right - left) / 2;

        if (arr[mid] == target) {
            return 1;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }

    return 0;
}

int main(void) {
    int array[] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20};
    size_t size = sizeof(array) / sizeof(array[0]);
    int target = 14;

    int result = binary_search(array, size, target);

    if (result) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    return 0;
}