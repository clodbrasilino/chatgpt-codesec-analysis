#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

static int rows_similar(const Row *r1, const Row *r2, int *result)
{
    Tuple *c1 = NULL;
    Tuple *c2 = NULL;

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

    c1 = malloc(r1->count * sizeof(Tuple));
    if (c1 == NULL) {
        return -1;
    }
    c2 = malloc(r2->count * sizeof(Tuple));
    if (c2 == NULL) {
        free(c1);
        return -1;
    }

    memcpy(c1, r1->tuples, r1->count * sizeof(Tuple));
    memcpy(c2, r2->tuples, r2->count * sizeof(Tuple));

    qsort(c1, r1->count, sizeof(Tuple), compare_tuples);
    qsort(c2, r2->count, sizeof(Tuple), compare_tuples);

    *result = (memcmp(c1, c2, r1->count * sizeof(Tuple)) == 0) ? 1 : 0;

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
            rows[write_index] = rows[i];
            write_index++;
        }
    }

    *row_count = write_index;
    return 0;
}

static Row make_row(const Tuple *src, size_t count, int *error)
{
    Row row;

    row.tuples = NULL;
    row.count = 0;

    if (error == NULL) {
        return row;
    }

    if (src == NULL || count == 0) {
        *error = 1;
        return row;
    }

    row.tuples = malloc(count * sizeof(Tuple));
    if (row.tuples == NULL) {
        *error = 1;
        return row;
    }

    memcpy(row.tuples, src, count * sizeof(Tuple));
    row.count = count;
    *error = 0;
    return row;
}

static void print_matrix(const Row *rows, size_t row_count)
{
    size_t i;
    size_t j;

    for (i = 0; i < row_count; i++) {
        printf("[ ");
        for (j = 0; j < rows[i].count; j++) {
            printf("(%d, %d) ", rows[i].tuples[j].first, rows[i].tuples[j].second);
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
    size_t i;
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

    for (i = 0; i < row_count; i++) {
        free(matrix[i].tuples);
        matrix[i].tuples = NULL;
        matrix[i].count = 0;
    }

    return EXIT_SUCCESS;
}