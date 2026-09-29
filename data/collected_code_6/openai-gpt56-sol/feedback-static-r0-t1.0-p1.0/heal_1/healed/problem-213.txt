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

static int duplicate_bounded_string(const char *source,
                                    size_t maximum_length,
                                    char **destination)
{
    const char *terminator;
    size_t length;
    char *copy;

    if (source == NULL || destination == NULL) {
        return -1;
    }

    *destination = NULL;
    terminator = memchr(source, '\0', maximum_length);
    if (terminator == NULL) {
        return -1;
    }

    length = (size_t)(terminator - source);
    if (length == SIZE_MAX) {
        return -1;
    }

    copy = malloc(length + 1);
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

static int concatenate_string_tuples(const StringTuple *first,
                                     const StringTuple *second,
                                     size_t maximum_string_length,
                                     StringTuple *result)
{
    size_t total;
    size_t i;

    if (first == NULL || second == NULL || result == NULL ||
        result == first || result == second ||
        maximum_string_length == 0 ||
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
        const char *source = i < first->count
            ? first->items[i]
            : second->items[i - first->count];

        if (duplicate_bounded_string(source, maximum_string_length,
                                     &result->items[i]) != 0) {
            free_string_tuple(result);
            return -1;
        }

        result->count = i + 1;
    }

    return 0;
}

int main(void)
{
    char first_item_0[] = "alpha";
    char first_item_1[] = "beta";
    char second_item_0[] = "gamma";
    char second_item_1[] = "delta";
    char *first_items[] = {first_item_0, first_item_1};
    char *second_items[] = {second_item_0, second_item_1};
    StringTuple first = {first_items, 2};
    StringTuple second = {second_items, 2};
    StringTuple result = {NULL, 0};
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