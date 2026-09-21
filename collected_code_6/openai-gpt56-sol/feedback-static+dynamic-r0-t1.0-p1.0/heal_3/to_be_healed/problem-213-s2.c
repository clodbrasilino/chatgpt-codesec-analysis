#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    char **items;
    size_t size;
} StringTuple;

static void free_string_tuple(StringTuple *tuple)
{
    if (tuple == NULL) {
        return;
    }

    for (size_t i = 0; i < tuple->size; ++i) {
        free(tuple->items[i]);
    }

    free(tuple->items);
    tuple->items = NULL;
    tuple->size = 0;
}

static int duplicate_string(const char *source, char **destination)
{
    if (source == NULL || destination == NULL) {
        return -1;
    }

    *destination = NULL;

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t length = strlen(source);

    if (length == SIZE_MAX) {
        return -1;
    }

    char *copy = malloc(length + 1);
    if (copy == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(copy, source, length + 1);
    *destination = copy;

    return 0;
}

static int concatenate_string_tuples(
    const StringTuple *first,
    const StringTuple *second,
    StringTuple *result)
{
    if (first == NULL || second == NULL || result == NULL ||
        result == first || result == second) {
        return -1;
    }

    result->items = NULL;
    result->size = 0;

    if ((first->size != 0 && first->items == NULL) ||
        (second->size != 0 && second->items == NULL) ||
        first->size > SIZE_MAX - second->size) {
        return -1;
    }

    size_t total = first->size + second->size;

    if (total == 0) {
        return 0;
    }

    if (total > SIZE_MAX / sizeof(*result->items)) {
        return -1;
    }

    char **items = calloc(total, sizeof(*items));
    if (items == NULL) {
        return -1;
    }

    result->items = items;
    result->size = total;

    for (size_t i = 0; i < total; ++i) {
        const char *source;

        if (i < first->size) {
            source = first->items[i];
        } else {
            source = second->items[i - first->size];
        }

        if (duplicate_string(source, &result->items[i]) != 0) {
            free_string_tuple(result);
            return -1;
        }
    }

    return 0;
}

int main(void)
{
    char *first_items[] = {"alpha", "beta"};
    char *second_items[] = {"gamma", "delta", "epsilon"};

    const StringTuple first = {
        first_items,
        sizeof(first_items) / sizeof(first_items[0])
    };

    const StringTuple second = {
        second_items,
        sizeof(second_items) / sizeof(second_items[0])
    };

    StringTuple result = {NULL, 0};

    if (concatenate_string_tuples(&first, &second, &result) != 0) {
        fputs("Failed to concatenate string tuples.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < result.size; ++i) {
        const char *separator = i + 1 < result.size ? ", " : "\n";

        if (printf("%s%s", result.items[i], separator) < 0) {
            free_string_tuple(&result);
            return EXIT_FAILURE;
        }
    }

    free_string_tuple(&result);
    return EXIT_SUCCESS;
}