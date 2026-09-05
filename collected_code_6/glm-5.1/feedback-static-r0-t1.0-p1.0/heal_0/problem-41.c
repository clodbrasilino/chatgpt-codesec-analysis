#include <stdio.h>
#include <stdlib.h>

int *filter_even(const int *src, size_t src_len, size_t *dst_len) {
    if (src == NULL || dst_len == NULL) {
        return NULL;
    }

    size_t count = 0;
    for (size_t i = 0; i < src_len; ++i) {
        if (src[i] % 2 == 0) {
            count++;
        }
    }

    int *dst = (int *)malloc(count * sizeof(int));
    if (dst == NULL) {
        return NULL;
    }

    size_t idx = 0;
    for (size_t i = 0; i < src_len; ++i) {
        if (src[i] % 2 == 0) {
            dst[idx++] = src[i];
        }
    }

    *dst_len = count;
    return dst;
}

int main(void) {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t arr_len = sizeof(arr) / sizeof(arr[0]);
    size_t dst_len = 0;

    int *even_arr = filter_even(arr, arr_len, &dst_len);

    if (even_arr == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < dst_len; ++i) {
        printf("%d ", even_arr[i]);
    }
    printf("\n");

    free(even_arr);
    even_arr = NULL;

    return EXIT_SUCCESS;
}