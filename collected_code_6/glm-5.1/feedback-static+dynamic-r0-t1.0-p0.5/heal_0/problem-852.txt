#include <stdio.h>
#include <stdlib.h>

int remove_negatives(int *src, size_t src_len, int **dst, size_t *dst_len) {
    if (src == NULL || dst == NULL || dst_len == NULL) {
        return -1;
    }

    size_t count = 0;
    for (size_t i = 0; i < src_len; i++) {
        if (src[i] >= 0) {
            count++;
        }
    }

    if (count == 0) {
        *dst = NULL;
        *dst_len = 0;
        return 0;
    }

    *dst = (int *)malloc(count * sizeof(int));
    if (*dst == NULL) {
        return -1;
    }

    *dst_len = count;
    size_t j = 0;
    for (size_t i = 0; i < src_len; i++) {
        if (src[i] >= 0) {
            (*dst)[j++] = src[i];
        }
    }

    return 0;
}

int main() {
    int list[] = {5, -2, 0, 8, -1, -9, 3};
    size_t len = sizeof(list) / sizeof(list[0]);
    int *new_list = NULL;
    size_t new_len = 0;

    if (remove_negatives(list, len, &new_list, &new_len) == 0) {
        for (size_t i = 0; i < new_len; i++) {
            printf("%d ", new_list[i]);
        }
        printf("\n");
        free(new_list);
    }

    return 0;
}