#include <stdio.h>
#include <stdlib.h>

int contains(int *arr, int size, int value) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == value) {
            return 1;
        }
    }
    return 0;
}

long long product_of_unique(int *list, int size) {
    if (list == NULL || size <= 0) {
        return 0;
    }

    int *unique = (int *)malloc(size * sizeof(int));
    if (unique == NULL) {
        return 0;
    }

    int unique_count = 0;
    long long product = 1;
    int has_unique = 0;

    for (int i = 0; i < size; i++) {
        int is_duplicate = 0;
        for (int j = 0; j < size; j++) {
            if (i != j && list[i] == list[j]) {
                is_duplicate = 1;
                break;
            }
        }
        if (!is_duplicate && !contains(unique, unique_count, list[i])) {
            unique[unique_count++] = list[i];
            product *= list[i];
            has_unique = 1;
        }
    }

    free(unique);

    if (!has_unique) {
        return 0;
    }

    return product;
}

int main(void) {
    int test1[] = {1, 2, 3, 2, 4, 1};
    int size1 = sizeof(test1) / sizeof(test1[0]);
    printf("%lld\n", product_of_unique(test1, size1));

    int test2[] = {5, 5, 5, 5};
    int size2 = sizeof(test2) / sizeof(test2[0]);
    printf("%lld\n", product_of_unique(test2, size2));

    int test3[] = {7, 14, 21};
    int size3 = sizeof(test3) / sizeof(test3[0]);
    printf("%lld\n", product_of_unique(test3, size3));

    int test4[] = {-2, -3, -2, 5};
    int size4 = sizeof(test4) / sizeof(test4[0]);
    printf("%lld\n", product_of_unique(test4, size4));

    printf("%lld\n", product_of_unique(NULL, 3));

    return 0;
}