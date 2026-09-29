#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    size_t size;
} Tuple;

static int tuple_is_empty(const Tuple *t)
{
    return t == NULL || t->size == 0;
}

static void clear_tuple(Tuple *t)
{
    if (t != NULL) {
        free(t->elements);
        t->elements = NULL;
        t->size = 0;
    }
}

static int init_tuple(Tuple *t, const int *values, size_t n)
{
    size_t i;

    if (t == NULL) {
        return -1;
    }

    t->elements = NULL;
    t->size = 0;

    if (n == 0 || values == NULL) {
        return 0;
    }

    t->elements = malloc(n * sizeof *t->elements);
    if (t->elements == NULL) {
        return -1;
    }

    for (i = 0; i < n; i++) {
        t->elements[i] = values[i];
    }
    t->size = n;

    return 0;
}

size_t remove_empty_tuples(Tuple *tuples, size_t count)
{
    size_t read_idx = 0;
    size_t write_idx = 0;

    if (tuples == NULL) {
        return 0;
    }

    for (read_idx = 0; read_idx < count; read_idx++) {
        if (tuple_is_empty(&tuples[read_idx])) {
            clear_tuple(&tuples[read_idx]);
        } else {
            if (write_idx != read_idx) {
                tuples[write_idx] = tuples[read_idx];
                tuples[read_idx].elements = NULL;
                tuples[read_idx].size = 0;
            }
            write_idx++;
        }
    }

    return write_idx;
}

int main(void)
{
    Tuple *tuples = NULL;
    const size_t count = 5;
    size_t new_count = 0;
    size_t i;
    size_t j;
    int a[] = {1, 2, 3};
    int b[] = {4, 5};
    int c[] = {6};

    tuples = calloc(count, sizeof *tuples);
    if (tuples == NULL) {
        fprintf(stderr, "Failed to allocate tuple list\n");
        return EXIT_FAILURE;
    }

    if (init_tuple(&tuples[0], a, 3) != 0 ||
        init_tuple(&tuples[2], b, 2) != 0 ||
        init_tuple(&tuples[4], c, 1) != 0) {
        fprintf(stderr, "Failed to initialize tuples\n");
        for (i = 0; i < count; i++) {
            clear_tuple(&tuples[i]);
        }
        free(tuples);
        return EXIT_FAILURE;
    }

    new_count = remove_empty_tuples(tuples, count);

    printf("Removed %zu empty tuple(s)\n", count - new_count);
    for (i = 0; i < new_count; i++) {
        printf("(");
        for (j = 0; j < tuples[i].size; j++) {
            printf("%d", tuples[i].elements[j]);
            if (j + 1 < tuples[i].size) {
                printf(", ");
            }
        }
        printf(")\n");
    }

    for (i = 0; i < new_count; i++) {
        clear_tuple(&tuples[i]);
    }
    free(tuples);
    tuples = NULL;

    return EXIT_SUCCESS;
}