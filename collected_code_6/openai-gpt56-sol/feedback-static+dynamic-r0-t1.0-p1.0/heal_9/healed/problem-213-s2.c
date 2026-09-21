#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **items;
    size_t size;
} StringTuple;

static void free_string_tuple(StringTuple *tuple)
{
    if (tuple == NULL) {
        return;
    }

    if (tuple->items != NULL) {
        for (size_t i = 0; i < tuple->size; ++i) {
            free(tuple->items[i]);
        }
        free(tuple->items);
    }

    tuple->items = NULL;
    tuple->size = 0;
}

static int duplicate_string(const char *source, size_t source_size,
                            char **destination)
{
    if (source == NULL || destination == NULL || source_size == 0) {
        return -1;
    }

    *destination = NULL;

    const char *terminator = memchr(source, '\0', source_size);
    if (terminator == NULL) {
        return -1;
    }

    size_t length = (size_t)(terminator - source);
    if (length == SIZE_MAX) {
        return -1;
    }

    size_t allocation_size = length + 1;
    char *copy = malloc(allocation_size);
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
    const size_t *first_item_sizes,
    const StringTuple *second,
    const size_t *second_item_sizes,
    StringTuple *result)
{
    if (first == NULL || second == NULL || result == NULL ||
        result == first || result == second) {
        return -1;
    }

    result->items = NULL;
    result->size = 0;

    if ((first->size > 0 &&
         (first->items == NULL || first_item_sizes == NULL)) ||
        (second->size > 0 &&
         (second->items == NULL || second_item_sizes == NULL)) ||
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

    char **items = calloc(total, sizeof(*items));
    if (items == NULL) {
        return -1;
    }

    StringTuple temporary = {items, total};

    for (size_t i = 0; i < total; ++i) {
        const char *source;
        size_t source_size;

        if (i < first->size) {
            source = first->items[i];
            source_size = first_item_sizes[i];
        } else {
            size_t index = i - first->size;
            source = second->items[index];
            source_size = second_item_sizes[index];
        }

        if (duplicate_string(source, source_size,
                             &temporary.items[i]) != 0) {
            free_string_tuple(&temporary);
            return -1;
        }
    }

    *result = temporary;
    return 0;
}

int main(void)
{
    char first_0[] = "alpha";
    char first_1[] = "beta";
    char second_0[] = "gamma";
    char second_1[] = "delta";
    char second_2[] = "epsilon";

    char *first_items[] = {
        first_0,
        first_1
    };

    const size_t first_item_sizes[] = {
        sizeof(first_0),
        sizeof(first_1)
    };

    char *second_items[] = {
        second_0,
        second_1,
        second_2
    };

    const size_t second_item_sizes[] = {
        sizeof(second_0),
        sizeof(second_1),
        sizeof(second_2)
    };

    const StringTuple first = {
        first_items,
        sizeof(first_items) / sizeof(first_items[0])
    };

    const StringTuple second = {
        second_items,
        sizeof(second_items) / sizeof(second_items[0])
    };

    StringTuple result = {NULL, 0};

    if (concatenate_string_tuples(
            &first,
            first_item_sizes,
            &second,
            second_item_sizes,
            &result) != 0) {
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