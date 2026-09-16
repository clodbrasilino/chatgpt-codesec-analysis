#include <stdio.h>
#include <stdlib.h>

int* findDifferences(const int* list, size_t size) {
    if (list == NULL || size < 2) {
        return NULL;
    }

    int* differences = (int*)malloc((size - 1) * sizeof(int));
    if (differences == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < size - 1; ++i) {
        differences[i] = list[i + 1] - list[i];
    }

    return differences;
}

int main(void) {
    int list[] = {5, 10, 18, 22, 35};
    size_t size = sizeof(list) / sizeof(list[0]);

    int* diffs = findDifferences(list, size);
    if (diffs != NULL) {
        for (size_t i = 0; i < size - 1; ++i) {
            printf("%d ", diffs[i]);
        }
        printf("\n");
        free(diffs);
    } else {
        fprintf(stderr, "Error allocating memory or invalid input.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}