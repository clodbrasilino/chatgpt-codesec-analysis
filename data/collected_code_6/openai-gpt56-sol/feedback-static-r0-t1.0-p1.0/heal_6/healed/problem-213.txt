#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

static int duplicate_bounded_string(const char *source,
                                    size_t maximum_length,
                                    char **destination)
{
    const char *terminator;
    size_t length;
    size_t allocation_size;
    char *copy;

    if (source == NULL || destination == NULL || maximum_length == 0) {
        return -1;
    }

    *destination = NULL;

    terminator = memchr(source, '\0', maximum_length);
    if (terminator == NULL) {
        return -1;
    }

    length = (size_t)(terminator - source);

    if (length > SIZE_MAX - 1) {
        return -1;
    }

    allocation_size = length + 1;
    copy = malloc(allocation_size);
    if (copy == NULL) {
        return -1;
    }

    memcpy(copy, source, allocation_size);

    *destination = copy;
    return 0;
}

static int concatenate_string_tuples(const StringTuple *first,
                                     const StringTuple *second,
                                     size_t maximum_string_length,
                                     StringTuple *result)
{
    StringTuple temporary = { NULL, 0 };
    size_t total;
    size_t i;

    if (first == NULL || second == NULL || result == NULL ||
        result == first || result == second ||
        maximum_string_length == 0 ||
        (first->count != 0 && first->items == NULL) ||
        (second->count != 0 && second->items == NULL) ||
        first->count > SIZE_MAX - second->count) {
        return -1;
    }

    total = first->count + second->count;

    if (total == 0) {
        result->items = NULL;
        result->count = 0;
        return 0;
    }

    if (total > SIZE_MAX / sizeof(*temporary.items)) {
        return -1;
    }

    temporary.items = calloc(total, sizeof(*temporary.items));
    if (temporary.items == NULL) {
        return -1;
    }

    for (i = 0; i < total; ++i) {
        const char *source;

        if (i < first->count) {
            source = first->items[i];
        } else {
            source = second->items[i - first->count];
        }

        if (source == NULL ||
            duplicate_bounded_string(source, maximum_string_length,
                                     &temporary.items[i]) != 0) {
            free_string_tuple(&temporary);
            return -1;
        }

        ++temporary.count;
    }

    result->items = temporary.items;
    result->count = temporary.count;
    return 0;
}

int main(void)
{
    char first_item_0[] = "alpha";
    char first_item_1[] = "beta";
    char second_item_0[] = "gamma";
    char second_item_1[] = "delta";
    char *first_items[] = { first_item_0, first_item_1 };
    char *second_items[] = { second_item_0, second_item_1 };
    StringTuple first = { first_items, 2 };
    StringTuple second = { second_items, 2 };
    StringTuple result = { NULL, 0 };
    size_t i;

    if (concatenate_string_tuples(&first, &second, 1024, &result) != 0) {
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