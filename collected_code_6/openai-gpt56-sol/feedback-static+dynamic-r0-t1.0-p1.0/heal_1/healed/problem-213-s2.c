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

    const size_t max_length = SIZE_MAX - 1;
    const char *terminator = memchr(source, '\0', max_length);

    if (terminator == NULL) {
        return -1;
    }

    const size_t length = (size_t)(terminator - source);
    char *copy = malloc(length + 1);

    if (copy == NULL) {
        return -1;
    }

    if (length > 0) {
        memcpy(copy, source, length);
    }
    copy[length] = '\0';

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

    if ((first->size > 0 && first->items == NULL) ||
        (second->size > 0 && second->items == NULL) ||
        first->size > SIZE_MAX - second->size) {
        return -1;
    }

    const size_t total = first->size + second->size;

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

    result->size = total;

    for (size_t i = 0; i < total; ++i) {
        const char *source = i < first->size
            ? first->items[i]
            : second->items[i - first->size];

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
        if (printf("%s%s",
                   result.items[i],
                   i + 1 < result.size ? ", " : "\n") < 0) {
            free_string_tuple(&result);
            return EXIT_FAILURE;
        }
    }

    free_string_tuple(&result);
    return EXIT_SUCCESS;
}