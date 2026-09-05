#include <stdio.h>
#include <stdlib.h>

int *filter_even(const int *src, size_t src_size, size_t *out_size) {
    if (src == NULL || out_size == NULL) {
        return NULL;
    }

    size_t count = 0;
    for (size_t i = 0; i < src_size; i++) {
        if (src[i] % 2 == 0) {
            count++;
        }
    }

    if (count == 0) {
        *out_size = 0;
        return NULL;
    }

    int *result = (int *)malloc(count * sizeof(int));
    if (result == NULL) {
        *out_size = 0;
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < src_size; i++) {
        if (src[i] % 2 == 0) {
            result[j++] = src[i];
        }
    }

    *out_size = count;
    return result;
}

int main(void) {
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t data_size = sizeof(data) / sizeof(data[0]);
    size_t out_size = 0;

    int *evens = filter_even(data, data_size, &out_size);

    if (evens != NULL) {
        for (size_t i = 0; i < out_size; i++) {
            printf("%d ", evens[i]);
        }
        printf("\n");
        free(evens);
    } else {
        printf("No even numbers found or allocation failed.\n");
    }

    return 0;
}