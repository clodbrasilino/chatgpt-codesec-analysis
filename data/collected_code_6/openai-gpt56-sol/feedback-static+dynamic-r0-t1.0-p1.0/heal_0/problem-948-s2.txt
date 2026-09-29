#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    size_t length;
    int *items;
} Tuple;

static int tuple_get(const Tuple *tuple, size_t index, int *value)
{
    if (tuple == NULL || value == NULL || tuple->items == NULL) {
        return -1;
    }

    if (index >= tuple->length) {
        return -1;
    }

    *value = tuple->items[index];
    return 0;
}

int main(void)
{
    int exit_status = EXIT_FAILURE;
    int value = 0;
    size_t index = 1;
    Tuple tuple = {0, NULL};

    tuple.length = 3;
    tuple.items = malloc(tuple.length * sizeof(*tuple.items));
    if (tuple.items == NULL) {
        fputs("Failed to allocate tuple storage\n", stderr);
        goto cleanup;
    }

    tuple.items[0] = 10;
    tuple.items[1] = 20;
    tuple.items[2] = 30;

    if (tuple_get(&tuple, index, &value) != 0) {
        fputs("Failed to get tuple item\n", stderr);
        goto cleanup;
    }

    if (printf("%d\n", value) < 0) {
        fputs("Failed to write output\n", stderr);
        goto cleanup;
    }

    exit_status = EXIT_SUCCESS;

cleanup:
    free(tuple.items);
    tuple.items = NULL;
    tuple.length = 0;
    return exit_status;
}