#include <stdio.h>
#include <stdlib.h>

int compare_ints(const void *a, const void *b) {
    int ia = *(const int *)a;
    int ib = *(const int *)b;
    return (ia > ib) - (ia < ib);
}

int **set_to_ordered_tuples(const int *set, size_t set_size, size_t *tuple_count, size_t *tuple_size) {
    if (set == NULL || tuple_count == NULL || tuple_size == NULL) {
        return NULL;
    }

    if (set_size == 0) {
        *tuple_count = 0;
        *tuple_size = 0;
        return NULL;
    }

    int *sorted = malloc(set_size * sizeof(int));
    if (sorted == NULL) {
        *tuple_count = 0;
        *tuple_size = 0;
        return NULL;
    }

    for (size_t i = 0; i < set_size; ++i) {
        sorted[i] = set[i];
    }

    qsort(sorted, set_size, sizeof(int), compare_ints);

    size_t unique_count = 1;
    for (size_t i = 1; i < set_size; ++i) {
        if (sorted[i] != sorted[i - 1]) {
            sorted[unique_count++] = sorted[i];
        }
    }

    if (unique_count < 2) {
        *tuple_count = 0;
        *tuple_size = 2;
        free(sorted);
        return NULL;
    }

    size_t count = unique_count * (unique_count - 1) / 2;

    int **tuples = malloc(count * sizeof(int *));
    if (tuples == NULL) {
        *tuple_count = 0;
        *tuple_size = 2;
        free(sorted);
        return NULL;
    }

    size_t index = 0;
    for (size_t i = 0; i < unique_count; ++i) {
        for (size_t j = i + 1; j < unique_count; ++j) {
            tuples[index] = malloc(2 * sizeof(int));
            if (tuples[index] == NULL) {
                for (size_t k = 0; k < index; ++k) {
                    free(tuples[k]);
                }
                free(tuples);
                free(sorted);
                *tuple_count = 0;
                *tuple_size = 0;
                return NULL;
            }
            tuples[index][0] = sorted[i];
            tuples[index][1] = sorted[j];
            ++index;
        }
    }

    *tuple_count = count;
    *tuple_size = 2;
    free(sorted);

    return tuples;
}

void free_tuples(int **tuples, size_t tuple_count) {
    if (tuples == NULL) {
        return;
    }
    for (size_t i = 0; i < tuple_count; ++i) {
        free(tuples[i]);
    }
    free(tuples);
}

int main(void) {
    int set[] = {5, 2, 8, 2, 5, 1, 9, 1};
    size_t set_size = sizeof(set) / sizeof(set[0]);
    size_t original_set_size = set_size;

    size_t tuple_count = 0;
    size_t tuple_size = 0;

    int **tuples = set_to_ordered_tuples(set, set_size, &tuple_count, &tuple_size);

    if (tuples != NULL) {
        for (size_t i = 0; i < tuple_count; ++i) {
            printf("(%d, %d)\n", tuples[i][0], tuples[i][1]);
        }
        free_tuples(tuples, tuple_count);
    } else {
        if (tuple_count == 0 && tuple_size == 2 && original_set_size > 0) {
            printf("Not enough unique elements to form a tuple.\n");
        } else if (original_set_size == 0) {
            printf("Empty set provided.\n");
        } else {
            printf("Memory allocation failed.\n");
        }
    }

    return 0;
}