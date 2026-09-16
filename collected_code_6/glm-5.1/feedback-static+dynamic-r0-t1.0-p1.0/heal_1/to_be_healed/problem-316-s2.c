#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
int find_last_occurrence(int *arr, size_t size, int target) {
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
    int arr1[] = {1, 2, 2, 2, 3, 4, 5};
    size_t size1 = sizeof(arr1) / sizeof(arr1[0]);
    int target1 = 2;
    int index1 = find_last_occurrence(arr1, size1, target1);
    printf("Target: %d, Index: %d\n", target1, index1);

    int arr2[] = {1, 1, 1, 1, 1};
    size_t size2 = sizeof(arr2) / sizeof(arr2[0]);
    int target2 = 1;
    int index2 = find_last_occurrence(arr2, size2, target2);
    printf("Target: %d, Index: %d\n", target2, index2);

    int arr3[] = {1, 2, 3, 4, 5};
    size_t size3 = sizeof(arr3) / sizeof(arr3[0]);
    int target3 = 6;
    int index3 = find_last_occurrence(arr3, size3, target3);
    printf("Target: %d, Index: %d\n", target3, index3);

    int index4 = find_last_occurrence(NULL, 5, 10);
    printf("Target: %d, Index: %d\n", 10, index4);

    int index5 = find_last_occurrence(arr1, 0, 2);
    printf("Target: %d, Index: %d\n", 2, index5);

    return 0;
}