#include <stdio.h>
#include <stdlib.h>

int *remove_duplicates(const int *tuple, size_t size, int custom_value, size_t *out_size) {
    if (tuple == NULL || out_size == NULL) {
        return NULL;
    }

    int *result = (int *)malloc(size * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < size; i++) {
        result[i] = tuple[i];
    }

    for (size_t i = 0; i < size; i++) {
        if (result[i] == custom_value) {
            continue;
        }

        int count = 0;
        for (size_t j = 0; j < size; j++) {
            if (result[j] == tuple[i]) {
                count++;
            }
        }

        if (count > 1) {
            for (size_t k = 0; k < size; k++) {
                if (result[k] == tuple[i]) {
                    result[k] = custom_value;
                }
            }
        }
    }

    *out_size = size;
    return result;
}

int main(void) {
    int tuple[] = {1, 2, 3, 2, 4, 1, 5, 6, 5};
    size_t size = sizeof(tuple) / sizeof(tuple[0]);
    int custom_value = -1;
    size_t out_size = 0;

    int *result = remove_duplicates(tuple, size, custom_value, &out_size);

    if (result != NULL) {
        for (size_t i = 0; i < out_size; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");
        free(result);
    }

    return 0;
}