#include <stdio.h>
#include <stdlib.h>

int find_last_occurrence(const int *arr, size_t size, int target) {
    if (arr == NULL || size == 0) {
        return -1;
    }

    size_t low = 0;
    size_t high = size - 1;
    int result = -1;

    while (low <= high) {
        size_t mid = low + (high - low) / 2;

        if (arr[mid] == target) {
            result = (int)mid;
            low = mid + 1;
        } else if (arr[mid] < target) {
            low = mid + 1;
        } else {
            if (mid == 0) {
                break;
            }
            high = mid - 1;
        }
    }

    return result;
}

int main(void) {
    int arr[] = {1, 2, 2, 2, 3, 4, 5, 5, 5, 6};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    int target = 5;

    int index = find_last_occurrence(arr, size, target);

    printf("%d\n", index);

    return 0;
}