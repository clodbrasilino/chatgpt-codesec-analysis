#include <stdio.h>
#include <stdlib.h>

int* filter_odd(const int* src, size_t src_size, size_t* out_size) {
    if (!src || !out_size) {
        return NULL;
    }

    size_t count = 0;
    for (size_t i = 0; i < src_size; ++i) {
        if (src[i] % 2 != 0) {
            count++;
        }
    }

    *out_size = count;
    if (count == 0) {
        return NULL;
    }

    int* dst = (int*)malloc(count * sizeof(int));
    if (!dst) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < src_size; ++i) {
        if (src[i] % 2 != 0) {
            dst[j++] = src[i];
        }
    }

    return dst;
}

int main(void) {
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t data_size = sizeof(data) / sizeof(data[0]);
    size_t out_size = 0;

    int* result = filter_odd(data, data_size, &out_size);

    if (result) {
        for (size_t i = 0; i < out_size; ++i) {
            printf("%d ", result[i]);
        }
        printf("\n");
        free(result);
    } else {
        if (out_size == 0) {
            printf("No odd numbers found.\n");
        } else {
            fprintf(stderr, "Allocation failed.\n");
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}