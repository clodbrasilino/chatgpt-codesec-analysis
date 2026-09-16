#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    int first;
    int second;
} Tuple2;

static int flatten_tuple_matrix(const Tuple2 *matrix, size_t rows, size_t cols,
                                int **result, size_t *tuple_count, size_t *tuple_len)
{
    size_t total;
    size_t j;
    size_t k;
    size_t i;
    size_t idx;
    int *buf;

    if (matrix == NULL || result == NULL || tuple_count == NULL ||
        tuple_len == NULL || rows == 0U || cols == 0U) {
        return -1;
    }

    if (cols > SIZE_MAX / 2U) {
        return -1;
    }
    total = cols * 2U;

    if (rows > SIZE_MAX / total) {
        return -1;
    }
    total = total * rows;

    if (total > SIZE_MAX / sizeof(int)) {
        return -1;
    }

    buf = malloc(total * sizeof(int));
    if (buf == NULL) {
        return -1;
    }

    idx = 0U;
    for (j = 0U; j < cols; j++) {
        for (k = 0U; k < 2U; k++) {
            for (i = 0U; i < rows; i++) {
                const Tuple2 *t = &matrix[(i * cols) + j];
                buf[idx] = (k == 0U) ? t->first : t->second;
                idx++;
            }
        }
    }

    *result = buf;
    *tuple_count = cols * 2U;
    *tuple_len = rows;
    return 0;
}

int main(void)
{
    Tuple2 matrix[2][2] = {
        { {4, 5}, {3, 2} },
        { {2, 2}, {6, 5} }
    };
    int *flat = NULL;
    size_t count = 0U;
    size_t len = 0U;
    size_t t;
    size_t e;
    int status;

    status = flatten_tuple_matrix(&matrix[0][0], 2U, 2U, &flat, &count, &len);
    if (status != 0) {
        (void)fprintf(stderr, "Failed to flatten tuple matrix\n");
        return EXIT_FAILURE;
    }

    (void)printf("[");
    for (t = 0U; t < count; t++) {
        (void)printf("(");
        for (e = 0U; e < len; e++) {
            (void)printf("%d", flat[(t * len) + e]);
            if (e + 1U < len) {
                (void)printf(", ");
            }
        }
        (void)printf(")");
        if (t + 1U < count) {
            (void)printf(", ");
        }
    }
    (void)printf("]\n");

    free(flat);
    flat = NULL;

    return EXIT_SUCCESS;
}