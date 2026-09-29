#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    size_t count;
    int **rows;
    size_t *lengths;
} NestedList;

static bool nested_list_init(NestedList *list, size_t count)
{
    if (list == NULL) {
        return false;
    }

    list->count = 0;
    list->rows = NULL;
    list->lengths = NULL;

    if (count == 0) {
        return true;
    }

    if (count > SIZE_MAX / sizeof(*list->rows) ||
        count > SIZE_MAX / sizeof(*list->lengths)) {
        return false;
    }

    list->rows = calloc(count, sizeof(*list->rows));
    list->lengths = calloc(count, sizeof(*list->lengths));

    if (list->rows == NULL || list->lengths == NULL) {
        free(list->rows);
        free(list->lengths);
        list->rows = NULL;
        list->lengths = NULL;
        return false;
    }

    list->count = count;
    return true;
}

static void nested_list_destroy(NestedList *list)
{
    if (list == NULL) {
        return;
    }

    if (list->rows != NULL) {
        for (size_t i = 0; i < list->count; ++i) {
            free(list->rows[i]);
        }
    }

    free(list->rows);
    free(list->lengths);

    list->count = 0;
    list->rows = NULL;
    list->lengths = NULL;
}

static bool nested_list_is_valid(const NestedList *list)
{
    if (list == NULL) {
        return false;
    }

    if (list->count != 0 &&
        (list->rows == NULL || list->lengths == NULL)) {
        return false;
    }

    for (size_t i = 0; i < list->count; ++i) {
        if (list->lengths[i] > SIZE_MAX / sizeof(*list->rows[i])) {
            return false;
        }

        if (list->lengths[i] != 0 && list->rows[i] == NULL) {
            return false;
        }
    }

    return true;
}

static bool nested_list_remove_column(NestedList *list, size_t column)
{
    bool removed = false;

    if (!nested_list_is_valid(list)) {
        return false;
    }

    for (size_t i = 0; i < list->count; ++i) {
        if (column < list->lengths[i]) {
            size_t remaining = list->lengths[i] - column - 1;

            if (remaining != 0) {
                memmove(&list->rows[i][column],
                        &list->rows[i][column + 1],
                        remaining * sizeof(*list->rows[i]));
            }

            --list->lengths[i];
            removed = true;
        }
    }

    return removed;
}

static bool nested_list_print(const NestedList *list)
{
    if (!nested_list_is_valid(list)) {
        return false;
    }

    if (putchar('[') == EOF) {
        return false;
    }

    for (size_t i = 0; i < list->count; ++i) {
        if (i != 0 && fputs(", ", stdout) == EOF) {
            return false;
        }

        if (putchar('[') == EOF) {
            return false;
        }

        for (size_t j = 0; j < list->lengths[i]; ++j) {
            if (j != 0 && fputs(", ", stdout) == EOF) {
                return false;
            }

            if (printf("%d", list->rows[i][j]) < 0) {
                return false;
            }
        }

        if (putchar(']') == EOF) {
            return false;
        }
    }

    return fputs("]\n", stdout) != EOF;
}

int main(void)
{
    NestedList list;
    size_t row_count;

    if (scanf("%zu", &row_count) != 1) {
        return EXIT_FAILURE;
    }

    if (!nested_list_init(&list, row_count)) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < row_count; ++i) {
        size_t length;

        if (scanf("%zu", &length) != 1 ||
            length > SIZE_MAX / sizeof(*list.rows[i])) {
            nested_list_destroy(&list);
            return EXIT_FAILURE;
        }

        if (length != 0) {
            list.rows[i] = malloc(length * sizeof(*list.rows[i]));

            if (list.rows[i] == NULL) {
                nested_list_destroy(&list);
                return EXIT_FAILURE;
            }
        }

        list.lengths[i] = length;

        for (size_t j = 0; j < length; ++j) {
            if (scanf("%d", &list.rows[i][j]) != 1) {
                nested_list_destroy(&list);
                return EXIT_FAILURE;
            }
        }
    }

    size_t column;

    if (scanf("%zu", &column) != 1 ||
        !nested_list_remove_column(&list, column) ||
        !nested_list_print(&list)) {
        nested_list_destroy(&list);
        return EXIT_FAILURE;
    }

    nested_list_destroy(&list);
    return EXIT_SUCCESS;
}