#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    int *items;
    size_t length;
} Tuple;

typedef struct {
    Tuple *tuples;
    size_t length;
} TupleList;

static void free_tuple_list(TupleList *list)
{
    if (list == NULL) {
        return;
    }

    for (size_t i = 0; i < list->length; ++i) {
        free(list->tuples[i].items);
        list->tuples[i].items = NULL;
        list->tuples[i].length = 0;
    }

    free(list->tuples);
    list->tuples = NULL;
    list->length = 0;
}

static void remove_empty_tuples(TupleList *list)
{
    if (list == NULL || list->tuples == NULL) {
        return;
    }

    size_t output = 0;

    for (size_t input = 0; input < list->length; ++input) {
        if (list->tuples[input].length == 0) {
            free(list->tuples[input].items);
            list->tuples[input].items = NULL;
            continue;
        }

        if (output != input) {
            list->tuples[output] = list->tuples[input];
        }

        ++output;
    }

    list->length = output;

    if (output == 0) {
        free(list->tuples);
        list->tuples = NULL;
        return;
    }

    if (output <= SIZE_MAX / sizeof(*list->tuples)) {
        Tuple *resized = realloc(list->tuples,
                                 output * sizeof(*list->tuples));
        if (resized != NULL) {
            list->tuples = resized;
        }
    }
}

static int print_tuple_list(const TupleList *list)
{
    if (list == NULL || (list->length != 0 && list->tuples == NULL)) {
        return -1;
    }

    if (putchar('[') == EOF) {
        return -1;
    }

    for (size_t i = 0; i < list->length; ++i) {
        const Tuple *tuple = &list->tuples[i];

        if (tuple->length != 0 && tuple->items == NULL) {
            return -1;
        }

        if (putchar('(') == EOF) {
            return -1;
        }

        for (size_t j = 0; j < tuple->length; ++j) {
            if (j != 0 && fputs(", ", stdout) == EOF) {
                return -1;
            }

            if (printf("%d", tuple->items[j]) < 0) {
                return -1;
            }
        }

        if (putchar(')') == EOF) {
            return -1;
        }

        if (i + 1 < list->length && fputs(", ", stdout) == EOF) {
            return -1;
        }
    }

    if (puts("]") == EOF) {
        return -1;
    }

    return ferror(stdout) ? -1 : 0;
}

static int initialize_tuple(Tuple *tuple, const int *source,
                            size_t source_length, size_t length)
{
    if (tuple == NULL || length > source_length ||
        (length != 0 && source == NULL)) {
        return -1;
    }

    tuple->items = NULL;
    tuple->length = 0;

    if (length == 0) {
        return 0;
    }

    if (length > SIZE_MAX / sizeof(*tuple->items)) {
        return -1;
    }

    size_t bytes = length * sizeof(*tuple->items);
    tuple->items = malloc(bytes);

    if (tuple->items == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(tuple->items, source, bytes);
    tuple->length = length;
    return 0;
}

int main(void)
{
    TupleList list = {0};
    static const size_t lengths[] = {2, 0, 3, 0};
    static const int values[][3] = {
        {1, 2, 0},
        {0, 0, 0},
        {3, 4, 5},
        {0, 0, 0}
    };
    const size_t tuple_count = sizeof(lengths) / sizeof(lengths[0]);
    const size_t value_count = sizeof(values) / sizeof(values[0]);
    const size_t value_capacity = sizeof(values[0]) / sizeof(values[0][0]);

    if (tuple_count != value_count ||
        tuple_count > SIZE_MAX / sizeof(*list.tuples)) {
        fputs("Invalid tuple data.\n", stderr);
        return EXIT_FAILURE;
    }

    list.tuples = calloc(tuple_count, sizeof(*list.tuples));
    if (list.tuples == NULL && tuple_count != 0) {
        fputs("Failed to allocate tuple list.\n", stderr);
        return EXIT_FAILURE;
    }

    list.length = tuple_count;

    for (size_t i = 0; i < tuple_count; ++i) {
        if (initialize_tuple(&list.tuples[i], values[i], value_capacity,
                             lengths[i]) != 0) {
            fputs("Failed to initialize tuple.\n", stderr);
            free_tuple_list(&list);
            return EXIT_FAILURE;
        }
    }

    remove_empty_tuples(&list);

    if (print_tuple_list(&list) != 0) {
        fputs("Failed to print tuple list.\n", stderr);
        free_tuple_list(&list);
        return EXIT_FAILURE;
    }

    free_tuple_list(&list);
    return EXIT_SUCCESS;
}