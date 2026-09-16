#include <stdio.h>
#include <stdlib.h>

size_t find_left_insertion_point(const int *arr, size_t size, int target) {
    if (arr == NULL || size == 0) {
        return 0;
    }

    size_t left = 0;
    size_t right = size;

    while (left < right) {
        size_t mid = left + (right - left) / 2;
        if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }

    return left;
}

int main(void) {
    int arr[] = {1, 2, 4, 4, 4, 6, 8};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    int target = 4;

    size_t index = find_left_insertion_point(arr, size, target);
    
    printf("%zu\n", index);

    return 0;
}