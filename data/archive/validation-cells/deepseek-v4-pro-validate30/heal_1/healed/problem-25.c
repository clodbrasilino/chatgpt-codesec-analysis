#include <stdio.h>
#include <stdlib.h>

int product_of_non_repeated(const int *arr, int size) {
    if (arr == NULL || size <= 0) {
        return 0;
    }

    int *count = (int *)calloc(size, sizeof(int));
    if (count == NULL) {
        return 0;
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (arr[i] == arr[j]) {
                count[i]++;
            }
        }
    }

    int product = 1;
    int has_non_repeated = 0;

    for (int i = 0; i < size; i++) {
        if (count[i] == 1) {
            product *= arr[i];
            has_non_repeated = 1;
        }
    }

    free(count);

    if (!has_non_repeated) {
        return 0;
    }

    return product;
}

int main(void) {
    int arr1[] = {2, 3, 2, 5, 3, 7};
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    int result1 = product_of_non_repeated(arr1, size1);
    printf("Product of non-repeated elements: %d\n", result1);

    int arr2[] = {1, 1, 1, 1};
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    int result2 = product_of_non_repeated(arr2, size2);
    printf("Product of non-repeated elements: %d\n", result2);

    int arr3[] = {5};
    int size3 = sizeof(arr3) / sizeof(arr3[0]);
    int result3 = product_of_non_repeated(arr3, size3);
    printf("Product of non-repeated elements: %d\n", result3);

    int result4 = product_of_non_repeated(NULL, 0);
    printf("Product of non-repeated elements: %d\n", result4);

    return 0;
}