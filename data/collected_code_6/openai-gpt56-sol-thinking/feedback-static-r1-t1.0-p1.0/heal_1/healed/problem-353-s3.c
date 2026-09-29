#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    size_t rows;
    size_t columns;
    int **items;
} NestedList;

static void nested_list_destroy(NestedList *list)
{
    if (list == NULL) {
        return;
    }

    if (list->items != NULL) {
        for (size_t row = 0; row < list->rows; ++row) {
            free(list->items[row]);
        }

        free(list->items);
    }

    list->rows = 0;
    list->columns = 0;
    list->items = NULL;
}

static bool nested_list_create(NestedList *list, size_t rows, size_t columns)
{
    if (list == NULL) {
        return false;
    }

    list->rows = 0;
    list->columns = 0;
    list->items = NULL;

    if (rows == 0 || columns == 0) {
        list->rows = rows;
        list->columns = columns;
        return true;
    }

    if (rows > SIZE_MAX / sizeof(*list->items) ||
        columns > SIZE_MAX / sizeof(*list->items[0])) {
        return false;
    }

    list->items = calloc(rows, sizeof(*list->items));
    if (list->items == NULL) {
        return false;
    }

    for (size_t row = 0; row < rows; ++row) {
        list->items[row] = malloc(columns * sizeof(*list->items[row]));

        if (list->items[row] == NULL) {
            list->rows = row;
            nested_list_destroy(list);
            return false;
        }
    }

    list->rows = rows;
    list->columns = columns;
    return true;
}

static bool remove_column(NestedList *list, size_t column)
{
    NestedList replacement = {0, 0, NULL};

    if (list == NULL || column >= list->columns) {
        return false;
    }

    if (list->rows > 0 && list->columns > 0) {
        if (list->items == NULL) {
            return false;
        }

        for (size_t row = 0; row < list->rows; ++row) {
            if (list->items[row] == NULL) {
                return false;
            }
        }
    }

    if (!nested_list_create(
            &replacement, list->rows, list->columns - 1)) {
        return false;
    }

    for (size_t row = 0; row < list->rows; ++row) {
        size_t destination_column = 0;

        for (size_t source_column = 0;
             source_column < list->columns;
             ++source_column) {
            if (source_column != column) {
                replacement.items[row][destination_column] =
                    list->items[row][source_column];
                ++destination_column;
            }
        }
    }

    nested_list_destroy(list);
    *list = replacement;

    return true;
}

static void print_nested_list(const NestedList *list)
{
    if (list == NULL) {
        return;
    }

    for (size_t row = 0; row < list->rows; ++row) {
        putchar('[');

        for (size_t column = 0; column < list->columns; ++column) {
            printf("%d", list->items[row][column]);

            if (column + 1 < list->columns) {
                fputs(", ", stdout);
            }
        }

        puts("]");
    }
}

int main(void)
{
    const int values[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };
    const size_t column_to_remove = 1;
    NestedList list = {0, 0, NULL};

    if (!nested_list_create(&list, 3, 4)) {
        fputs("Failed to create nested list.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t row = 0; row < list.rows; ++row) {
        for (size_t column = 0; column < list.columns; ++column) {
            list.items[row][column] = values[row][column];
        }
    }

    if (!remove_column(&list, column_to_remove)) {
        fputs("Failed to remove column.\n", stderr);
        nested_list_destroy(&list);
        return EXIT_FAILURE;
    }

    print_nested_list(&list);
    nested_list_destroy(&list);

    return EXIT_SUCCESS;
}