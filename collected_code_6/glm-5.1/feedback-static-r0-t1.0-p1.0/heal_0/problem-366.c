#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int largest_adjacent_product(const int *array, size_t size) {
    if (array == NULL || size < 2) {
        return 0;
    }

    int max_product = INT_MIN;

    for (size_t i = 0; i < size - 1; i++) {
        int product = array[i] * array[i + 1];
        if (product > max_product) {
            max_product = product;
        }
    }

    return max_product;
}

int main(void) {
    int arr1[] = {3, 6, -2, -5, 7, 3};
    size_t size1 = sizeof(arr1) / sizeof(arr1[0]);
    int result1 = largest_adjacent_product(arr1, size1);
    printf("%d\n", result1);

    int arr2[] = {-1, -2, -3, -4};
    size_t size2 = sizeof(arr2) / sizeof(arr2[0]);
    int result2 = largest_adjacent_product(arr2, size2);
    printf("%d\n", result2);

    int arr3[] = {5};
    size_t size3 = sizeof(arr3) / sizeof(arr3[0]);
    int result3 = largest_adjacent_product(arr3, size3);
    printf("%d\n", result3);

    return 0;
}