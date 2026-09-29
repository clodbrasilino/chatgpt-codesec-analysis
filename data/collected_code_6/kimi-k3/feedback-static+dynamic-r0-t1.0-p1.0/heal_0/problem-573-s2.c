#include <stdio.h>
#include <stdlib.h>

int is_unique(int *arr, int size, int index) {
    int i;
    for (i = 0; i < size; i++) {
        if (i != index && arr[i] == arr[index]) {
            return 0;
        }
    }
    return 1;
}

long long product_of_unique(int *arr, int size) {
    long long product = 1;
    int i;
    int found = 0;

    if (arr == NULL || size <= 0) {
        return 0;
    }

    for (i = 0; i < size; i++) {
        if (is_unique(arr, size, i)) {
            product *= arr[i];
            found = 1;
        }
    }

    if (!found) {
        return 0;
    }

    return product;
}

int main(void) {
    int arr[] = {1, 2, 3, 2, 4, 1, 5};
    int size = sizeof(arr) / sizeof(arr[0]);
    long long result;

    result = product_of_unique(arr, size);

    printf("Product of unique numbers: %lld\n", result);

    return 0;
}