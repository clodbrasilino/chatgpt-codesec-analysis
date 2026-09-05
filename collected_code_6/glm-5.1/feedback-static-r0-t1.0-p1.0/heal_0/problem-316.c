#include <stdio.h>
#include <stdlib.h>

int find_last_occurrence(int *array, size_t size, int target) {
    if (array == NULL || size == 0) {
        return -1;
    }

    size_t low = 0;
    size_t high = size - 1;
    int result = -1;

    while (low <= high) {
        size_t mid = low + (high - low) / 2;

        if (array[mid] == target) {
            result = (int)mid;
            low = mid + 1;
        } else if (array[mid] < target) {
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
    int index1 = find_last_occurrence(arr1, size1, target1);
    printf("%d\n", index1);

    int arr2[] = {1, 1, 1, 1, 1};
    size_t size2 = sizeof(arr2) / sizeof(arr2[0]);
    int target2 = 1;
    int index2 = find_last_occurrence(arr2, size2, target2);
    printf("%d\n", index2);

    int arr3[] = {1, 2, 3, 4, 5};
    size_t size3 = sizeof(arr3) / sizeof(arr3[0]);
    int target3 = 6;
    int index3 = find_last_occurrence(arr3, size3, target3);
    printf("%d\n", index3);

    int index4 = find_last_occurrence(NULL, 0, 5);
    printf("%d\n", index4);

    return 0;
}