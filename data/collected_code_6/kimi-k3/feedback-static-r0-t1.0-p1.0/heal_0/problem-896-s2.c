#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    size_t size;
} Tuple;

static int compare_tuples(const void *a, const void *b)
{
    const Tuple *tuple_a = (const Tuple *)a;
    const Tuple *tuple_b = (const Tuple *)b;

    if (tuple_a->size == 0 || tuple_b->size == 0) {
        return 0;
    }

    int last_a = tuple_a->elements[tuple_a->size - 1];
    int last_b = tuple_b->elements[tuple_b->size - 1];

    if (last_a < last_b) {
        return -1;
    }
    if (last_a > last_b) {
        return 1;
    }
    return 0;
}

int sort_tuples_by_last_element(Tuple *tuples, size_t count)
{
    if (tuples == NULL) {
        return -1;
    }

    if (count == 0) {
        return 0;
    }

    qsort(tuples, count, sizeof(Tuple), compare_tuples);
    return 0;
}

static void free_tuples(Tuple *tuples, size_t count)
{
    if (tuples == NULL) {
        return;
    }

    for (size_t i = 0; i < count; i++) {
        free(tuples[i].elements);
        tuples[i].elements = NULL;
        tuples[i].size = 0;
    }
    free(tuples);
}

int main(void)
{
    const size_t tuple_count = 5;
    Tuple *tuples = malloc(tuple_count * sizeof(Tuple));
    if (tuples == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    int data0[] = {1, 7};
    int data1[] = {2, 3, 5};
    int data2[] = {4, 1};
    int data3[] = {6, 8, 9, 3};
    int data4[] = {2};

    int *all_data[] = {data0, data1, data2, data3, data4};
    size_t sizes[] = {2, 3, 2, 4, 1};

    for (size_t i = 0; i < tuple_count; i++) {
        tuples[i].elements = malloc(sizes[i] * sizeof(int));
        if (tuples[i].elements == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            for (size_t j = 0; j < i; j++) {
                free(tuples[j].elements);
            }
            free(tuples);
            return EXIT_FAILURE;
        }
        tuples[i].size = sizes[i];
        for (size_t j = 0; j < sizes[i]; j++) {
            tuples[i].elements[j] = all_data[i][j];
        }
    }

    if (sort_tuples_by_last_element(tuples, tuple_count) != 0) {
        fprintf(stderr, "Sorting failed\n");
        free_tuples(tuples, tuple_count);
        return EXIT_FAILURE;
    }

    printf("Sorted tuples by last element:\n");
    for (size_t i = 0; i < tuple_count; i++) {
        printf("(");
        for (size_t j = 0; j < tuples[i].size; j++) {
            printf("%d", tuples[i].elements[j]);
            if (j < tuples[i].size - 1) {
                printf(", ");
            }
        }
        printf(")\n");
    }

    free_tuples(tuples, tuple_count);
    return EXIT_SUCCESS;
}