#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_greater_than_array(int num, const int *array, size_t size) {
    if (array == NULL) {
        return false;
    }

    for (size_t i = 0; i < size; i++) {
        if (num <= array[i]) {
            return false;
        }
    }

    return true;
}

int main(void) {
    size_t size;
    int num;

    if (scanf("%zu", &size) != 1) {
        return EXIT_FAILURE;
    }

    if (size > 0) {
        int *array = (int *)malloc(size * sizeof(int));
        if (array == NULL) {
            return EXIT_FAILURE;
        }

        for (size_t i = 0; i < size; i++) {
            if (scanf("%d", &array[i]) != 1) {
                free(array);
                return EXIT_FAILURE;
            }
        }

        if (scanf("%d", &num) != 1) {
            free(array);
            return EXIT_FAILURE;
        }

        bool result = is_greater_than_array(num, array, size);

        printf("%s\n", result ? "True" : "False");

        free(array);
    } else {
        if (scanf("%d", &num) != 1) {
            return EXIT_FAILURE;
        }
        printf("True\n");
    }

    return EXIT_SUCCESS;
}