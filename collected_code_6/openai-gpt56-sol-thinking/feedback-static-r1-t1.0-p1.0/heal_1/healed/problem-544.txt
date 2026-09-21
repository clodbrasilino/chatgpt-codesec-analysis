#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const char *data;
    size_t length;
} StringItem;

typedef struct {
    const StringItem *items;
    size_t count;
} StringTuple;

static int append_bytes(char *destination,
                        size_t capacity,
                        size_t *position,
                        const char *source,
                        size_t length)
{
    if (destination == NULL || position == NULL || source == NULL) {
        return -1;
    }

    if (*position > capacity || length > capacity - *position) {
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
                       const char *separator,
                       size_t separator_length,
                       char **result)
{
    size_t total_length = 0;
    size_t position = 0;
    int has_item = 0;
    char *flattened;

    if (result == NULL || separator == NULL) {
        return -1;
    }

    *result = NULL;

    if (tuple_count != 0 && tuples == NULL) {
        return -1;
    }

    for (size_t i = 0; i < tuple_count; ++i) {
        if (tuples[i].count != 0 && tuples[i].items == NULL) {
            return -1;
        }

        for (size_t j = 0; j < tuples[i].count; ++j) {
            const StringItem *item = &tuples[i].items[j];

            if (item->data == NULL) {
                return -1;
            }

            if (has_item) {
                if (separator_length > SIZE_MAX - total_length) {
                    return -1;
                }

                total_length += separator_length;
            }

            if (item->length > SIZE_MAX - total_length) {
                return -1;
            }

            total_length += item->length;
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
            const StringItem *item = &tuples[i].items[j];

            if (has_item &&
                append_bytes(flattened,
                             total_length,
                             &position,
                             separator,
                             separator_length) != 0) {
                free(flattened);
                return -1;
            }

            if (append_bytes(flattened,
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
    static const StringItem tuple1[] = {
        {"alpha", sizeof("alpha") - 1},
        {"beta", sizeof("beta") - 1}
    };

    static const StringItem tuple2[] = {
        {"gamma", sizeof("gamma") - 1},
        {"delta", sizeof("delta") - 1},
        {"epsilon", sizeof("epsilon") - 1}
    };

    static const StringItem tuple3[] = {
        {"zeta", sizeof("zeta") - 1}
    };

    static const StringTuple tuples[] = {
        {tuple1, sizeof(tuple1) / sizeof(tuple1[0])},
        {tuple2, sizeof(tuple2) / sizeof(tuple2[0])},
        {tuple3, sizeof(tuple3) / sizeof(tuple3[0])}
    };

    static const char separator[] = ", ";
    char *flattened = NULL;

    if (flatten_tuple_list(
            tuples,
            sizeof(tuples) / sizeof(tuples[0]),
            separator,
            sizeof(separator) - 1,
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