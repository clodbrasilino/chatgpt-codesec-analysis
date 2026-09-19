#include <stdio.h>
#include <stdlib.h>

int *add_consecutive(const int *list, size_t size, size_t *result_size) {
    if (list == NULL || result_size == NULL) {
        return NULL;
    }

    if (size < 2) {
        *result_size = 0;
        return NULL;
    }

    *result_size = size - 1;
    int *result = (int *)malloc(*result_size * sizeof(int));
    if (result == NULL) {
        *result_size = 0;
        return NULL;
    }

    for (size_t i = 0; i < *result_size; i++) {
        result[i] = list[i] + list[i + 1];
    }

    return result;
}

int main(void) {
    int list[] = {2, 4, 7, 8, 9, 11, 13};
    size_t size = sizeof(list) / sizeof(list[0]);
    size_t result_size = 0;

    int *result = add_consecutive(list, size, &result_size);

    if (result != NULL) {
        printf("[");
        for (size_t i = 0; i < result_size; i++) {
            printf("%d", result[i]);
            if (i < result_size - 1) {
                printf(", ");
            }
        }
        printf("]\n");
        free(result);
    } else {
        if (size < 2) {
            printf("List size is less than 2.\n");
        } else {
            printf("Memory allocation failed.\n");
        }
    }

    return 0;
}