#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    size_t size;
} Tuple;

int get_column(const Tuple *tuple, size_t index, int *out_value)
{
    if (tuple == NULL || out_value == NULL) {
        return -1;
    }
    if (tuple->elements == NULL) {
        return -1;
    }
    if (index >= tuple->size) {
        return -1;
    }
    *out_value = tuple->elements[index];
    return 0;
}

int main(void)
{
    size_t count = 5;
    Tuple tuple;
    int value = 0;
    size_t i;

    tuple.elements = malloc(count * sizeof(int));
    if (tuple.elements == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    tuple.size = count;

    for (i = 0; i < count; i++) {
        tuple.elements[i] = (int)(i * 10);
    }

    if (get_column(&tuple, 2, &value) == 0) {
        printf("Column 2: %d\n", value);
    } else {
        fprintf(stderr, "Failed to get column 2\n");
        free(tuple.elements);
        return EXIT_FAILURE;
    }

    if (get_column(&tuple, 10, &value) != 0) {
        fprintf(stderr, "Index 10 is out of range\n");
    }

    free(tuple.elements);
    tuple.elements = NULL;
    tuple.size = 0;

    return EXIT_SUCCESS;
}