#include <stdio.h>
#include <stdlib.h>

int positive_count(const int *array, size_t size) {
    int count = 0;
    for (size_t i = 0; i < size; i++) {
        if (array[i] > 0) {
            count++;
        }
    }
    return count;
}

double find_ratio(const int *array, size_t size) {
    if (size == 0) {
        return 0.0;
    }
    return (double)positive_count(array, size) / (double)size;
}

int main(void) {
    const int arr1[] = {1, -2, 3, -4, 5};
    size_t size1 = sizeof(arr1) / sizeof(arr1[0]);
    printf("%f\n", find_ratio(arr1, size1));

    const int arr2[] = {-1, -2, -3};
    size_t size2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("%f\n", find_ratio(arr2, size2));

    const int arr3[] = {};
    size_t size3 = 0;
    printf("%f\n", find_ratio(arr3, size3));

    return 0;
}