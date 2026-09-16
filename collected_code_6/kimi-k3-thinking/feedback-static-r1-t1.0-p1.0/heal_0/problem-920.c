#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TUPLE_SIZE 3

typedef struct {
    int values[TUPLE_SIZE];
    bool is_none[TUPLE_SIZE];
} Tuple;

static bool tuple_is_all_none(const Tuple *t)
{
    size_t i;

    if (t == NULL) {
        return false;
    }
    for (i = 0; i < TUPLE_SIZE; i++) {
        if (!t->is_none[i]) {
            return false;
        }
    }
    return true;
}

size_t remove_all_none_tuples(Tuple *tuples, size_t count)
{
    size_t read_idx;
    size_t write_idx;

    if (tuples == NULL) {
        return 0;
    }
    write_idx = 0;
    for (read_idx = 0; read_idx < count; read_idx++) {
        if (!tuple_is_all_none(&tuples[read_idx])) {
            if (write_idx != read_idx) {
                tuples[write_idx] = tuples[read_idx];
            }
            write_idx++;
        }
    }
    return write_idx;
}

static Tuple make_tuple(const int *values, const bool *is_none, size_t n)
{
    Tuple t;
    size_t i;

    for (i = 0; i < TUPLE_SIZE; i++) {
        t.values[i] = 0;
        t.is_none[i] = true;
    }
    if (values == NULL || is_none == NULL) {
        return t;
    }
    for (i = 0; i < n && i < TUPLE_SIZE; i++) {
        t.values[i] = values[i];
        t.is_none[i] = is_none[i];
    }
    return t;
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
            if (tuples[i].is_none[j]) {
                printf("None");
            } else {
                printf("%d", tuples[i].values[j]);
            }
            if (j + 1 < TUPLE_SIZE) {
                printf(", ");
            }
        }
        printf(")\n");
    }
}

int main(void)
{
    Tuple tuples[5];
    size_t count = 5;
    size_t new_count;

    tuples[0] = make_tuple((int[]){1, 2, 3}, (bool[]){false, false, false}, TUPLE_SIZE);
    tuples[1] = make_tuple((int[]){0, 0, 0}, (bool[]){true, true, true}, TUPLE_SIZE);
    tuples[2] = make_tuple((int[]){4, 5, 6}, (bool[]){false, true, false}, TUPLE_SIZE);
    tuples[3] = make_tuple((int[]){0, 0, 0}, (bool[]){true, true, true}, TUPLE_SIZE);
    tuples[4] = make_tuple((int[]){7, 8, 9}, (bool[]){false, false, false}, TUPLE_SIZE);

    printf("Before removal:\n");
    print_tuples(tuples, count);

    new_count = remove_all_none_tuples(tuples, count);

    printf("After removal:\n");
    print_tuples(tuples, new_count);

    return 0;
}