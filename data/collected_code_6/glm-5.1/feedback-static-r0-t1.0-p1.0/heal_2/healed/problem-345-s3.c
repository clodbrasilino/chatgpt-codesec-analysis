#include <stdio.h>
#include <stdlib.h>

int* find_differences(const int* list, size_t size, size_t* out_size) {
    if (list == NULL || out_size == NULL || size < 2) {
        return NULL;
    }

    *out_size = size - 1;
    int* differences = malloc(*out_size * sizeof(int));
    if (differences == NULL) {
        *out_size = 0;
        return NULL;
    }

    for (size_t i = 0; i < *out_size; ++i) {
        differences[i] = list[i + 1] - list[i];
    }

    return differences;
}

int main(void) {
    int list[] = {10, 5, 20, 15};
    size_t size = sizeof(list) / sizeof(list[0]);
    size_t diff_size = 0;

    int* differences = find_differences(list, size, &diff_size);
    if (differences == NULL) {
        if (diff_size == 0 && size >= 2) {
            fprintf(stderr, "Memory allocation failed\n");
        } else {
            fprintf(stderr, "Invalid input\n");
        }
        return 1;
    }

    for (size_t i = 0; i < diff_size; ++i) {
        printf("%d ", differences[i]);
    }
    printf("\n");

    free(differences);
    differences = NULL;

    return 0;
}