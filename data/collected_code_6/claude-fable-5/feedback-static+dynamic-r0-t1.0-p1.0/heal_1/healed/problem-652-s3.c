#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    int *items;
    size_t count;
} Tuple;

Tuple *flatten_tuple_matrix(const int *matrix, size_t rows, size_t cols,
                            size_t tuple_size, size_t *result_count);
void free_tuple_list(Tuple *list, size_t count);
void print_tuple_list(const Tuple *list, size_t count);

Tuple *flatten_tuple_matrix(const int *matrix, size_t rows, size_t cols,
                            size_t tuple_size, size_t *result_count)
{
    Tuple *result = NULL;
    size_t total = 0;
    size_t idx = 0;
    size_t r;
    size_t c;
    size_t t;
    size_t k;

    if ((matrix == NULL) || (result_count == NULL) ||
        (rows == 0U) || (cols == 0U) || (tuple_size == 0U)) {
        return NULL;
    }

    if (rows > (SIZE_MAX / cols)) {
        return NULL;
    }
    total = rows * cols;

    if (total > (SIZE_MAX / tuple_size)) {
        return NULL;
    }
    if (tuple_size > (SIZE_MAX / sizeof(Tuple))) {
        return NULL;
    }
    if (total > (SIZE_MAX / sizeof(int))) {
        return NULL;
    }

    result = (Tuple *)malloc(tuple_size * sizeof(Tuple));
    if (result == NULL) {
        return NULL;
    }

    for (t = 0; t < tuple_size; t++) {
        result[t].items = (int *)malloc(total * sizeof(int));
        result[t].count = total;
        if (result[t].items == NULL) {
            for (k = 0; k < t; k++) {
                free(result[k].items);
                result[k].items = NULL;
            }
            free(result);
            return NULL;
        }
    }

    idx = 0;
    for (r = 0; r < rows; r++) {
        for (c = 0; c < cols; c++) {
            const int *tup = &matrix[((r * cols) + c) * tuple_size];
            for (t = 0; t < tuple_size; t++) {
                result[t].items[idx] = tup[t];
            }
            idx++;
        }
    }

    *result_count = tuple_size;
    return result;
}

void free_tuple_list(Tuple *list, size_t count)
{
    size_t i;

    if (list == NULL) {
        return;
    }

    for (i = 0; i < count; i++) {
        free(list[i].items);
        list[i].items = NULL;
        list[i].count = 0;
    }
    free(list);
}

void print_tuple_list(const Tuple *list, size_t count)
{
    size_t i;
    size_t j;

    if (list == NULL) {
        return;
    }

    (void)printf("[");
    for (i = 0; i < count; i++) {
        (void)printf("(");
        for (j = 0; j < list[i].count; j++) {
            (void)printf("%d", list[i].items[j]);
            if (j < (list[i].count - 1U)) {
                (void)printf(", ");
            }
        }
        (void)printf(")");
        if (i < (count - 1U)) {
            (void)printf(", ");
        }
    }
    (void)printf("]\n");
}

int main(void)
{
    const size_t rows = 2;
    const size_t cols = 2;
    const size_t tuple_size = 2;
    size_t result_count = 0;
    Tuple *result = NULL;

    static const int matrix[2][2][2] = {
        { {4, 5}, {3, 2} },
        { {2, 2}, {4, 6} }
    };

    result = flatten_tuple_matrix(&matrix[0][0][0], rows, cols,
                                  tuple_size, &result_count);
    if (result == NULL) {
        (void)fprintf(stderr, "Failed to flatten the tuple matrix\n");
        return EXIT_FAILURE;
    }

    (void)printf("Flattened tuple list (column-wise):\n");
    print_tuple_list(result, result_count);

    free_tuple_list(result, result_count);
    result = NULL;

    return EXIT_SUCCESS;
}