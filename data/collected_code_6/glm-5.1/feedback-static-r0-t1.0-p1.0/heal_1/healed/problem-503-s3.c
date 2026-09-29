#include <stdio.h>
#include <stdlib.h>

int* add_consecutive_numbers(const int* list, size_t size, size_t* result_size) {
    if (list == NULL || result_size == NULL) {
        return NULL;
    }

    if (size == 0) {
        *result_size = 0;
        return NULL;
    }

    *result_size = (size + 1) / 2;

    int* result = (int*)malloc(*result_size * sizeof(int));
    if (result == NULL) {
        *result_size = 0;
        return NULL;
    }

    for (size_t i = 0; i < size; i += 2) {
        if (i + 1 < size) {
            result[i / 2] = list[i] + list[i + 1];
        } else {
            result[i / 2] = list[i];
        }
    }

    return result;
}

int main(void) {
    int list[] = {1, 2, 3, 4, 5};
    const size_t size = sizeof(list) / sizeof(list[0]);
    size_t result_size = 0;

    int* result = add_consecutive_numbers(list, size, &result_size);

    if (result != NULL) {
        for (size_t i = 0; i < result_size; ++i) {
            printf("%d ", result[i]);
        }
        printf("\n");
        free(result);
    } else {
        printf("Allocation failed\n");
    }

    return 0;
}