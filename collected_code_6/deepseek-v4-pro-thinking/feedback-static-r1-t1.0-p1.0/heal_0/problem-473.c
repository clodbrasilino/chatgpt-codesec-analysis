#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    const int *elements;
    size_t size;
} Tuple;

static int contains_int(const int *elements, size_t size, int value) {
    for (size_t i = 0; i < size; ++i) {
        if (elements[i] == value) {
            return 1;
        }
    }
    return 0;
}

int tuple_intersection(const Tuple *tuples, size_t tuple_count, int **result, size_t *result_size) {
    if (result == NULL || result_size == NULL) {
        return -1;
    }

    *result = NULL;
    *result_size = 0;

    if (tuples == NULL || tuple_count == 0) {
        return 0;
    }

    for (size_t i = 0; i < tuple_count; ++i) {
        if (tuples[i].elements == NULL && tuples[i].size > 0) {
            return -1;
        }
    }

    if (tuples[0].size > SIZE_MAX / sizeof(int)) {
        return -1;
    }

    int *current = NULL;
    size_t current_size = 0;

    if (tuples[0].size > 0) {
        current = malloc(tuples[0].size * sizeof(int));
        if (current == NULL) {
            return -1;
        }

        for (size_t i = 0; i < tuples[0].size; ++i) {
            if (!contains_int(current, current_size, tuples[0].elements[i])) {
                current[current_size++] = tuples[0].elements[i];
            }
        }

        if (current_size == 0) {
            free(current);
            current = NULL;
        }
    }

    for (size_t i = 1; i < tuple_count && current_size > 0; ++i) {
        int *next = malloc(current_size * sizeof(int));
        if (next == NULL) {
            free(current);
            return -1;
        }

        size_t next_size = 0;
        for (size_t j = 0; j < current_size; ++j) {
            if (contains_int(tuples[i].elements, tuples[i].size, current[j])) {
                next[next_size++] = current[j];
            }
        }

        free(current);
        current = next;
        current_size = next_size;

        if (current_size == 0) {
            free(current);
            current = NULL;
        }
    }

    if (current_size > 0) {
        int *resized = realloc(current, current_size * sizeof(int));
        if (resized != NULL) {
            current = resized;
        }
    } else if (current != NULL) {
        free(current);
        current = NULL;
    }

    *result = current;
    *result_size = current_size;
    return 0;
}

int main(void) {
    Tuple tuples[] = {
        { (int[]){1, 2, 3, 4}, 4 },
        { (int[]){2, 4, 6}, 3 },
        { (int[]){4, 2, 8}, 3 }
    };

    int *result = NULL;
    size_t result_size = 0;

    if (tuple_intersection(tuples, 3, &result, &result_size) != 0) {
        return 1;
    }

    for (size_t i = 0; i < result_size; ++i) {
        printf("%d ", result[i]);
    }
    printf("\n");

    free(result);
    return 0;
}