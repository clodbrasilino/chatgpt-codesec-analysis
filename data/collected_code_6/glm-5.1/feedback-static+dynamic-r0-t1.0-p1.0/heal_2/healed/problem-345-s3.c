#include <stdio.h>
#include <stdlib.h>

int* find_differences(const int* list, size_t size) {
    if (list == NULL || size < 2) {
        return NULL;
    }

    int* differences = malloc((size - 1) * sizeof(int));
    if (differences == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < size - 1; ++i) {
        differences[i] = list[i + 1] - list[i];
    }

    return differences;
}

int main(void) {
    const int list[] = {10, 5, 20, 15};
    size_t size = 4;

    int* differences = find_differences(list, size);
    if (differences == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    for (size_t i = 0; i < size - 1; ++i) {
        printf("%d ", differences[i]);
    }
    printf("\n");

    free(differences);
    differences = NULL;

    return 0;
}