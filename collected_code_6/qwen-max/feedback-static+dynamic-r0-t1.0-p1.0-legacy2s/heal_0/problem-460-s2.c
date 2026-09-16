#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t length;
} Sublist;

int* get_first_elements(Sublist *sublists, size_t list_count, size_t *output_length) {
    if (!sublists || !list_count) {
        *output_length = 0;
        return NULL;
    }

    int *first_elements = (int *)malloc(list_count * sizeof(int));
    if (!first_elements) {
        *output_length = 0;
        return NULL;
    }

    *output_length = list_count;
    for (size_t i = 0; i < list_count; ++i) {
        if (sublists[i].length > 0) {
            first_elements[i] = sublists[i].data[0];
        } else {
            first_elements[i] = 0; // Assume 0 as a default value for an empty sublist
        }
    }

    return first_elements;
}

int main() {
    Sublist sublists[] = {
        { .data = (int []){1, 2, 3}, .length = 3 },
        { .data = (int []){4, 5, 6}, .length = 3 },
        { .data = (int []){7, 8, 9}, .length = 3 },
        { .data = (int []){}, .length = 0 }, // Empty sublist
    };
    size_t list_count = sizeof(sublists) / sizeof(sublists[0]);
    size_t output_length;

    int *first_elements = get_first_elements(sublists, list_count, &output_length);

    if (first_elements) {
        for (size_t i = 0; i < output_length; ++i) {
            printf("%d\n", first_elements[i]);
        }
        free(first_elements);
    }

    return 0;
}