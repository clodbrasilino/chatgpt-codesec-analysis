#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b) {
    long long va = *(const long long *)a;
    long long vb = *(const long long *)b;
    if (va < vb) return 1;
    if (va > vb) return -1;
    return 0;
}

long long *find_largest_products(const int *list1, const int *list2, size_t len1, size_t len2, size_t k, size_t *out_len) {
    if (!list1 || !list2 || !out_len || len1 == 0 || len2 == 0) {
        if (out_len) *out_len = 0;
        return NULL;
    }

    size_t total_products = len1 * len2;
    if (k > total_products) {
        k = total_products;
    }
    
    long long *products = (long long *)malloc(total_products * sizeof(long long));
    if (!products) {
        *out_len = 0;
        return NULL;
    }

    size_t idx = 0;
    for (size_t i = 0; i < len1; ++i) {
        for (size_t j = 0; j < len2; ++j) {
            products[idx++] = (long long)list1[i] * list2[j];
        }
    }

    qsort(products, total_products, sizeof(long long), cmp);

    long long *result = (long long *)malloc(k * sizeof(long long));
    if (!result) {
        free(products);
        *out_len = 0;
        return NULL;
    }

    for (size_t i = 0; i < k; ++i) {
        result[i] = products[i];
    }

    free(products);
    *out_len = k;
    return result;
}

int main() {
    int list1[] = {-10, 10, 5, 7};
    int list2[] = {3, -2, 5};
    size_t len1 = sizeof(list1) / sizeof(list1[0]);
    size_t len2 = sizeof(list2) / sizeof(list2[0]);
    size_t k = 4;
    size_t out_len = 0;

    long long *result = find_largest_products(list1, list2, len1, len2, k, &out_len);

    if (result) {
        for (size_t i = 0; i < out_len; ++i) {
            printf("%lld ", result[i]);
        }
        printf("\n");
        free(result);
    } else {
        printf("No products found or memory allocation failed.\n");
    }

    return 0;
}