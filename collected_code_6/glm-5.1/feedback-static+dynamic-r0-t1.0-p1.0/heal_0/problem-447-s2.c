#include <stdio.h>
#include <stdlib.h>

int *find_cubes(const int *list, size_t size) {
    if (list == NULL) {
        return NULL;
    }

    int *cubes = (int *)malloc(size * sizeof(int));
    if (cubes == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < size; ++i) {
        cubes[i] = list[i] * list[i] * list[i];
    }

    return cubes;
}

int main(void) {
    int list[] = {1, 2, 3, 4, 5};
    size_t size = sizeof(list) / sizeof(list[0]);

    int *cubes = find_cubes(list, size);
    if (cubes == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < size; ++i) {
        printf("%d ", cubes[i]);
    }
    printf("\n");

    free(cubes);
    cubes = NULL;

    return EXIT_SUCCESS;
}