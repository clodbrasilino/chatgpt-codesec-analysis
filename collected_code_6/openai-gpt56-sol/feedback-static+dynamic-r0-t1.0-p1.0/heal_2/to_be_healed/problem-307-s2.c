#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *data;
    size_t size;
} IntTuple;

int tuple_clone(const IntTuple *source, IntTuple *destination)
{
    int *copy;
    size_t bytes;

    if (source == NULL || destination == NULL || source == destination) {
        return EINVAL;
    }

    if (source->size == 0) {
        destination->data = NULL;
        destination->size = 0;
        return 0;
    }

    if (source->data == NULL || source->size > SIZE_MAX / sizeof(*copy)) {
        return EINVAL;
    }

    bytes = source->size * sizeof(*copy);
    copy = malloc(bytes);
    if (copy == NULL) {
        return ENOMEM;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(copy, source->data, bytes);

    destination->data = copy;
    destination->size = source->size;

    return 0;
}

void tuple_destroy(IntTuple *tuple)
{
    if (tuple != NULL) {
        free(tuple->data);
        tuple->data = NULL;
        tuple->size = 0;
    }
}

int main(void)
{
    int values[] = {10, 20, 30, 40};
    IntTuple original = {
        values,
        sizeof(values) / sizeof(values[0])
    };
    IntTuple clone = {NULL, 0};
    int result;

    result = tuple_clone(&original, &clone);
    if (result != 0) {
        fprintf(stderr, "Failed to clone tuple: %s\n", strerror(result));
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < clone.size; ++i) {
        printf("%d%s", clone.data[i],
               i + 1 < clone.size ? ": " : "\n");
    }

    tuple_destroy(&clone);
    return EXIT_SUCCESS;
}