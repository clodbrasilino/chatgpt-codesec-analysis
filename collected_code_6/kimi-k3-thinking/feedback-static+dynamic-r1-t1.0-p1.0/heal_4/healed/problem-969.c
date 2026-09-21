#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_TUPLE_SIZE 16

typedef struct {
    int elements[MAX_TUPLE_SIZE];
    size_t size;
} Tuple;

typedef struct {
    Tuple *tuples;
    size_t size;
} TupleList;

static void init_tuple(Tuple *t, const int *values, size_t n)
{
    size_t i;

    if (t == NULL) {
        return;
    }

    t->size = 0;

    if (values == NULL || n == 0 || n > MAX_TUPLE_SIZE) {
        return;
    }

    for (i = 0; i < n; i++) {
        t->elements[i] = values[i];
    }
    t->size = n;
}

TupleList join_tuples(const Tuple *tuples, size_t count)
{
    TupleList result;
    size_t i, j, k;

    result.tuples = NULL;
    result.size = 0;

    if (tuples == NULL || count == 0) {
        return result;
    }

    if (count > SIZE_MAX / sizeof(Tuple)) {
        return result;
    }

    result.tuples = (Tuple *)malloc(count * sizeof(Tuple));
    if (result.tuples == NULL) {
        return result;
    }

    for (i = 0; i < count; i++) {
        int matched = 0;

        if (tuples[i].size == 0 || tuples[i].size > MAX_TUPLE_SIZE) {
            continue;
        }

        for (j = 0; j < result.size; j++) {
            if (result.tuples[j].size > 0 &&
                result.tuples[j].size <= MAX_TUPLE_SIZE &&
                result.tuples[j].elements[0] == tuples[i].elements[0]) {
                for (k = 1; k < tuples[i].size; k++) {
                    if (result.tuples[j].size < MAX_TUPLE_SIZE) {
                        result.tuples[j].elements[result.tuples[j].size] =
                            tuples[i].elements[k];
                        result.tuples[j].size++;
                    }
                }
                matched = 1;
                break;
            }
        }

        if (!matched && result.size < count) {
            result.tuples[result.size] = tuples[i];
            result.size++;
        }
    }

    return result;
}

void free_tuple_list(TupleList *list)
{
    if (list == NULL) {
        return;
    }
    free(list->tuples);
    list->tuples = NULL;
    list->size = 0;
}

static void print_tuple_list(const TupleList *list)
{
    size_t i, j;

    if (list == NULL || list->tuples == NULL) {
        return;
    }

    for (i = 0; i < list->size; i++) {
        if (list->tuples[i].size > MAX_TUPLE_SIZE) {
            continue;
        }
        printf("(");
        for (j = 0; j < list->tuples[i].size; j++) {
            printf("%d", list->tuples[i].elements[j]);
            if (j + 1 < list->tuples[i].size) {
                printf(", ");
            }
        }
        printf(")\n");
    }
}

int main(void)
{
    Tuple input[5];
    TupleList joined;

    const int t0[] = {5, 6};
    const int t1[] = {5, 7};
    const int t2[] = {6, 8};
    const int t3[] = {6, 10};
    const int t4[] = {7, 13};

    init_tuple(&input[0], t0, 2);
    init_tuple(&input[1], t1, 2);
    init_tuple(&input[2], t2, 2);
    init_tuple(&input[3], t3, 2);
    init_tuple(&input[4], t4, 2);

    joined = join_tuples(input, 5);

    printf("Joined tuples:\n");
    print_tuple_list(&joined);

    free_tuple_list(&joined);

    return 0;
}