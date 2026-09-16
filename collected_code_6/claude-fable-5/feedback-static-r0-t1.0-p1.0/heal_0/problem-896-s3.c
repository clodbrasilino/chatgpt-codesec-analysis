#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    size_t size;
} Tuple;

static int compare_tuples(const void *a, const void *b)
{
    const Tuple *ta = (const Tuple *)a;
    const Tuple *tb = (const Tuple *)b;
    int last_a = ta->elements[ta->size - 1];
    int last_b = tb->elements[tb->size - 1];

    if (last_a < last_b) {
        return -1;
    }
    if (last_a > last_b) {
        return 1;
    }
    return 0;
}

int sort_tuples_by_last(Tuple *tuples, size_t count)
{
    size_t i;

    if (tuples == NULL || count == 0) {
        return -1;
    }

    for (i = 0; i < count; i++) {
        if (tuples[i].elements == NULL || tuples[i].size == 0) {
            return -1;
        }
    }

    qsort(tuples, count, sizeof(Tuple), compare_tuples);
    return 0;
}

static Tuple *create_tuple(const int *values, size_t size)
{
    Tuple *t;
    size_t i;

    if (values == NULL || size == 0) {
        return NULL;
    }

    t = malloc(sizeof(Tuple));
    if (t == NULL) {
        return NULL;
    }

    t->elements = malloc(size * sizeof(int));
    if (t->elements == NULL) {
        free(t);
        return NULL;
    }

    for (i = 0; i < size; i++) {
        t->elements[i] = values[i];
    }
    t->size = size;
    return t;
}

static void free_tuple_contents(Tuple *t)
{
    if (t != NULL) {
        free(t->elements);
        t->elements = NULL;
        t->size = 0;
    }
}

static void print_tuples(const Tuple *tuples, size_t count)
{
    size_t i;
    size_t j;

    printf("[");
    for (i = 0; i < count; i++) {
        printf("(");
        for (j = 0; j < tuples[i].size; j++) {
            printf("%d", tuples[i].elements[j]);
            if (j + 1 < tuples[i].size) {
                printf(", ");
            }
        }
        printf(")");
        if (i + 1 < count) {
            printf(", ");
        }
    }
    printf("]\n");
}

int main(void)
{
    int v1[] = {2, 5};
    int v2[] = {1, 2};
    int v3[] = {4, 4};
    int v4[] = {2, 3};
    int v5[] = {2, 1};
    Tuple *t1;
    Tuple *t2;
    Tuple *t3;
    Tuple *t4;
    Tuple *t5;
    Tuple tuples[5];
    size_t count = 5;
    size_t i;

    t1 = create_tuple(v1, sizeof(v1) / sizeof(v1[0]));
    t2 = create_tuple(v2, sizeof(v2) / sizeof(v2[0]));
    t3 = create_tuple(v3, sizeof(v3) / sizeof(v3[0]));
    t4 = create_tuple(v4, sizeof(v4) / sizeof(v4[0]));
    t5 = create_tuple(v5, sizeof(v5) / sizeof(v5[0]));

    if (t1 == NULL || t2 == NULL || t3 == NULL || t4 == NULL || t5 == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        if (t1 != NULL) { free_tuple_contents(t1); free(t1); }
        if (t2 != NULL) { free_tuple_contents(t2); free(t2); }
        if (t3 != NULL) { free_tuple_contents(t3); free(t3); }
        if (t4 != NULL) { free_tuple_contents(t4); free(t4); }
        if (t5 != NULL) { free_tuple_contents(t5); free(t5); }
        return EXIT_FAILURE;
    }

    tuples[0] = *t1;
    tuples[1] = *t2;
    tuples[2] = *t3;
    tuples[3] = *t4;
    tuples[4] = *t5;
    free(t1);
    free(t2);
    free(t3);
    free(t4);
    free(t5);

    printf("Before sorting: ");
    print_tuples(tuples, count);

    if (sort_tuples_by_last(tuples, count) != 0) {
        fprintf(stderr, "Sorting failed due to invalid input\n");
        for (i = 0; i < count; i++) {
            free_tuple_contents(&tuples[i]);
        }
        return EXIT_FAILURE;
    }

    printf("After sorting:  ");
    print_tuples(tuples, count);

    for (i = 0; i < count; i++) {
        free_tuple_contents(&tuples[i]);
    }

    return EXIT_SUCCESS;
}