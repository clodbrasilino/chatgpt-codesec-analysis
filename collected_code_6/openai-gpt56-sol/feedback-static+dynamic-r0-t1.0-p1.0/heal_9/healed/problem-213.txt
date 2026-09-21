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
    if (tuple == NULL) {
        return;
    }

    for (size_t i = 0; i < tuple->count; ++i) {
        free(tuple->items[i]);
    }

    free(tuple->items);
    tuple->items = NULL;
    tuple->count = 0;
}

static int duplicate_string(const char *source, size_t source_size,
                            char **destination)
{
    if (source == NULL || source_size == 0 || destination == NULL) {
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

static int concatenate_string_tuples(const StringTuple *first,
                                     const size_t *first_sizes,
                                     const StringTuple *second,
                                     const size_t *second_sizes,
                                     StringTuple *result)
{
    if (first == NULL || second == NULL || result == NULL ||
        result == first || result == second) {
        return -1;
    }

    result->items = NULL;
    result->count = 0;

    if ((first->count > 0 &&
         (first->items == NULL || first_sizes == NULL)) ||
        (second->count > 0 &&
         (second->items == NULL || second_sizes == NULL))) {
        return -1;
    }

    if (first->count > SIZE_MAX - second->count) {
        return -1;
    }

    size_t total = first->count + second->count;
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

    for (size_t i = 0; i < total; ++i) {
        const char *source;
        size_t source_size;

        if (i < first->count) {
            source = first->items[i];
            source_size = first_sizes[i];
        } else {
            size_t index = i - first->count;
            source = second->items[index];
            source_size = second_sizes[index];
        }

        if (duplicate_string(source, source_size, &result->items[i]) != 0) {
            result->count = i;
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

    char *first_items[] = {
        first_item_0,
        first_item_1
    };

    char *second_items[] = {
        second_item_0,
        second_item_1
    };

    const size_t first_sizes[] = {
        sizeof(first_item_0),
        sizeof(first_item_1)
    };

    const size_t second_sizes[] = {
        sizeof(second_item_0),
        sizeof(second_item_1)
    };

    StringTuple first = {
        first_items,
        sizeof(first_items) / sizeof(first_items[0])
    };

    StringTuple second = {
        second_items,
        sizeof(second_items) / sizeof(second_items[0])
    };

    StringTuple result = {NULL, 0};

    if (concatenate_string_tuples(&first, first_sizes,
                                  &second, second_sizes,
                                  &result) != 0) {
        fputs("Failed to concatenate string tuples.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < result.count; ++i) {
        if (fputs(result.items[i], stdout) == EOF ||
            (i + 1 < result.count
                 ? fputs(", ", stdout) == EOF
                 : fputc('\n', stdout) == EOF)) {
            free_string_tuple(&result);
            return EXIT_FAILURE;
        }
    }

    free_string_tuple(&result);
    return EXIT_SUCCESS;
}