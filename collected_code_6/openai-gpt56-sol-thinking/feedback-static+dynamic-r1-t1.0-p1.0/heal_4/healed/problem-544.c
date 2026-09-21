#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const char *data;
    size_t length;
} StringSlice;

typedef struct {
    const StringSlice *items;
    size_t count;
} StringTuple;

static int checked_add_size(size_t left, size_t right, size_t *result)
{
    if (result == NULL || left > SIZE_MAX - right) {
        return -1;
    }

    *result = left + right;
    return 0;
}

static int append_data(char *destination,
                       size_t capacity,
                       size_t *position,
                       const char *source,
                       size_t length)
{
    size_t available;

    if (destination == NULL || position == NULL) {
        return -1;
    }

    if (length != 0 && source == NULL) {
        return -1;
    }

    if (*position >= capacity) {
        return -1;
    }

    available = capacity - *position;

    if (length >= available) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        destination[*position + i] = source[i];
    }

    *position += length;
    return 0;
}

int flatten_tuple_list(const StringTuple *tuples,
                       size_t tuple_count,
                       StringSlice separator,
                       char **result)
{
    size_t total_length = 0;
    size_t allocation_size;
    size_t position = 0;
    int has_item = 0;
    char *flattened;

    if (result == NULL) {
        return -1;
    }

    *result = NULL;

    if (separator.length != 0 && separator.data == NULL) {
        return -1;
    }

    if (tuple_count != 0 && tuples == NULL) {
        return -1;
    }

    for (size_t i = 0; i < tuple_count; ++i) {
        const StringTuple *tuple = &tuples[i];

        if (tuple->count != 0 && tuple->items == NULL) {
            return -1;
        }

        for (size_t j = 0; j < tuple->count; ++j) {
            const StringSlice *item = &tuple->items[j];

            if (item->length != 0 && item->data == NULL) {
                return -1;
            }

            if (has_item &&
                checked_add_size(total_length,
                                 separator.length,
                                 &total_length) != 0) {
                return -1;
            }

            if (checked_add_size(total_length,
                                 item->length,
                                 &total_length) != 0) {
                return -1;
            }

            has_item = 1;
        }
    }

    if (checked_add_size(total_length, 1, &allocation_size) != 0) {
        return -1;
    }

    flattened = malloc(allocation_size);
    if (flattened == NULL) {
        return -1;
    }

    has_item = 0;

    for (size_t i = 0; i < tuple_count; ++i) {
        const StringTuple *tuple = &tuples[i];

        for (size_t j = 0; j < tuple->count; ++j) {
            const StringSlice *item = &tuple->items[j];

            if (has_item &&
                append_data(flattened,
                            allocation_size,
                            &position,
                            separator.data,
                            separator.length) != 0) {
                free(flattened);
                return -1;
            }

            if (append_data(flattened,
                            allocation_size,
                            &position,
                            item->data,
                            item->length) != 0) {
                free(flattened);
                return -1;
            }

            has_item = 1;
        }
    }

    if (position != total_length || position >= allocation_size) {
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

    const StringSlice separator = {
        ", ",
        sizeof(", ") - 1
    };

    char *flattened = NULL;

    if (flatten_tuple_list(tuples,
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