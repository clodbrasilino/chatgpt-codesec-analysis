#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *items;
    size_t size;
} Tuple;

typedef struct {
    Tuple *tuples;
    size_t size;
} TupleList;

static int remove_empty_tuples(TupleList *list)
{
    size_t write_index = 0;

    if (list == NULL || (list->size > 0 && list->tuples == NULL)) {
        return -1;
    }

    for (size_t read_index = 0; read_index < list->size; ++read_index) {
        if (list->tuples[read_index].size > 0) {
            if (list->tuples[read_index].items == NULL) {
                return -1;
            }

            if (write_index != read_index) {
                list->tuples[write_index] = list->tuples[read_index];
                list->tuples[read_index].items = NULL;
                list->tuples[read_index].size = 0;
            }

            ++write_index;
        } else {
            free(list->tuples[read_index].items);
            list->tuples[read_index].items = NULL;
        }
    }

    if (write_index == 0) {
        free(list->tuples);
        list->tuples = NULL;
    } else if (write_index < list->size) {
        Tuple *resized = realloc(list->tuples,
                                 write_index * sizeof(*list->tuples));

        if (resized != NULL) {
            list->tuples = resized;
        }
    }

    list->size = write_index;
    return 0;
}

static void free_tuple_list(TupleList *list)
{
    if (list == NULL) {
        return;
    }

    if (list->tuples != NULL) {
        for (size_t i = 0; i < list->size; ++i) {
            free(list->tuples[i].items);
        }

        free(list->tuples);
    }

    list->tuples = NULL;
    list->size = 0;
}

static int initialize_tuple(Tuple *tuple, const int *values, size_t size)
{
    if (tuple == NULL || (size > 0 && values == NULL)) {
        return -1;
    }

    tuple->items = NULL;
    tuple->size = 0;

    if (size == 0) {
        return 0;
    }

    if (size > SIZE_MAX / sizeof(*tuple->items)) {
        return -1;
    }

    size_t byte_count = size * sizeof(*tuple->items);
    int *items = malloc(byte_count);

    if (items == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(items, values, byte_count);
    tuple->items = items;
    tuple->size = size;

    return 0;
}

static int print_tuple_list(const TupleList *list)
{
    if (list == NULL || (list->size > 0 && list->tuples == NULL)) {
        return -1;
    }

    for (size_t i = 0; i < list->size; ++i) {
        if (list->tuples[i].size > 0 && list->tuples[i].items == NULL) {
            return -1;
        }

        if (putchar('(') == EOF) {
            return -1;
        }

        for (size_t j = 0; j < list->tuples[i].size; ++j) {
            if (j > 0 && printf(", ") < 0) {
                return -1;
            }

            if (printf("%d", list->tuples[i].items[j]) < 0) {
                return -1;
            }
        }

        if (puts(")") == EOF) {
            return -1;
        }
    }

    return 0;
}

int main(void)
{
    const int first[] = {1, 2};
    const int third[] = {3};
    TupleList list = {NULL, 0};
    int status = EXIT_FAILURE;

    list.size = 4;
    list.tuples = calloc(list.size, sizeof(*list.tuples));

    if (list.tuples == NULL) {
        goto cleanup;
    }

    if (initialize_tuple(&list.tuples[0], first,
                         sizeof(first) / sizeof(first[0])) != 0 ||
        initialize_tuple(&list.tuples[1], NULL, 0) != 0 ||
        initialize_tuple(&list.tuples[2], third,
                         sizeof(third) / sizeof(third[0])) != 0 ||
        initialize_tuple(&list.tuples[3], NULL, 0) != 0) {
        goto cleanup;
    }

    if (remove_empty_tuples(&list) != 0) {
        goto cleanup;
    }

    if (print_tuple_list(&list) != 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free_tuple_list(&list);
    return status;
}