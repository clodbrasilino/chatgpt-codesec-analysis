#include <stdio.h>
#include <stdlib.h>

int sequential_search(int *array, size_t size, int target) {
    if (array == NULL || size == 0) {
        return -1;
    }

    for (size_t i = 0; i < size; i++) {
        if (array[i] == target) {
            return (int)i;
        }
    }

    return -1;
}

int main(void) {
    size_t size = 5;
    int *array = malloc(size * sizeof(int));
    if (array == NULL) {
        return EXIT_FAILURE;
    }

    array[0] = 10;
    array[1] = 20;
    array[2] = 30;
    array[3] = 40;
    array[4] = 50;

    int target = 30;
    int index = sequential_search(array, size, target);

    printf("%d\n", index);

    free(array);
    array = NULL;

    return EXIT_SUCCESS;
}