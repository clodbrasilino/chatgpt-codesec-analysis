#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
} Tuple;

int tuple_first_last(const Tuple *tuple, int *first, int *last)
{
    if (tuple == NULL || first == NULL || last == NULL ||
        tuple->data == NULL || tuple->size == 0) {
        return -1;
    }

    *first = tuple->data[0];
    *last = tuple->data[tuple->size - 1];

    return 0;
}

int main(void)
{
    int values[] = {10, 20, 30, 40, 50};
    Tuple tuple = {
        .data = values,
        .size = sizeof(values) / sizeof(values[0])
    };
    int first = 0;
    int last = 0;

    if (tuple_first_last(&tuple, &first, &last) != 0) {
        if (fputs("Unable to access tuple data.\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("Initial: %d\nLast: %d\n", first, last) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}