#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const int *items;
    size_t length;
} List;

typedef struct {
    List element;
} SingletonTuple;

static int copy_list_from_singleton_tuple(const SingletonTuple *tuple,
                                          int **output,
                                          size_t *output_length)
{
    int *copy;
    size_t byte_count;

    if (tuple == NULL || output == NULL || output_length == NULL) {
        return -1;
    }

    *output = NULL;
    *output_length = 0;

    if (tuple->element.length == 0) {
        return 0;
    }

    if (tuple->element.items == NULL ||
        tuple->element.length > SIZE_MAX / sizeof(*copy)) {
        return -1;
    }

    byte_count = tuple->element.length * sizeof(*copy);
    copy = malloc(byte_count);
    if (copy == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(copy, tuple->element.items, byte_count);

    *output = copy;
    *output_length = tuple->element.length;
    return 0;
}

int main(void)
{
    static const int source[] = {1, 2, 3, 4, 5};
    const SingletonTuple tuple = {
        .element = {
            .items = source,
            .length = sizeof(source) / sizeof(source[0])
        }
    };
    int *copy = NULL;
    size_t copy_length = 0;

    if (copy_list_from_singleton_tuple(&tuple, &copy, &copy_length) != 0) {
        fputs("Failed to copy list\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < copy_length; ++i) {
        if (printf("%d%c", copy[i], i + 1 < copy_length ? ' ' : '\n') < 0) {
            free(copy);
            return EXIT_FAILURE;
        }
    }

    free(copy);
    return EXIT_SUCCESS;
}