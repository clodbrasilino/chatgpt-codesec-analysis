#include <stdio.h>
#include <stdlib.h>

int cmp_desc(const void *a, const void *b) {
    long long va = *(const long long *)a;
    long long vb = *(const long long *)b;
    if (va > vb) return -1;
    if (va < vb) return 1;
    return 0;
}

long long *find_largest_products(const int *list1, size_t len1, const int *list2, size_t len2, size_t k, size_t *out_len) {
    *out_len = 0;
    if (!list1 || !list2 || len1 == 0 || len2 == 0 || k == 0) {
        return NULL;
    }

    size_t total = len1 * len2;
    size_t actual_k = k < total ? k : total;
    long long *products = (long long *)malloc(total * sizeof(long long));
    if (!products) {
        return NULL;
    }

    size_t idx = 0;
    for (size_t i = 0; i < len1; ++i) {
        for (size_t j = 0; j < len2; ++j) {
            products[idx++] = (long long)list1[i] * (long long)list2[j];
        }
    }

    qsort(products, total, sizeof(long long), cmp_desc);

    long long *result = (long long *)malloc(actual_k * sizeof(long long));
    if (!result) {
        free(products);
        return NULL;
    }

    for (size_t i = 0; i < actual_k; ++i) {
        result[i] = products[i];
    }

    free(products);
    *out_len = actual_k;
    return result;
}

int main(void) {
    int list1[] = {10, -10, 5, -5, 2};
    int list2[] = {8, -8, 3, -3, 1};
    size_t len1 = sizeof(list1) / sizeof(list1[0]);
    size_t len2 = sizeof(list2) / sizeof(list2[0]);
    size_t k = 5;
    size_t out_len = 0;

    long long *result = find_largest_products(list1, len1, list2, len2, k, &out_len);

    if (result) {
        for (size_t i = 0; i < out_len; ++i) {
            printf("%lld ", result[i]);
        }
        printf("\n");
        free(result);
    }

    return 0;
}