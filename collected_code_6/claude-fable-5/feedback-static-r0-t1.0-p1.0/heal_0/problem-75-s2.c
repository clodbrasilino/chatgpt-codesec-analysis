#include <stdio.h>
#include <stdlib.h>

#define TUPLE_SIZE 3

typedef struct {
    int elements[TUPLE_SIZE];
} Tuple;

static int is_tuple_divisible(const Tuple *t, int k)
{
    int i;

    if (t == NULL || k == 0) {
        return 0;
    }

    for (i = 0; i < TUPLE_SIZE; i++) {
        if (t->elements[i] % k != 0) {
            return 0;
        }
    }

    return 1;
}

static int find_divisible_tuples(const Tuple *tuples, size_t count, int k,
                                 Tuple *result, size_t result_capacity,
                                 size_t *result_count)
{
    size_t i;
    size_t found;

    if (tuples == NULL || result == NULL || result_count == NULL || k == 0) {
        return -1;
    }

    found = 0;

    for (i = 0; i < count; i++) {
        if (is_tuple_divisible(&tuples[i], k)) {
            if (found >= result_capacity) {
                return -1;
            }
            result[found] = tuples[i];
            found++;
        }
    }

    *result_count = found;
    return 0;
}

static void print_tuple(const Tuple *t)
{
    int i;

    if (t == NULL) {
        return;
    }

    printf("(");
    for (i = 0; i < TUPLE_SIZE; i++) {
        printf("%d", t->elements[i]);
        if (i < TUPLE_SIZE - 1) {
            printf(", ");
        }
    }
    printf(")\n");
}

int main(void)
{
    Tuple tuples[] = {
        { {6, 24, 12} },
        { {7, 9, 6} },
        { {12, 18, 21} },
        { {12, 24, 36} },
        { {5, 10, 15} }
    };
    size_t count = sizeof(tuples) / sizeof(tuples[0]);
    Tuple *result;
    size_t result_count = 0;
    size_t i;
    int k = 6;
    int status;

    result = malloc(count * sizeof(Tuple));
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    status = find_divisible_tuples(tuples, count, k, result, count,
                                   &result_count);
    if (status != 0) {
        fprintf(stderr, "Error finding divisible tuples\n");
        free(result);
        return EXIT_FAILURE;
    }

    printf("Tuples with all elements divisible by %d:\n", k);
    for (i = 0; i < result_count; i++) {
        print_tuple(&result[i]);
    }

    free(result);
    return EXIT_SUCCESS;
}