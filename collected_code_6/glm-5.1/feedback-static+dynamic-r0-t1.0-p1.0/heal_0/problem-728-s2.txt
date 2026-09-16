#include <stdio.h>
#include <stdlib.h>

int* sum_lists(const int* a, size_t a_len, const int* b, size_t b_len, size_t* out_len) {
    if (a == NULL || b == NULL || out_len == NULL) {
        return NULL;
    }

    size_t min_len = a_len < b_len ? a_len : b_len;

    int* result = (int*)malloc(min_len * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < min_len; ++i) {
        result[i] = a[i] + b[i];
    }

    *out_len = min_len;
    return result;
}

int main(void) {
    int a[] = {1, 2, 3, 4, 5};
    int b[] = {6, 7, 8};

    size_t a_len = sizeof(a) / sizeof(a[0]);
    size_t b_len = sizeof(b) / sizeof(b[0]);
    size_t out_len = 0;

    int* result = sum_lists(a, a_len, b, b_len, &out_len);

    if (result != NULL) {
        for (size_t i = 0; i < out_len; ++i) {
            printf("%d ", result[i]);
        }
        printf("\n");
        free(result);
        result = NULL;
    } else {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}