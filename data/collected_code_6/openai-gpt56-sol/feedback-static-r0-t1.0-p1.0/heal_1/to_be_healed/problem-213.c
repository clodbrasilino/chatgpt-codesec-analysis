#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    char **items;
    size_t count;
} StringTuple;

static void free_string_tuple(StringTuple *tuple)
{
    size_t i;

    if (tuple == NULL) {
        return;
    }

    for (i = 0; i < tuple->count; ++i) {
        free(tuple->items[i]);
    }

    free(tuple->items);
    tuple->items = NULL;
    tuple->count = 0;
}

static int concatenate_string_tuples(
    const StringTuple *first,
    const StringTuple *second,
    StringTuple *result)
{
    size_t total;
    size_t i;

    if (first == NULL || second == NULL || result == NULL ||
        (first->count > 0 && first->items == NULL) ||
        (second->count > 0 && second->items == NULL) ||
        first->count > SIZE_MAX - second->count) {
        return -1;
    }

    result->items = NULL;
    result->count = 0;
    total = first->count + second->count;

    if (total == 0) {
        return 0;
    }

    if (total > SIZE_MAX / sizeof(*result->items)) {
        return -1;
    }

    result->items = calloc(total, sizeof(*result->items));
    if (result->items == NULL) {
        return -1;
    }

    for (i = 0; i < total; ++i) {
        const char *source;
        size_t length;

        source = i < first->count
            ? first->items[i]
            : second->items[i - first->count];

        if (source == NULL) {
            free_string_tuple(result);
            return -1;
        }

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        length = strlen(source);
        if (length == SIZE_MAX) {
            free_string_tuple(result);
            return -1;
        }

        result->items[i] = malloc(length + 1);
        if (result->items[i] == NULL) {
            result->count = i;
            free_string_tuple(result);
            return -1;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result->items[i], source, length + 1);
        result->count = i + 1;
    }

    return 0;
}

int main(void)
{
    char *first_items[] = {"alpha", "beta"};
    char *second_items[] = {"gamma", "delta"};
    StringTuple first = {first_items, 2};
    StringTuple second = {second_items, 2};
    StringTuple result = {NULL, 0};
    size_t i;

    if (concatenate_string_tuples(&first, &second, &result) != 0) {
        fputs("Failed to concatenate string tuples.\n", stderr);
        return EXIT_FAILURE;
    }

    for (i = 0; i < result.count; ++i) {
        if (printf("%s%s", result.items[i],
                   i + 1 < result.count ? ", " : "\n") < 0) {
            free_string_tuple(&result);
            return EXIT_FAILURE;
        }
    }

    free_string_tuple(&result);
    return EXIT_SUCCESS;
}