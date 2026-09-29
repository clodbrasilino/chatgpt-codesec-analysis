#include <stdio.h>
#include <stdlib.h>

#define TUPLE_SIZE 3
#define LIST_SIZE 5

typedef struct {
    int values[TUPLE_SIZE];
} Tuple;

static int compare_tuples(const void *a, const void *b)
{
    const Tuple *ta = (const Tuple *)a;
    const Tuple *tb = (const Tuple *)b;
    int last_a = ta->values[TUPLE_SIZE - 1];
    int last_b = tb->values[TUPLE_SIZE - 1];

    if (last_a < last_b) {
        return -1;
    }
    if (last_a > last_b) {
        return 1;
    }
    return 0;
}

static int sort_tuples(Tuple *tuples, size_t count)
{
    if (tuples == NULL || count == 0U) {
        return -1;
    }
    qsort(tuples, count, sizeof(Tuple), compare_tuples);
    return 0;
}

static void print_tuples(const Tuple *tuples, size_t count)
{
    size_t i;
    size_t j;

    if (tuples == NULL) {
        return;
    }

    for (i = 0U; i < count; i++) {
        (void)printf("(");
        for (j = 0U; j < TUPLE_SIZE; j++) {
            (void)printf("%d", tuples[i].values[j]);
            if (j < (TUPLE_SIZE - 1U)) {
                (void)printf(", ");
            }
        }
        (void)printf(")\n");
    }
}

int main(void)
{
    Tuple *tuples;
    size_t i;
    const int initial_data[LIST_SIZE][TUPLE_SIZE] = {
        {1, 2, 9},
        {4, 5, 1},
        {7, 8, 5},
        {3, 6, 2},
        {0, 1, 7}
    };

    tuples = (Tuple *)malloc(LIST_SIZE * sizeof(Tuple));
    if (tuples == NULL) {
        (void)fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (i = 0U; i < LIST_SIZE; i++) {
        size_t j;
        for (j = 0U; j < TUPLE_SIZE; j++) {
            tuples[i].values[j] = initial_data[i][j];
        }
    }

    (void)printf("Before sorting:\n");
    print_tuples(tuples, LIST_SIZE);

    if (sort_tuples(tuples, LIST_SIZE) != 0) {
        (void)fprintf(stderr, "Sorting failed\n");
        free(tuples);
        return EXIT_FAILURE;
    }

    (void)printf("After sorting:\n");
    print_tuples(tuples, LIST_SIZE);

    free(tuples);
    tuples = NULL;

    return EXIT_SUCCESS;
}