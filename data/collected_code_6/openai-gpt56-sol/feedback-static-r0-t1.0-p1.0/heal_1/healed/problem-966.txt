#include <stdio.h>
#include <stdlib.h>

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
            list->tuples[input].items = NULL;
            list->tuples[input].length = 0;
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
        if (list->tuples[i].length != 0 &&
            list->tuples[i].items == NULL) {
            return -1;
        }

        if (putchar('(') == EOF) {
            return -1;
        }

        for (size_t j = 0; j < list->tuples[i].length; ++j) {
            if (j != 0 && fputs(", ", stdout) == EOF) {
                return -1;
            }

            if (printf("%d", list->tuples[i].items[j]) < 0) {
                return -1;
            }
        }

        if (putchar(')') == EOF) {
            return -1;
        }

        if (i + 1 < list->length &&
            fputs(", ", stdout) == EOF) {
            return -1;
        }
    }

    if (puts("]") == EOF) {
        return -1;
    }

    return ferror(stdout) ? -1 : 0;
}

int main(void)
{
    static const size_t lengths[] = {2, 0, 3, 0};
    static const int values[][3] = {
        {1, 2, 0},
        {0, 0, 0},
        {3, 4, 5},
        {0, 0, 0}
    };

    TupleList list = {NULL, 0};
    const size_t tuple_count = sizeof(lengths) / sizeof(lengths[0]);
    const size_t value_count = sizeof(values) / sizeof(values[0]);
    const size_t value_capacity = sizeof(values[0]) / sizeof(values[0][0]);

    if (tuple_count != value_count ||
        tuple_count > SIZE_MAX / sizeof(*list.tuples)) {
        fputs("Invalid tuple data.\n", stderr);
        return EXIT_FAILURE;
    }

    list.tuples = calloc(tuple_count, sizeof(*list.tuples));
    if (list.tuples == NULL) {
        fputs("Failed to allocate tuple list.\n", stderr);
        return EXIT_FAILURE;
    }

    list.length = tuple_count;

    for (size_t i = 0; i < tuple_count; ++i) {
        if (lengths[i] > value_capacity ||
            lengths[i] > SIZE_MAX / sizeof(*list.tuples[i].items)) {
            fputs("Invalid tuple length.\n", stderr);
            free_tuple_list(&list);
            return EXIT_FAILURE;
        }

        list.tuples[i].length = lengths[i];

        if (lengths[i] == 0) {
            continue;
        }

        list.tuples[i].items =
            malloc(lengths[i] * sizeof(*list.tuples[i].items));

        if (list.tuples[i].items == NULL) {
            fputs("Failed to allocate tuple.\n", stderr);
            free_tuple_list(&list);
            return EXIT_FAILURE;
        }

        for (size_t j = 0; j < lengths[i]; ++j) {
            list.tuples[i].items[j] = values[i][j];
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