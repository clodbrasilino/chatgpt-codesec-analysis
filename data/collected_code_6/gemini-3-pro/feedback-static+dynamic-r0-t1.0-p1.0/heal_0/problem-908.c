#include <stdio.h>
#include <stdlib.h>

int find_fixed_point(const int *arr, size_t size) {
    if (arr == NULL) {
        return -1;
    }

    size_t low = 0;
    size_t high = size > 0 ? size - 1 : 0;

    if (size == 0) {
        return -1;
    }

    while (low <= high) {
        size_t mid = low + (high - low) / 2;

        if (arr[mid] == (int)mid) {
            return (int)mid;
        } else if (arr[mid] < (int)mid) {
            low = mid + 1;
        } else {
            if (mid == 0) {
                break;
            }
            high = mid - 1;
        }
    }

    return -1;
}

int main(void) {
    int arr[] = {-10, -5, 0, 3, 7};
    size_t size = sizeof(arr) / sizeof(arr[0]);

    int fixed_point = find_fixed_point(arr, size);

    if (fixed_point != -1) {
        printf("Fixed point is %d\n", fixed_point);
    } else {
        printf("No fixed point found\n");
    }

    return 0;
}