#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool binary_search(const int *arr, size_t size, int target) {
    if (arr == NULL || size == 0) {
        return false;
    }

    size_t left = 0;
    size_t right = size - 1;

    while (left <= right) {
        size_t mid = left + (right - left) / 2;

        if (arr[mid] == target) {
            return true;
        }

        if (arr[mid] < target) {
            left = mid + 1;
        } else {
            if (mid == 0) {
                break;
            }
            right = mid - 1;
        }
    }

    return false;
}

int main(void) {
    int arr[] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    
    printf("%s\n", binary_search(arr, size, 12) ? "True" : "False");
    printf("%s\n", binary_search(arr, size, 5) ? "True" : "False");
    printf("%s\n", binary_search(arr, size, 20) ? "True" : "False");

    return 0;
}