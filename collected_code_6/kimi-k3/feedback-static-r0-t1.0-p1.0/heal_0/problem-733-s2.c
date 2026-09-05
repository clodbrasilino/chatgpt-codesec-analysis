#include <stdio.h>

int find_first_occurrence(const int *array, size_t size, int target) {
    size_t left = 0;
    size_t right = size;
    size_t result = size;

    if (array == NULL) {
        return -1;
    }

    while (left < right) {
        size_t mid = left + (right - left) / 2;

        if (array[mid] < target) {
            left = mid + 1;
        } else {
            if (array[mid] == target) {
                result = mid;
            }
            right = mid;
        }
    }

    if (result == size) {
        return -1;
    }

    return (int)result;
}

int main(void) {
    int array[] = {1, 2, 2, 2, 3, 4, 5};
    size_t size = sizeof(array) / sizeof(array[0]);
    int target = 2;
    int index = find_first_occurrence(array, size, target);

    if (index >= 0) {
        printf("First occurrence of %d is at index %d\n", target, index);
    } else {
        printf("%d not found in the array\n", target);
    }

    return 0;
}