#include <stdio.h>
#include <stdlib.h>

int min_add_to_even(const int *arr, size_t size) {
    if (arr == NULL || size == 0) {
        return -1;
    }

    int sum = 0;
    for (size_t i = 0; i < size; i++) {
        sum += arr[i];
    }

    if (sum % 2 == 0) {
        return 0;
    }

    return 1;
}

int main(void) {
    int arr1[] = {1, 2, 3, 4, 5};
    size_t size1 = sizeof(arr1) / sizeof(arr1[0]);
    int res1 = min_add_to_even(arr1, size1);
    printf("%d\n", res1);

    int arr2[] = {2, 4, 6};
    size_t size2 = sizeof(arr2) / sizeof(arr2[0]);
    int res2 = min_add_to_even(arr2, size2);
    printf("%d\n", res2);

    const int *arr3 = NULL;
    int res3 = min_add_to_even(arr3, 0);
    printf("%d\n", res3);

    return 0;
}