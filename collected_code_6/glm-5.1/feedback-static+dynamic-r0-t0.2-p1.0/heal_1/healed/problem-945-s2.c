#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *elements;
    size_t size;
} Set;

Set tuples_to_set(const int *tuples, size_t tuple_count, size_t tuple_size) {
    Set empty = {NULL, 0};
    if (tuple_count == 0 || tuple_size == 0) {
        return empty;
    }

    size_t total_elements = tuple_count * tuple_size;
    if (total_elements / tuple_count != tuple_size) {
        return empty;
    }

    int *temp = malloc(total_elements * sizeof(int));
    if (!temp) {
        return empty;
    }

    if (total_elements > SIZE_MAX / sizeof(int)) {
        free(temp);
        return empty;
    }
    memcpy(temp, tuples, total_elements * sizeof(int));

    size_t unique_count = 0;
    for (size_t i = 0; i < total_elements; i++) {
        int is_unique = 1;
        for (size_t j = 0; j < unique_count; j++) {
            if (temp[i] == temp[j]) {
                is_unique = 0;
                break;
            }
        }
        if (is_unique) {
            temp[unique_count++] = temp[i];
        }
    }

    int *set_elements = malloc(unique_count * sizeof(int));
    if (!set_elements) {
        free(temp);
        return empty;
    }

    if (unique_count > SIZE_MAX / sizeof(int)) {
        free(temp);
        free(set_elements);
        return empty;
    }
    memcpy(set_elements, temp, unique_count * sizeof(int));
    free(temp);

    Set result;
    result.elements = set_elements;
    result.size = unique_count;
    return result;
}

void free_set(Set *s) {
    if (s) {
        free(s->elements);
        s->elements = NULL;
        s->size = 0;
    }
}

int main(void) {
    int data[][3] = {{1, 2, 3}, {2, 3, 4}, {4, 5, 1}};
    size_t tuple_count = sizeof(data) / sizeof(data[0]);
    size_t tuple_size = sizeof(data[0]) / sizeof(data[0][0]);

    Set s = tuples_to_set((const int *)data, tuple_count, tuple_size);

    if (s.elements != NULL) {
        for (size_t i = 0; i < s.size; i++) {
            printf("%d ", s.elements[i]);
        }
        printf("\n");
    }

    free_set(&s);

    return 0;
}