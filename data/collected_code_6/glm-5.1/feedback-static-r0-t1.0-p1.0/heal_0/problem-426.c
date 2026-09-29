#include <stdio.h>
#include <stdlib.h>

int *filter_odd(const int *src, size_t src_len, size_t *out_len) {
    if (src == NULL || out_len == NULL) {
        return NULL;
    }

    size_t count = 0;
    for (size_t i = 0; i < src_len; i++) {
        if (src[i] % 2 != 0) {
            count++;
        }
    }

    int *result = (int *)malloc(count * sizeof(int));
    if (result == NULL) {
        *out_len = 0;
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < src_len; i++) {
        if (src[i] % 2 != 0) {
            result[j++] = src[i];
        }
    }

    *out_len = count;
    return result;
}

int main(void) {
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t data_len = sizeof(data) / sizeof(data[0]);
    size_t out_len = 0;

    int *odds = filter_odd(data, data_len, &out_len);

    if (odds != NULL) {
        for (size_t i = 0; i < out_len; i++) {
            printf("%d ", odds[i]);
        }
        printf("\n");
        free(odds);
    }

    return 0;
}