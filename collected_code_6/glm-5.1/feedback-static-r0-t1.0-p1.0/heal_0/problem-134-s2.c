#include <stdio.h>
#include <stdlib.h>

int check_last_element(int *array, size_t size, int p) {
    if (array == NULL || size == 0) {
        return -1;
    }

    if (p < 0) {
        return -1;
    }

    long long last_element = (long long)array[size - 1];

    for (int i = 0; i < p; i++) {
        last_element = last_element * last_element;
    }

    return (last_element % 2 == 0) ? 0 : 1;
}

int main(void) {
    int arr1[] = {1, 2, 3, 4};
    size_t size1 = sizeof(arr1) / sizeof(arr1[0]);
    int p1 = 2;
    int result1 = check_last_element(arr1, size1, p1);
    printf("%d\n", result1);

    int arr2[] = {1, 2, 3, 5};
    size_t size2 = sizeof(arr2) / sizeof(arr2[0]);
    int p2 = 3;
    int result2 = check_last_element(arr2, size2, p2);
    printf("%d\n", result2);

    int *arr3 = NULL;
    size_t size3 = 0;
    int p3 = 1;
    int result3 = check_last_element(arr3, size3, p3);
    printf("%d\n", result3);

    return 0;
}