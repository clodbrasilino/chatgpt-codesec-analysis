#include <stdio.h>
#include <stdlib.h>

int is_product_even(const int *array, size_t size) {
    if (array == NULL) {
        return 0;
    }
    for (size_t i = 0; i < size; i++) {
        if (array[i] % 2 == 0) {
            return 1;
        }
    }
    return 0;
}

int main(void) {
    int arr1[] = {1, 3, 5, 7};
    int arr2[] = {1, 3, 4, 7};
    int arr3[] = {2, 4, 6, 8};

    int res1 = is_product_even(arr1, sizeof(arr1) / sizeof(arr1[0]));
    int res2 = is_product_even(arr2, sizeof(arr2) / sizeof(arr2[0]));
    int res3 = is_product_even(arr3, sizeof(arr3) / sizeof(arr3[0]));

    printf("%d\n", res1);
    printf("%d\n", res2);
    printf("%d\n", res3);

    return 0;
}