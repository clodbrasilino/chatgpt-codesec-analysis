#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool check_unique(const int *array, size_t size) {
    if (array == NULL || size == 0) {
        return true;
    }

    for (size_t i = 0; i < size; ++i) {
        for (size_t j = i + 1; j < size; ++j) {
            if (array[i] == array[j]) {
                return false;
            }
        }
    }

    return true;
}

int main(void) {
    size_t size;
    int *array = NULL;

    if (scanf("%zu", &size) != 1) {
        return EXIT_FAILURE;
    }

    if (size > 0) {
        array = (int *)malloc(size * sizeof(int));
        if (array == NULL) {
            return EXIT_FAILURE;
        }

        for (size_t i = 0; i < size; ++i) {
            if (scanf("%d", &array[i]) != 1) {
                free(array);
                return EXIT_FAILURE;
            }
        }
    }

    bool is_unique = check_unique(array, size);

    if (is_unique) {
        printf("Elements are unique.\n");
    } else {
        printf("Elements are not unique.\n");
    }

    free(array);

    return EXIT_SUCCESS;
}