#include <stdio.h>
#include <stdlib.h>

int* sum_lists(const int* a, size_t len_a, const int* b, size_t len_b, size_t* out_len) {
    size_t min_len = len_a < len_b ? len_a : len_b;
    size_t max_len = len_a > len_b ? len_a : len_b;
    *out_len = max_len;

    int* result = (int*)malloc(max_len * sizeof(int));
    if (result == NULL) {
        *out_len = 0;
        return NULL;
    }

    size_t i = 0;
    for (; i < min_len; ++i) {
        result[i] = a[i] + b[i];
    }

    for (; i < len_a; ++i) {
        result[i] = a[i];
    }

    for (; i < len_b; ++i) {
        result[i] = b[i];
    }

    return result;
}

int main(void) {
    int a[] = {1, 2, 3};
    int b[] = {4, 5, 6, 7, 8};
    size_t len_a = sizeof(a) / sizeof(a[0]);
    size_t len_b = sizeof(b) / sizeof(b[0]);
    size_t out_len = 0;

    int* result = sum_lists(a, len_a, b, len_b, &out_len);

    if (result != NULL) {
        for (size_t i = 0; i < out_len; ++i) {
            printf("%d ", result[i]);
        }
        printf("\n");
        free(result);
    }

    return 0;
}