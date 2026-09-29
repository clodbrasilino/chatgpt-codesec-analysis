#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    size_t length;
} Tuple;

static int compare_tuples(const void *a, const void *b)
{
    const Tuple *ta = (const Tuple *)a;
    const Tuple *tb = (const Tuple *)b;
    int last_a = ta->elements[ta->length - 1];
    int last_b = tb->elements[tb->length - 1];

    if (last_a < last_b) {
        return -1;
    }
    if (last_a > last_b) {
        return 1;
    }
    return 0;
}

static int sort_tuples_by_last(Tuple *tuples, size_t count)
{
    size_t i;

    if (tuples == NULL || count == 0U) {
        return -1;
    }

    for (i = 0U; i < count; i++) {
        if (tuples[i].elements == NULL || tuples[i].length == 0U) {
            return -1;
        }
    }

    qsort(tuples, count, sizeof(Tuple), compare_tuples);
    return 0;
}

static Tuple make_tuple(const int *values, size_t length)
{
    Tuple t;
    size_t i;

    t.elements = NULL;
    t.length = 0U;

    if (values == NULL || length == 0U) {
        return t;
    }

    t.elements = (int *)malloc(length * sizeof(int));
    if (t.elements == NULL) {
        return t;
    }

    for (i = 0U; i < length; i++) {
        t.elements[i] = values[i];
    }
    t.length = length;
    return t;
}

static void free_tuples(Tuple *tuples, size_t count)
{
    size_t i;

    if (tuples == NULL) {
        return;
    }

    for (i = 0U; i < count; i++) {
        free(tuples[i].elements);
        tuples[i].elements = NULL;
        tuples[i].length = 0U;
    }
}

static void print_tuples(const Tuple *tuples, size_t count)
{
    size_t i;
    size_t j;

    for (i = 0U; i < count; i++) {
        printf("(");
        for (j = 0U; j < tuples[i].length; j++) {
            printf("%d", tuples[i].elements[j]);
            if (j + 1U < tuples[i].length) {
                printf(", ");
            }
        }
        printf(")\n");
    }
}

int main(void)
{
    int data0[] = { 2, 5 };
    int data1[] = { 1, 2, 3 };
    int data2[] = { 4, 4, 10, 1 };
    int data3[] = { 7 };
    Tuple tuples[4];
    size_t count = 4U;
    size_t i;

    tuples[0] = make_tuple(data0, sizeof(data0) / sizeof(data0[0]));
    tuples[1] = make_tuple(data1, sizeof(data1) / sizeof(data1[0]));
    tuples[2] = make_tuple(data2, sizeof(data2) / sizeof(data2[0]));
    tuples[3] = make_tuple(data3, sizeof(data3) / sizeof(data3[0]));

    for (i = 0U; i < count; i++) {
        if (tuples[i].elements == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            free_tuples(tuples, count);
            return EXIT_FAILURE;
        }
    }

    if (sort_tuples_by_last(tuples, count) != 0) {
        fprintf(stderr, "Sorting failed due to invalid input\n");
        free_tuples(tuples, count);
        return EXIT_FAILURE;
    }

    print_tuples(tuples, count);
    free_tuples(tuples, count);
    return EXIT_SUCCESS;
}