#include <stdio.h>
#include <stdlib.h>

#define TUPLE_SIZE 3

typedef struct {
    int values[TUPLE_SIZE];
} Tuple;

static int compare_tuples(const void *a, const void *b)
{
    const Tuple *ta = (const Tuple *)a;
    const Tuple *tb = (const Tuple *)b;

    if (ta->values[TUPLE_SIZE - 1] < tb->values[TUPLE_SIZE - 1]) {
        return -1;
    }
    if (ta->values[TUPLE_SIZE - 1] > tb->values[TUPLE_SIZE - 1]) {
        return 1;
    }
    return 0;
}

static int sort_tuples(Tuple *tuples, size_t count)
{
    if (tuples == NULL || count == 0) {
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

    for (i = 0; i < count; i++) {
        printf("(");
        for (j = 0; j < TUPLE_SIZE; j++) {
            printf("%d", tuples[i].values[j]);
            if (j < TUPLE_SIZE - 1) {
                printf(", ");
            }
        }
        printf(")\n");
    }
}

int main(void)
{
    size_t count = 4;
    Tuple *tuples = malloc(count * sizeof(Tuple));

    if (tuples == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    tuples[0] = (Tuple){ { 1, 3, 9 } };
    tuples[1] = (Tuple){ { 2, 4, 5 } };
    tuples[2] = (Tuple){ { 7, 8, 1 } };
    tuples[3] = (Tuple){ { 0, 6, 3 } };

    printf("Before sorting:\n");
    print_tuples(tuples, count);

    if (sort_tuples(tuples, count) != 0) {
        fprintf(stderr, "Sorting failed\n");
        free(tuples);
        return EXIT_FAILURE;
    }

    printf("After sorting:\n");
    print_tuples(tuples, count);

    free(tuples);
    tuples = NULL;

    return EXIT_SUCCESS;
}