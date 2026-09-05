#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'src' can be declared as pointer to const [constParameterPointer]
 */
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
    int *result = NULL;
    size_t result_len = 0;

    if (remove_negatives(list, len, &result, &result_len) == 0) {
        for (size_t i = 0; i < result_len; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");
        free(result);
    } else {
        printf("Allocation failed\n");
    }

    return 0;
}