#include <stdio.h>
#include <stdlib.h>

int all_different(const int *array, size_t size) {
    if (array == NULL) {
        return 0;
    }

    for (size_t i = 0; i < size; i++) {
        for (size_t j = i + 1; j < size; j++) {
            if (array[i] == array[j]) {
                return 0;
            }
        }
    }

    return 1;
}

int main(void) {
    int arr1[] = {1, 2, 3, 4, 5};
    size_t len1 = sizeof(arr1) / sizeof(arr1[0]);

    int arr2[] = {1, 2, 3, 4, 5, 1};
    size_t len2 = sizeof(arr2) / sizeof(arr2[0]);

    int arr3[] = {7};
    size_t len3 = sizeof(arr3) / sizeof(arr3[0]);

    printf("%d\n", all_different(arr1, len1));
    printf("%d\n", all_different(arr2, len2));
    printf("%d\n", all_different(arr3, len3));
    printf("%d\n", all_different(NULL, len1));

    return 0;
}