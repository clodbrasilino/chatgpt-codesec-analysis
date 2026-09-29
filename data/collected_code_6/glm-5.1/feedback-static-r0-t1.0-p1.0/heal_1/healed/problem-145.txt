#include <stdio.h>
#include <stdlib.h>

int find_max_difference(const int *array, size_t size) {
    if (array == NULL || size < 2) {
        return -1;
    }

    int min_val = array[0];
    int max_val = array[0];

    for (size_t i = 1; i < size; i++) {
        if (array[i] < min_val) {
            min_val = array[i];
        } else if (array[i] > max_val) {
            max_val = array[i];
        }
    }

    return max_val - min_val;
}

int main(void) {
    int arr1[] = {2, 3, 1, 7, 9, 5, 11, 6};
    size_t size1 = sizeof(arr1) / sizeof(arr1[0]);
    int result1 = find_max_difference(arr1, size1);
    printf("%d\n", result1);

    int arr2[] = {5};
    size_t size2 = sizeof(arr2) / sizeof(arr2[0]);
    int result2 = find_max_difference(arr2, size2);
    printf("%d\n", result2);

    int *arr3 = NULL;
    size_t size3 = 5;
    int result3 = find_max_difference(arr3, size3);
    printf("%d\n", result3);

    return 0;
}