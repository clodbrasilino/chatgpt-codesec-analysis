#include <stdio.h>
#include <stdlib.h>

int find_first_position(const int *arr, size_t size, int target) {
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
            if (mid == 0) {
                break;
            }
            high = mid - 1;
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
    int arr1[] = {1, 2, 2, 2, 3, 4, 5};
    size_t size1 = sizeof(arr1) / sizeof(arr1[0]);
    int target1 = 2;
    int pos1 = find_first_position(arr1, size1, target1);
    printf("%d\n", pos1);

    int arr2[] = {10, 20, 30, 40, 50};
    size_t size2 = sizeof(arr2) / sizeof(arr2[0]);
    int target2 = 25;
    int pos2 = find_first_position(arr2, size2, target2);
    printf("%d\n", pos2);

    int arr3[] = {5, 5, 5, 5, 5};
    size_t size3 = sizeof(arr3) / sizeof(arr3[0]);
    int target3 = 5;
    int pos3 = find_first_position(arr3, size3, target3);
    printf("%d\n", pos3);

    int pos4 = find_first_position(NULL, 0, 5);
    printf("%d\n", pos4);

    return 0;
}