#include <stdio.h>
#include <stddef.h>

size_t find_first_position(const int *arr, size_t len, int target) {
    if (arr == NULL || len == 0) {
        return (size_t)-1;
    }
    size_t low = 0;
    size_t high = len - 1;
    size_t result = (size_t)-1;
    while (low <= high) {
        size_t mid = low + (high - low) / 2;
        if (arr[mid] == target) {
            result = mid;
            if (mid == 0) {
                break;
            }
            high = mid - 1;
        } else if (arr[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return result;
}

int main(void) {
    int arr[] = {1, 2, 2, 2, 3, 4, 5, 5, 6};
    size_t len = sizeof(arr) / sizeof(arr[0]);
    int target = 2;
    size_t pos = find_first_position(arr, len, target);
    if (pos != (size_t)-1) {
        printf("%zu\n", pos);
    } else {
        printf("Not found\n");
    }
    return 0;
}