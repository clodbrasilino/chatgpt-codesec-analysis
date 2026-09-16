#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct {
    int **rows;
    size_t *row_lengths;
    size_t row_count;
} NestedList;

int *extract_column(const NestedList *list, size_t column, size_t *out_count) {
    if (!out_count) {
        return NULL;
    }
    *out_count = 0;
    if (!list) {
        return NULL;
    }
    size_t count = list->row_count;
    if (count > 0 && (!list->rows || !list->row_lengths)) {
        return NULL;
    }
    int *result = malloc((count == 0 ? 1 : count) * sizeof(*result));
    if (!result) {
        return NULL;
    }
    for (size_t i = 0; i < count; ++i) {
        if (!list->rows[i] || column >= list->row_lengths[i]) {
            free(result);
            return NULL;
        }
        result[i] = list->rows[i][column];
    }
    *out_count = count;
    return result;
}

int main(void) {
    int row0[] = { 10, 20, 30 };
    int row1[] = { 40, 50, 60 };
    int row2[] = { 70, 80, 90 };
    int *rows[] = { row0, row1, row2 };
    size_t lengths[] = { 3, 3, 3 };
    NestedList list = { rows, lengths, 3 };
    size_t count = 0;
    int *column = extract_column(&list, 1, &count);
    if (!column) {
        return 1;
    }
    for (size_t i = 0; i < count; ++i) {
        printf("%d\n", column[i]);
    }
    free(column);
    return 0;
}