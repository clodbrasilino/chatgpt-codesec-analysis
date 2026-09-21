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

static char *duplicate_string(const char *source, size_t max_length)
{
    if (source == NULL || max_length == 0) {
        return NULL;
    }

    const char *terminator = memchr(source, '\0', max_length);
    if (terminator == NULL) {
        return NULL;
    }

    size_t length = (size_t)(terminator - source);
    char *copy = malloc(length + 1);

    if (copy == NULL) {
        return NULL;
    }

    if (length > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(copy, source, length);
    }

    copy[length] = '\0';
    return copy;
}

static int concatenate_string_tuples(
    const StringTuple *first,
    const StringTuple *second,
    StringTuple *result,
    size_t max_string_length)
{
    if (first == NULL || second == NULL || result == NULL ||
        result == first || result == second || max_string_length == 0) {
        return -1;
    }

    result->items = NULL;
    result->size = 0;

    if ((first->size > 0 && first->items == NULL) ||
        (second->size > 0 && second->items == NULL) ||
        first->size > SIZE_MAX - second->size) {
        return -1;
    }

    size_t total = first->size + second->size;

    if (total == 0) {
        return 0;
    }

    if (total > SIZE_MAX / sizeof(char *)) {
        return -1;
    }

    char **items = calloc(total, sizeof(char *));
    if (items == NULL) {
        return -1;
    }

    StringTuple temporary = {items, total};

    for (size_t i = 0; i < total; ++i) {
        const char *source;

        if (i < first->size) {
            source = first->items[i];
        } else {
            source = second->items[i - first->size];
        }

        temporary.items[i] = duplicate_string(source, max_string_length);
        if (temporary.items[i] == NULL) {
            free_string_tuple(&temporary);
            return -1;
        }
    }

    *result = temporary;
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

    if (concatenate_string_tuples(&first, &second, &result, 1024) != 0) {
        fputs("Failed to concatenate string tuples.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < result.size; ++i) {
        if (fputs(result.items[i], stdout) == EOF ||
            fputs(i + 1 < result.size ? ", " : "\n", stdout) == EOF) {
            free_string_tuple(&result);
            return EXIT_FAILURE;
        }
    }

    free_string_tuple(&result);
    return EXIT_SUCCESS;
}