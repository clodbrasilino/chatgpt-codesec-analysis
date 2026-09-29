#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Pair;

int flatten_tuple_matrix(const Pair *matrix, size_t rows, size_t cols,
                         int **out_first, int **out_second, size_t *out_len)
{
    size_t total;
    size_t i;
    int *first_list;
    int *second_list;

    if (matrix == NULL || out_first == NULL || out_second == NULL ||
        out_len == NULL || rows == 0U || cols == 0U) {
        return -1;
    }

    if (rows > (SIZE_MAX / cols)) {
        return -1;
    }

    total = rows * cols;

    if (total > (SIZE_MAX / sizeof(int))) {
        return -1;
    }

    first_list = (int *)malloc(total * sizeof(int));
    if (first_list == NULL) {
        return -1;
    }

    second_list = (int *)malloc(total * sizeof(int));
    if (second_list == NULL) {
        free(first_list);
        return -1;
    }

    for (i = 0U; i < total; i++) {
        first_list[i] = matrix[i].first;
        second_list[i] = matrix[i].second;
    }

    *out_first = first_list;
    *out_second = second_list;
    *out_len = total;

    return 0;
}

int main(void)
{
    const Pair matrix[2][2] = {
        { {4, 5}, {7, 8} },
        { {10, 13}, {18, 17} }
    };
    int *first_tuple = NULL;
    int *second_tuple = NULL;
    size_t len = 0U;
    size_t i;
    int result;

    result = flatten_tuple_matrix(&matrix[0][0], 2U, 2U,
                                  &first_tuple, &second_tuple, &len);

    if (result != 0) {
        (void)fprintf(stderr, "Failed to flatten tuple matrix\n");
        return EXIT_FAILURE;
    }

    (void)printf("[(");
    for (i = 0U; i < len; i++) {
        if (i > 0U) {
            (void)printf(", ");
        }
        (void)printf("%d", first_tuple[i]);
    }
    (void)printf("), (");
    for (i = 0U; i < len; i++) {
        if (i > 0U) {
            (void)printf(", ");
        }
        (void)printf("%d", second_tuple[i]);
    }
    (void)printf(")]\n");

    free(first_tuple);
    free(second_tuple);

    return EXIT_SUCCESS;
}