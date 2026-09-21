#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *data;
    size_t length;
} StringSlice;

typedef struct {
    const StringSlice *items;
    size_t count;
} StringTuple;

static int checked_add_size(size_t *value, size_t amount)
{
    if (value == NULL || amount > SIZE_MAX - *value) {
        return -1;
    }

    *value += amount;
    return 0;
}

static int append_data(char *destination,
                       size_t capacity,
                       size_t *position,
                       const char *source,
                       size_t length)
{
    if (destination == NULL || position == NULL) {
        return -1;
    }

    if (length > 0 && source == NULL) {
        return -1;
    }

    if (*position > capacity || length > capacity - *position) {
        return -1;
    }

    if (length > 0) {
        memcpy(destination + *position, source, length);
        *position += length;
    }

    return 0;
}

int flatten_tuple_list(const StringTuple *tuples,
                       size_t tuple_count,
                       StringSlice separator,
                       char **result)
{
    size_t total_length = 0;
    size_t position = 0;
    int has_item = 0;
    char *flattened;

    if (result == NULL) {
        return -1;
    }

    *result = NULL;

    if (separator.length > 0 && separator.data == NULL) {
        return -1;
    }

    if (tuple_count > 0 && tuples == NULL) {
        return -1;
    }

    for (size_t i = 0; i < tuple_count; ++i) {
        if (tuples[i].count > 0 && tuples[i].items == NULL) {
            return -1;
        }

        for (size_t j = 0; j < tuples[i].count; ++j) {
            const StringSlice *item = &tuples[i].items[j];

            if (item->length > 0 && item->data == NULL) {
                return -1;
            }

            if (has_item &&
                checked_add_size(&total_length, separator.length) != 0) {
                return -1;
            }

            if (checked_add_size(&total_length, item->length) != 0) {
                return -1;
            }

            has_item = 1;
        }
    }

    if (total_length == SIZE_MAX) {
        return -1;
    }

    flattened = malloc(total_length + 1);
    if (flattened == NULL) {
        return -1;
    }

    has_item = 0;

    for (size_t i = 0; i < tuple_count; ++i) {
        for (size_t j = 0; j < tuples[i].count; ++j) {
            const StringSlice *item = &tuples[i].items[j];

            if (has_item &&
                append_data(flattened,
                            total_length,
                            &position,
                            separator.data,
                            separator.length) != 0) {
                free(flattened);
                return -1;
            }

            if (append_data(flattened,
                            total_length,
                            &position,
                            item->data,
                            item->length) != 0) {
                free(flattened);
                return -1;
            }

            has_item = 1;
        }
    }

    if (position != total_length) {
        free(flattened);
        return -1;
    }

    flattened[position] = '\0';
    *result = flattened;

    return 0;
}

int main(void)
{
    const StringSlice tuple1[] = {
        {"alpha", sizeof("alpha") - 1},
        {"beta", sizeof("beta") - 1}
    };
    const StringSlice tuple2[] = {
        {"gamma", sizeof("gamma") - 1},
        {"delta", sizeof("delta") - 1},
        {"epsilon", sizeof("epsilon") - 1}
    };
    const StringSlice tuple3[] = {
        {"zeta", sizeof("zeta") - 1}
    };
    const StringTuple tuples[] = {
        {tuple1, sizeof(tuple1) / sizeof(tuple1[0])},
        {tuple2, sizeof(tuple2) / sizeof(tuple2[0])},
        {tuple3, sizeof(tuple3) / sizeof(tuple3[0])}
    };
    const StringSlice separator = {", ", sizeof(", ") - 1};
    char *flattened = NULL;

    if (flatten_tuple_list(
            tuples,
            sizeof(tuples) / sizeof(tuples[0]),
            separator,
            &flattened) != 0) {
        fputs("Failed to flatten tuple list.\n", stderr);
        return EXIT_FAILURE;
    }

    if (puts(flattened) == EOF) {
        free(flattened);
        return EXIT_FAILURE;
    }

    free(flattened);
    return EXIT_SUCCESS;
}