#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *items;
    size_t length;
} Tuple;

int tuple_get(const Tuple *tuple, size_t index, int *value)
{
    if (tuple == NULL || value == NULL || tuple->items == NULL ||
        index >= tuple->length) {
        return -1;
    }

    *value = tuple->items[index];
    return 0;
}

int main(void)
{
    Tuple tuple = {NULL, 3U};
    int value = 0;
    int status = EXIT_FAILURE;

    tuple.items = malloc(tuple.length * sizeof(*tuple.items));
    if (tuple.items == NULL) {
        fputs("Failed to allocate tuple storage.\n", stderr);
        return EXIT_FAILURE;
    }

    tuple.items[0] = 10;
    tuple.items[1] = 20;
    tuple.items[2] = 30;

    if (tuple_get(&tuple, 1U, &value) != 0) {
        fputs("Failed to get tuple item.\n", stderr);
        goto cleanup;
    }

    if (printf("%d\n", value) < 0) {
        fputs("Failed to write output.\n", stderr);
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(tuple.items);
    tuple.items = NULL;
    tuple.length = 0U;
    return status;
}