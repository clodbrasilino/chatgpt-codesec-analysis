#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

struct counted_element {
    int value;
    size_t count;
};

static int expand_elements(const struct counted_element *elements,
                           size_t num_elements,
                           int **out_result,
                           size_t *out_size)
{
    size_t total = 0;
    size_t i;
    size_t pos;
    int *result;

    if (elements == NULL || out_result == NULL || out_size == NULL) {
        return -1;
    }

    for (i = 0; i < num_elements; i++) {
        if (elements[i].count > (SIZE_MAX - total)) {
            return -1;
        }
        total += elements[i].count;
    }

    if (total == 0) {
        *out_result = NULL;
        *out_size = 0;
        return 0;
    }

    if (total > (SIZE_MAX / sizeof(int))) {
        return -1;
    }

    result = malloc(total * sizeof(int));
    if (result == NULL) {
        return -1;
    }

    pos = 0;
    for (i = 0; i < num_elements; i++) {
        size_t j;
        for (j = 0; j < elements[i].count; j++) {
            result[pos] = elements[i].value;
            pos++;
        }
    }

    *out_result = result;
    *out_size = total;
    return 0;
}

int main(void)
{
    struct counted_element elements[] = {
        { 7, 3 },
        { 42, 1 },
        { 5, 4 },
        { 9, 0 },
        { 13, 2 }
    };
    size_t num_elements = sizeof(elements) / sizeof(elements[0]);
    int *expanded = NULL;
    size_t expanded_size = 0;
    size_t i;

    if (expand_elements(elements, num_elements, &expanded, &expanded_size) != 0) {
        fprintf(stderr, "Failed to expand elements\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < expanded_size; i++) {
        if (printf("%d ", expanded[i]) < 0) {
            free(expanded);
            return EXIT_FAILURE;
        }
    }

    if (printf("\n") < 0) {
        free(expanded);
        return EXIT_FAILURE;
    }

    free(expanded);
    return EXIT_SUCCESS;
}