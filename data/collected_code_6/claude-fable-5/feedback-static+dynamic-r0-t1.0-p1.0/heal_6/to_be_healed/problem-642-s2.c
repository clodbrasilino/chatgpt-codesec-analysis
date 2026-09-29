#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    int first;
    int second;
} Tuple;

typedef struct {
    Tuple *tuples;
    size_t count;
} Row;

static int compare_tuples(const void *a, const void *b)
{
    const Tuple *x = (const Tuple *)a;
    const Tuple *y = (const Tuple *)b;

    if (x->first < y->first) {
        return -1;
    }
    if (x->first > y->first) {
        return 1;
    }
    if (x->second < y->second) {
        return -1;
    }
    if (x->second > y->second) {
        return 1;
    }
    return 0;
}

static int safe_tuple_size(size_t count, size_t *out_bytes)
{
    if (out_bytes == NULL) {
        return -1;
    }
    if (count == 0) {
        return -1;
    }
    if (count > SIZE_MAX / sizeof(Tuple)) {
        return -1;
    }
    *out_bytes = count * sizeof(Tuple);
    return 0;
}

static int safe_copy_tuples(Tuple *dst, size_t dst_bytes,
                            const Tuple *src, size_t src_bytes)
{
    if (dst == NULL || src == NULL) {
        return -1;
    }
    if (src_bytes == 0) {
        return -1;
    }
    if (src_bytes > dst_bytes) {
        return -1;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(dst, src, src_bytes);
    return 0;
}

static int rows_similar(const Row *r1, const Row *r2, int *result)
{
    Tuple *c1 = NULL;
    Tuple *c2 = NULL;
    size_t bytes = 0;

    if (r1 == NULL || r2 == NULL || result == NULL) {
        return -1;
    }

    if (r1->count != r2->count) {
        *result = 0;
        return 0;
    }

    if (r1->count == 0) {
        *result = 1;
        return 0;
    }

    if (r1->tuples == NULL || r2->tuples == NULL) {
        return -1;
    }

    if (safe_tuple_size(r1->count, &bytes) != 0) {
        return -1;
    }

    c1 = malloc(bytes);
    if (c1 == NULL) {
        return -1;
    }
    c2 = malloc(bytes);
    if (c2 == NULL) {
        free(c1);
        return -1;
    }

    if (safe_copy_tuples(c1, bytes, r1->tuples, bytes) != 0) {
        free(c1);
        free(c2);
        return -1;
    }
    if (safe_copy_tuples(c2, bytes, r2->tuples, bytes) != 0) {
        free(c1);
        free(c2);
        return -1;
    }

    qsort(c1, r1->count, sizeof(Tuple), compare_tuples);
    qsort(c2, r2->count, sizeof(Tuple), compare_tuples);

    *result = (memcmp(c1, c2, bytes) == 0) ? 1 : 0;

    free(c1);
    free(c2);
    return 0;
}

static int remove_similar_rows(Row *rows, size_t *row_count)
{
    size_t write_index = 0;
    size_t i;
    size_t j;

    if (rows == NULL || row_count == NULL) {
        return -1;
    }

    for (i = 0; i < *row_count; i++) {
        int duplicate = 0;

        for (j = 0; j < write_index; j++) {
            int similar = 0;
            if (rows_similar(&rows[i], &rows[j], &similar) != 0) {
                return -1;
            }
            if (similar == 1) {
                duplicate = 1;
                break;
            }
        }

        if (duplicate == 1) {
            free(rows[i].tuples);
            rows[i].tuples = NULL;
            rows[i].count = 0;
        } else {
            if (write_index != i) {
                rows[write_index] = rows[i];
                rows[i].tuples = NULL;
                rows[i].count = 0;
            }
            write_index++;
        }
    }

    for (i = write_index; i < *row_count; i++) {
        rows[i].tuples = NULL;
        rows[i].count = 0;
    }

    *row_count = write_index;
    return 0;
}

static Row make_row(const Tuple *src, size_t count, int *error)
{
    Row row;
    size_t bytes = 0;

    row.tuples = NULL;
    row.count = 0;

    if (error == NULL) {
        return row;
    }

    if (src == NULL || count == 0) {
        *error = 1;
        return row;
    }

    if (safe_tuple_size(count, &bytes) != 0) {
        *error = 1;
        return row;
    }

    row.tuples = malloc(bytes);
    if (row.tuples == NULL) {
        *error = 1;
        return row;
    }

    if (safe_copy_tuples(row.tuples, bytes, src, bytes) != 0) {
        free(row.tuples);
        row.tuples = NULL;
        *error = 1;
        return row;
    }

    row.count = count;
    *error = 0;
    return row;
}

static void print_matrix(const Row *rows, size_t row_count)
{
    size_t i;
    size_t j;

    if (rows == NULL) {
        return;
    }

    for (i = 0; i < row_count; i++) {
        printf("[ ");
        if (rows[i].tuples != NULL) {
            for (j = 0; j < rows[i].count; j++) {
                printf("(%d, %d) ", rows[i].tuples[j].first,
                       rows[i].tuples[j].second);
            }
        }
        printf("]\n");
    }
}

static void free_matrix(Row *rows, size_t row_count)
{
    size_t i;

    if (rows == NULL) {
        return;
    }

    for (i = 0; i < row_count; i++) {
        free(rows[i].tuples);
        rows[i].tuples = NULL;
        rows[i].count = 0;
    }
}

int main(void)
{
    Tuple r0[] = { {4, 5}, {3, 2} };
    Tuple r1[] = { {2, 2}, {4, 6} };
    Tuple r2[] = { {3, 2}, {4, 5} };
    Tuple r3[] = { {2, 2}, {4, 6} };
    Row matrix[4];
    size_t row_count = 4;
    int error = 0;

    matrix[0] = make_row(r0, sizeof(r0) / sizeof(r0[0]), &error);
    if (error != 0) {
        fprintf(stderr, "Allocation failure\n");
        free_matrix(matrix, 0);
        return EXIT_FAILURE;
    }
    matrix[1] = make_row(r1, sizeof(r1) / sizeof(r1[0]), &error);
    if (error != 0) {
        fprintf(stderr, "Allocation failure\n");
        free_matrix(matrix, 1);
        return EXIT_FAILURE;
    }
    matrix[2] = make_row(r2, sizeof(r2) / sizeof(r2[0]), &error);
    if (error != 0) {
        fprintf(stderr, "Allocation failure\n");
        free_matrix(matrix, 2);
        return EXIT_FAILURE;
    }
    matrix[3] = make_row(r3, sizeof(r3) / sizeof(r3[0]), &error);
    if (error != 0) {
        fprintf(stderr, "Allocation failure\n");
        free_matrix(matrix, 3);
        return EXIT_FAILURE;
    }

    printf("Original matrix:\n");
    print_matrix(matrix, row_count);

    if (remove_similar_rows(matrix, &row_count) != 0) {
        fprintf(stderr, "Failed to remove similar rows\n");
        free_matrix(matrix, 4);
        return EXIT_FAILURE;
    }

    printf("Matrix after removing similar rows:\n");
    print_matrix(matrix, row_count);

    free_matrix(matrix, row_count);

    return EXIT_SUCCESS;
}