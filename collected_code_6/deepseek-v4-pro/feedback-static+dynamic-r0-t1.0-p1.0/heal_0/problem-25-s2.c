#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

long long product_of_non_repeated(int arr[], int size) {
    if (size <= 0) {
        return 0;
    }

    int *temp = (int*)malloc(size * sizeof(int));
    if (temp == NULL) {
        return 0;
    }

    for (int i = 0; i < size; i++) {
        temp[i] = arr[i];
    }

    qsort(temp, size, sizeof(int), compare);

    long long product = 1;
    int found = 0;

    for (int i = 0; i < size; i++) {
        int count = 1;
        while (i + 1 < size && temp[i] == temp[i + 1]) {
            count++;
            i++;
        }
        if (count == 1) {
            product *= temp[i];
            found = 1;
        }
    }

    free(temp);

    if (!found) {
        return 0;
    }

    return product;
}

int main() {
    int arr1[] = {1, 2, 3, 2, 1, 4};
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    printf("Product: %lld\n", product_of_non_repeated(arr1, size1));

    int arr2[] = {5, 5, 5, 5};
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("Product: %lld\n", product_of_non_repeated(arr2, size2));

    int arr3[] = {7};
    int size3 = sizeof(arr3) / sizeof(arr3[0]);
    printf("Product: %lld\n", product_of_non_repeated(arr3, size3));

    int arr4[] = {};
    int size4 = 0;
    printf("Product: %lld\n", product_of_non_repeated(arr4, size4));

    return 0;
}