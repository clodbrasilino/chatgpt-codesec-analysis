#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct {
    int *elements;
    size_t length;
} Tuple;

static int compare_tuples(const void *left, const void *right)
{
    const Tuple *a = left;
    const Tuple *b = right;
    int last_a = a->elements[a->length - 1];
    int last_b = b->elements[b->length - 1];

    return (last_a > last_b) - (last_a < last_b);
}

static int sort_tuples(Tuple *tuples, size_t count)
{
    if (tuples == NULL && count != 0) {
        return -1;
    }

    for (size_t i = 0; i < count; ++i) {
        if (tuples[i].elements == NULL || tuples[i].length == 0) {
            return -1;
        }
    }

    qsort(tuples, count, sizeof(*tuples), compare_tuples);
    return 0;
}

static void free_tuples(Tuple *tuples, size_t count)
{
    if (tuples == NULL) {
        return;
    }

    for (size_t i = 0; i < count; ++i) {
        free(tuples[i].elements);
    }

    free(tuples);
}

int main(void)
{
    static const int values[][3] = {
        {1, 2, 9},
        {4, 5, 3},
        {7, 8, 6}
    };
    const size_t count = sizeof(values) / sizeof(values[0]);
    const size_t tuple_length = sizeof(values[0]) / sizeof(values[0][0]);
    Tuple *tuples = calloc(count, sizeof(*tuples));

    if (tuples == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        tuples[i].elements = malloc(tuple_length * sizeof(*tuples[i].elements));
        if (tuples[i].elements == NULL) {
            fputs("Memory allocation failed\n", stderr);
            free_tuples(tuples, count);
            return EXIT_FAILURE;
        }

        tuples[i].length = tuple_length;

        for (size_t j = 0; j < tuple_length; ++j) {
            tuples[i].elements[j] = values[i][j];
        }
    }

    if (sort_tuples(tuples, count) != 0) {
        fputs("Invalid tuple list\n", stderr);
        free_tuples(tuples, count);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        putchar('(');

        for (size_t j = 0; j < tuples[i].length; ++j) {
            if (printf("%d%s", tuples[i].elements[j],
                       j + 1 == tuples[i].length ? "" : ", ") < 0) {
                free_tuples(tuples, count);
                return EXIT_FAILURE;
            }
        }

        if (puts(")") == EOF) {
            free_tuples(tuples, count);
            return EXIT_FAILURE;
        }
    }

    free_tuples(tuples, count);
    return EXIT_SUCCESS;
}