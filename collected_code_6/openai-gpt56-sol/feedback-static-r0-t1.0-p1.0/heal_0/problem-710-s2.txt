#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
} Tuple;

int tuple_get_ends(const Tuple *tuple, int *initial, int *last)
{
    if (tuple == NULL || initial == NULL || last == NULL ||
        tuple->data == NULL || tuple->size == 0) {
        return -1;
    }

    *initial = tuple->data[0];
    *last = tuple->data[tuple->size - 1];

    return 0;
}

int main(void)
{
    Tuple tuple = {NULL, 0};
    int initial = 0;
    int last = 0;
    int status = EXIT_FAILURE;

    tuple.size = 5;
    tuple.data = malloc(tuple.size * sizeof(*tuple.data));
    if (tuple.data == NULL) {
        fputs("Memory allocation failed\n", stderr);
        goto cleanup;
    }

    tuple.data[0] = 10;
    tuple.data[1] = 20;
    tuple.data[2] = 30;
    tuple.data[3] = 40;
    tuple.data[4] = 50;

    if (tuple_get_ends(&tuple, &initial, &last) != 0) {
        fputs("Unable to access tuple data\n", stderr);
        goto cleanup;
    }

    if (printf("Initial: %d\nLast: %d\n", initial, last) < 0) {
        fputs("Output failed\n", stderr);
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(tuple.data);
    tuple.data = NULL;
    tuple.size = 0;

    return status;
}