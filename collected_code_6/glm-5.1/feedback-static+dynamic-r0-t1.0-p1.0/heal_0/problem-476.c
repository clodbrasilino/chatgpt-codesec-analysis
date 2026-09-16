#include <stdio.h>
#include <limits.h>

int sum_min_max(const int *array, size_t size) {
    if (array == NULL || size == 0) {
        return 0;
    }

    int min_val = INT_MAX;
    int max_val = INT_MIN;

    for (size_t i = 0; i < size; i++) {
        if (array[i] < min_val) {
            min_val = array[i];
        }
        if (array[i] > max_val) {
            max_val = array[i];
        }
    }

    return min_val + max_val;
}

int main(void) {
    int arr1[] = {5, 2, 9, 1, 7};
    size_t size1 = sizeof(arr1) / sizeof(arr1[0]);
    printf("%d\n", sum_min_max(arr1, size1));

    int arr2[] = {-10, 0, 50, 20};
    size_t size2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("%d\n", sum_min_max(arr2, size2));

    int arr3[] = {42};
    size_t size3 = sizeof(arr3) / sizeof(arr3[0]);
    printf("%d\n", sum_min_max(arr3, size3));

    printf("%d\n", sum_min_max(NULL, 0));

    return 0;
}