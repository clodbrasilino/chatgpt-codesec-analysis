#include <stdio.h>
#include <stdbool.h>

bool is_sorted(const int *list, size_t size) {
    if (list == NULL || size <= 1) {
        return true;
    }

    for (size_t i = 0; i < size - 1; i++) {
        if (list[i] > list[i + 1]) {
            return false;
        }
    }

    return true;
}

int main(void) {
    int arr1[] = {1, 2, 3, 4, 5};
    size_t size1 = sizeof(arr1) / sizeof(arr1[0]);

    int arr2[] = {5, 3, 1, 4, 2};
    size_t size2 = sizeof(arr2) / sizeof(arr2[0]);

    int arr3[] = {10};
    size_t size3 = sizeof(arr3) / sizeof(arr3[0]);

    printf("%d\n", is_sorted(arr1, size1));
    printf("%d\n", is_sorted(arr2, size2));
    printf("%d\n", is_sorted(arr3, size3));
    printf("%d\n", is_sorted(NULL, 0));

    return 0;
}