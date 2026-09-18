#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

int* convert_tuple_to_set(const int *tuple, size_t tuple_size, size_t *set_size);

int* convert_tuple_to_set(const int *tuple, size_t tuple_size, size_t *set_size) {
    if (tuple == NULL || set_size == NULL) {
        return NULL;
    }

    if (tuple_size == 0) {
        *set_size = 0;
        return NULL;
    }

    int *set = (int *)malloc(tuple_size * sizeof(int));
    if (set == NULL) {
        return NULL;
    }

    size_t unique_count = 0;

    for (size_t i = 0; i < tuple_size; ++i) {
        int is_duplicate = 0;
        for (size_t j = 0; j < unique_count; ++j) {
            if (tuple[i] == set[j]) {
                is_duplicate = 1;
                break;
            }
        }
        if (!is_duplicate) {
            set[unique_count] = tuple[i];
            unique_count++;
        }
    }

    if (unique_count > 0) {
        int *resized_set = (int *)realloc(set, unique_count * sizeof(int));
        if (resized_set != NULL) {
            set = resized_set;
        }
    } else {
        free(set);
        set = NULL;
    }

    *set_size = unique_count;
    return set;
}

int main(void) {
    int tuple[] = {1, 2, 2, 3, 4, 1, 5, 4};
    size_t tuple_size = sizeof(tuple) / sizeof(tuple[0]);
    size_t set_size = 0;

    int *set = convert_tuple_to_set(tuple, tuple_size, &set_size);

    if (set != NULL) {
        for (size_t i = 0; i < set_size; ++i) {
            printf("%d ", set[i]);
        }
        printf("\n");
        free(set);
    }

    return 0;
}