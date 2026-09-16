#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int list_difference(const int *list1, size_t size1,
                    const int *list2, size_t size2,
                    int **result, size_t *result_size)
{
    if (result == NULL || result_size == NULL) {
        return -1;
    }

    *result = NULL;
    *result_size = 0;

    if (size1 == 0) {
        return 0;
    }

    if (list1 == NULL || (size2 > 0 && list2 == NULL)) {
        return -1;
    }

    if (size1 > (size_t)-1 / sizeof(int)) {
        return -1;
    }

    int *out = malloc(size1 * sizeof(int));
    if (out == NULL) {
        return -1;
    }

    size_t out_size = 0;

    for (size_t i = 0; i < size1; i++) {
        int found = 0;

        for (size_t j = 0; j < size2; j++) {
            if (list1[i] == list2[j]) {
                found = 1;
                break;
            }
        }

        if (!found) {
            out[out_size++] = list1[i];
        }
    }

    if (out_size == 0) {
        free(out);
        *result = NULL;
    } else {
        *result = out;
        *result_size = out_size;
    }

    return 0;
}

int main(void)
{
    int list1[] = { 1, 2, 3, 4 };
    int list2[] = { 2, 4 };
    int *result = NULL;
    size_t result_size = 0;

    if (list_difference(list1, sizeof(list1) / sizeof(list1[0]),
                        list2, sizeof(list2) / sizeof(list2[0]),
                        &result, &result_size) != 0) {
        return 1;
    }

    for (size_t i = 0; i < result_size; i++) {
        printf("%d\n", result[i]);
    }

    free(result);
    return 0;
}