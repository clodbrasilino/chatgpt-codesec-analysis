#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int find_max_difference(int *array, size_t size) {
    if (array == NULL) {
        return -1;
    }
    
    if (size < 2) {
        return 0;
    }

    int min_element = array[0];
    int max_difference = array[1] - array[0];

    for (size_t i = 1; i < size; i++) {
        int current_diff = array[i] - min_element;
        if (current_diff > max_difference) {
            max_difference = current_diff;
        }
        if (array[i] < min_element) {
            min_element = array[i];
        }
    }

    return max_difference;
}

int main(void) {
    int arr1[] = {2, 3, 10, 6, 4, 8, 1};
    size_t size1 = sizeof(arr1) / sizeof(arr1[0]);
    int result1 = find_max_difference(arr1, size1);
    printf("%d\n", result1);

    int arr2[] = {7, 9, 5, 6, 3, 2};
    size_t size2 = sizeof(arr2) / sizeof(arr2[0]);
    int result2 = find_max_difference(arr2, size2);
    printf("%d\n", result2);

    int arr3[] = {10, 10, 10};
    size_t size3 = sizeof(arr3) / sizeof(arr3[0]);
    int result3 = find_max_difference(arr3, size3);
    printf("%d\n", result3);

    int *arr4 = NULL;
    size_t size4 = 0;
    int result4 = find_max_difference(arr4, size4);
    printf("%d\n", result4);

    return 0;
}