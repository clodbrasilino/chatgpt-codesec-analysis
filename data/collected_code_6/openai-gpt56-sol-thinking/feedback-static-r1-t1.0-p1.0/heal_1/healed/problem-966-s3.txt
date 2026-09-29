#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *values;
    size_t length;
} Tuple;

typedef struct {
    Tuple *items;
    size_t length;
    size_t capacity;
} TupleList;

static int tuple_list_init(TupleList *list, size_t length)
{
    if (list == NULL) {
        return -1;
    }

    list->items = NULL;
    list->length = 0;
    list->capacity = 0;

    if (length == 0) {
        return 0;
    }

    if (length > SIZE_MAX / sizeof(*list->items)) {
        return -1;
    }

    list->items = calloc(length, sizeof(*list->items));
    if (list->items == NULL) {
        return -1;
    }

    list->length = length;
    list->capacity = length;
    return 0;
}

static int tuple_set(Tuple *tuple, const int *values, size_t length)
{
    int *new_values = NULL;

    if (tuple == NULL || (length > 0 && values == NULL)) {
        return -1;
    }

    if (length > SIZE_MAX / sizeof(*new_values)) {
        return -1;
    }

    if (length > 0) {
        new_values = malloc(length * sizeof(*new_values));
        if (new_values == NULL) {
            return -1;
        }

        for (size_t i = 0; i < length; ++i) {
            new_values[i] = values[i];
        }
    }

    free(tuple->values);
    tuple->values = new_values;
    tuple->length = length;
    return 0;
}

static int tuple_list_is_valid(const TupleList *list)
{
    if (list == NULL || list->length > list->capacity ||
        (list->capacity > 0 && list->items == NULL)) {
        return 0;
    }

    for (size_t i = 0; i < list->length; ++i) {
        if (list->items[i].length > 0 &&
            list->items[i].values == NULL) {
            return 0;
        }
    }

    return 1;
}

static int remove_empty_tuples(TupleList *list)
{
    size_t destination = 0;

    if (!tuple_list_is_valid(list)) {
        return -1;
    }

    for (size_t source = 0; source < list->length; ++source) {
        Tuple *tuple = &list->items[source];

        if (tuple->length == 0) {
            free(tuple->values);
            tuple->values = NULL;
            continue;
        }

        if (destination != source) {
            list->items[destination] = *tuple;
            tuple->values = NULL;
            tuple->length = 0;
        }

        ++destination;
    }

    list->length = destination;
    return 0;
}

static int tuple_list_print(const TupleList *list)
{
    if (!tuple_list_is_valid(list)) {
        return -1;
    }

    if (putchar('[') == EOF) {
        return -1;
    }

    for (size_t i = 0; i < list->length; ++i) {
        if (i > 0 && fputs(", ", stdout) == EOF) {
            return -1;
        }

        if (putchar('(') == EOF) {
            return -1;
        }

        for (size_t j = 0; j < list->items[i].length; ++j) {
            if (j > 0 && fputs(", ", stdout) == EOF) {
                return -1;
            }

            if (printf("%d", list->items[i].values[j]) < 0) {
                return -1;
            }
        }

        if (putchar(')') == EOF) {
            return -1;
        }
    }

    if (fputs("]\n", stdout) == EOF) {
        return -1;
    }

    return 0;
}

static void tuple_list_destroy(TupleList *list)
{
    if (list == NULL) {
        return;
    }

    if (list->items != NULL) {
        for (size_t i = 0; i < list->capacity; ++i) {
            free(list->items[i].values);
            list->items[i].values = NULL;
            list->items[i].length = 0;
        }

        free(list->items);
    }

    list->items = NULL;
    list->length = 0;
    list->capacity = 0;
}

int main(void)
{
    const int first[] = {1, 2};
    const int third[] = {3, 4, 5};
    const int fifth[] = {6};
    TupleList list = {0};
    int status = EXIT_FAILURE;

    if (tuple_list_init(&list, 5) != 0) {
        goto cleanup;
    }

    if (tuple_set(&list.items[0], first,
                  sizeof(first) / sizeof(first[0])) != 0 ||
        tuple_set(&list.items[2], third,
                  sizeof(third) / sizeof(third[0])) != 0 ||
        tuple_set(&list.items[4], fifth,
                  sizeof(fifth) / sizeof(fifth[0])) != 0) {
        goto cleanup;
    }

    if (fputs("Before: ", stdout) == EOF ||
        tuple_list_print(&list) != 0) {
        goto cleanup;
    }

    if (remove_empty_tuples(&list) != 0) {
        goto cleanup;
    }

    if (fputs("After: ", stdout) == EOF ||
        tuple_list_print(&list) != 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    tuple_list_destroy(&list);
    return status;
}