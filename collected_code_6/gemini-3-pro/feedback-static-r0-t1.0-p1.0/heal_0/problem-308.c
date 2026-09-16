#include <stdio.h>
#include <stdlib.h>

int compare_desc(const void *a, const void *b) {
    long long int_a = *(const long long *)a;
    long long int_b = *(const long long *)b;
    if (int_a < int_b) return 1;
    if (int_a > int_b) return -1;
    return 0;
}

long long* find_k_largest_products(const int *list1, size_t size1, const int *list2, size_t size2, size_t k, size_t *out_size) {
    if (!list1 || !list2 || !out_size || size1 == 0 || size2 == 0 || k == 0) {
        if (out_size) *out_size = 0;
        return NULL;
    }

    size_t total_products = size1 * size2;
    if (total_products / size1 != size2) {
        *out_size = 0;
        return NULL;
    }

    long long *products = (long long *)malloc(total_products * sizeof(long long));
    if (!products) {
        *out_size = 0;
        return NULL;
    }

    size_t idx = 0;
    for (size_t i = 0; i < size1; ++i) {
        for (size_t j = 0; j < size2; ++j) {
            products[idx++] = (long long)list1[i] * (long long)list2[j];
        }
    }

    qsort(products, total_products, sizeof(long long), compare_desc);

    size_t result_size = k < total_products ? k : total_products;
    long long *result = (long long *)malloc(result_size * sizeof(long long));
    if (!result) {
        free(products);
        *out_size = 0;
        return NULL;
    }

    for (size_t i = 0; i < result_size; ++i) {
        result[i] = products[i];
    }

    free(products);
    *out_size = result_size;
    return result;
}

int main(void) {
    int list1[] = {1, 5, 2};
    int list2[] = {3, 4, -1};
    size_t size1 = sizeof(list1) / sizeof(list1[0]);
    size_t size2 = sizeof(list2) / sizeof(list2[0]);
    size_t k = 3;
    size_t out_size = 0;

    long long *largest_products = find_k_largest_products(list1, size1, list2, size2, k, &out_size);

    if (largest_products) {
        for (size_t i = 0; i < out_size; ++i) {
            printf("%lld\n", largest_products[i]);
        }
        free(largest_products);
    }

    return 0;
}