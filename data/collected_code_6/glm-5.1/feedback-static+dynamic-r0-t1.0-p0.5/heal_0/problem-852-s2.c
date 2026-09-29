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

    int *result = (int *)malloc(count * sizeof(int));
    if (result == NULL) {
        return -1;
    }

    size_t j = 0;
    for (size_t i = 0; i < src_len; i++) {
        if (src[i] >= 0) {
            result[j++] = src[i];
        }
    }

    *dst = result;
    *dst_len = count;
    return 0;
}

int main(void) {
    int list[] = {5, -2, 0, 8, -1, -7, 3};
    size_t len = sizeof(list) / sizeof(list[0]);
    int *new_list = NULL;
    size_t new_len = 0;

    int ret = remove_negatives(list, len, &new_list, &new_len);
    if (ret == 0) {
        for (size_t i = 0; i < new_len; i++) {
            printf("%d ", new_list[i]);
        }
        printf("\n");
        free(new_list);
    } else {
        printf("Error removing negatives.\n");
    }

    return 0;
}