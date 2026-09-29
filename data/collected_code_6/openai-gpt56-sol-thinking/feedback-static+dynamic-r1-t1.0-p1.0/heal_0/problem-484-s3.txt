#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *items;
    size_t size;
} Tuple;

static void tuple_destroy(Tuple *tuple)
{
    if (tuple != NULL) {
        free(tuple->items);
        tuple->items = NULL;
        tuple->size = 0;
    }
}

static bool tuple_init(Tuple *tuple, const int *items, size_t size)
{
    if (tuple == NULL || (size > 0 && items == NULL) ||
        size > SIZE_MAX / sizeof(*tuple->items)) {
        return false;
    }

    tuple->items = NULL;
    tuple->size = 0;

    if (size == 0) {
        return true;
    }

    tuple->items = malloc(size * sizeof(*tuple->items));
    if (tuple->items == NULL) {
        return false;
    }

    memcpy(tuple->items, items, size * sizeof(*tuple->items));
    tuple->size = size;
    return true;
}

static bool remove_matching_tuples(Tuple *first, Tuple *second)
{
    unsigned char *remove_first = NULL;
    unsigned char *remove_second = NULL;
    int *new_first = NULL;
    int *new_second = NULL;
    size_t first_remaining;
    size_t second_remaining;
    size_t first_index = 0;
    size_t second_index = 0;

    if (first == NULL || second == NULL || first == second ||
        (first->size > 0 && first->items == NULL) ||
        (second->size > 0 && second->items == NULL)) {
        return false;
    }

    if (first->size > 0) {
        remove_first = calloc(first->size, sizeof(*remove_first));
        if (remove_first == NULL) {
            return false;
        }
    }

    if (second->size > 0) {
        remove_second = calloc(second->size, sizeof(*remove_second));
        if (remove_second == NULL) {
            free(remove_first);
            return false;
        }
    }

    first_remaining = first->size;
    second_remaining = second->size;

    for (size_t i = 0; i < first->size; ++i) {
        for (size_t j = 0; j < second->size; ++j) {
            if (remove_second[j] == 0 && first->items[i] == second->items[j]) {
                remove_first[i] = 1;
                remove_second[j] = 1;
                --first_remaining;
                --second_remaining;
                break;
            }
        }
    }

    if (first_remaining > 0) {
        if (first_remaining > SIZE_MAX / sizeof(*new_first)) {
            free(remove_first);
            free(remove_second);
            return false;
        }

        new_first = malloc(first_remaining * sizeof(*new_first));
        if (new_first == NULL) {
            free(remove_first);
            free(remove_second);
            return false;
        }
    }

    if (second_remaining > 0) {
        if (second_remaining > SIZE_MAX / sizeof(*new_second)) {
            free(new_first);
            free(remove_first);
            free(remove_second);
            return false;
        }

        new_second = malloc(second_remaining * sizeof(*new_second));
        if (new_second == NULL) {
            free(new_first);
            free(remove_first);
            free(remove_second);
            return false;
        }
    }

    for (size_t i = 0; i < first->size; ++i) {
        if (remove_first[i] == 0) {
            new_first[first_index++] = first->items[i];
        }
    }

    for (size_t i = 0; i < second->size; ++i) {
        if (remove_second[i] == 0) {
            new_second[second_index++] = second->items[i];
        }
    }

    free(remove_first);
    free(remove_second);
    free(first->items);
    free(second->items);

    first->items = new_first;
    first->size = first_remaining;
    second->items = new_second;
    second->size = second_remaining;

    return true;
}

static bool print_tuple(const Tuple *tuple)
{
    if (tuple == NULL || (tuple->size > 0 && tuple->items == NULL)) {
        return false;
    }

    if (putchar('(') == EOF) {
        return false;
    }

    for (size_t i = 0; i < tuple->size; ++i) {
        if (i > 0 && fputs(", ", stdout) == EOF) {
            return false;
        }

        if (printf("%d", tuple->items[i]) < 0) {
            return false;
        }
    }

    return putchar(')') != EOF && putchar('\n') != EOF;
}

int main(void)
{
    const int first_values[] = {1, 2, 2, 3, 5};
    const int second_values[] = {2, 4, 2, 5};
    Tuple first = {NULL, 0};
    Tuple second = {NULL, 0};
    int status = EXIT_FAILURE;

    if (!tuple_init(&first, first_values,
                    sizeof(first_values) / sizeof(first_values[0]))) {
        goto cleanup;
    }

    if (!tuple_init(&second, second_values,
                    sizeof(second_values) / sizeof(second_values[0]))) {
        goto cleanup;
    }

    if (!remove_matching_tuples(&first, &second)) {
        goto cleanup;
    }

    if (!print_tuple(&first) || !print_tuple(&second)) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    tuple_destroy(&first);
    tuple_destroy(&second);
    return status;
}