#include <stdio.h>
#include <stdlib.h>

struct Pair {
    int u;
    int v;
};

void find_k_pairs(const int* arr1, size_t size1, const int* arr2, size_t size2, size_t k, struct Pair** result, size_t* result_size) {
    if (!arr1 || !arr2 || !result || !result_size) {
        return;
    }

    size_t count = 0;
    size_t max_pairs = size1 * size2;
    if (k > max_pairs) {
        k = max_pairs;
    }

    *result = (struct Pair*)malloc(k * sizeof(struct Pair));
    if (!*result) {
        *result_size = 0;
        return;
    }

    *result_size = k;

    for (size_t i = 0; i < size1 && count < k; ++i) {
        for (size_t j = 0; j < size2 && count < k; ++j) {
            (*result)[count].u = arr1[i];
            (*result)[count].v = arr2[j];
            count++;
        }
    }
}

int main(void) {
    int arr1[] = {1, 2, 3};
    int arr2[] = {4, 5, 6};
    size_t size1 = sizeof(arr1) / sizeof(arr1[0]);
    size_t size2 = sizeof(arr2) / sizeof(arr2[0]);
    size_t k = 5;

    struct Pair* result = NULL;
    size_t result_size = 0;

    find_k_pairs(arr1, size1, arr2, size2, k, &result, &result_size);

    if (result) {
        for (size_t i = 0; i < result_size; ++i) {
            printf("(%d, %d)\n", result[i].u, result[i].v);
        }
        free(result);
        result = NULL;
    }

    return 0;
}