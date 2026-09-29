#include <stdio.h>
#include <stdlib.h>

long long product_of_unique(const int *arr, int size) {
    if (arr == NULL || size <= 0) {
        return 1;
    }

    long long product = 1;
    int *unique = (int *)malloc(size * sizeof(int));
    if (unique == NULL) {
        return 1;
    }

    int unique_count = 0;

    for (int i = 0; i < size; i++) {
        int found = 0;
        for (int j = 0; j < unique_count; j++) {
            if (arr[i] == unique[j]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            unique[unique_count] = arr[i];
            unique_count++;
        }
    }

    for (int i = 0; i < unique_count; i++) {
        product *= unique[i];
    }

    free(unique);
    return product;
}

int main(void) {
    int list1[] = {2, 3, 2, 5, 3, 7};
    int size1 = sizeof(list1) / sizeof(list1[0]);

    int list2[] = {1, 2, 3, 4, 5};
    int size2 = sizeof(list2) / sizeof(list2[0]);

    int list3[] = {10, 10, 10, 10};
    int size3 = sizeof(list3) / sizeof(list3[0]);

    int list4[] = {-2, 3, -2, 4, 3};
    int size4 = sizeof(list4) / sizeof(list4[0]);

    printf("Product of unique numbers in list1: %lld\n", product_of_unique(list1, size1));
    printf("Product of unique numbers in list2: %lld\n", product_of_unique(list2, size2));
    printf("Product of unique numbers in list3: %lld\n", product_of_unique(list3, size3));
    printf("Product of unique numbers in list4: %lld\n", product_of_unique(list4, size4));
    printf("Product of unique numbers in NULL list: %lld\n", product_of_unique(NULL, 0));
    printf("Product of unique numbers in empty list: %lld\n", product_of_unique(list1, 0));

    return 0;
}