#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

typedef struct {
    int *elements;
    size_t count;
} Tuple;

static int find_max_in_tuples(const Tuple *tuples, size_t tuple_count, int *result)
{
    if (tuples == NULL || result == NULL || tuple_count == 0) {
        return -1;
    }

    int max_val = INT_MIN;
    int found = 0;

    for (size_t i = 0; i < tuple_count; ++i) {
        if (tuples[i].elements == NULL || tuples[i].count == 0) {
            continue;
        }
        for (size_t j = 0; j < tuples[i].count; ++j) {
            if (!found || tuples[i].elements[j] > max_val) {
                max_val = tuples[i].elements[j];
                found = 1;
            }
        }
    }

    if (!found) {
        return -1;
    }

    *result = max_val;
    return 0;
}

static void free_tuples(Tuple *tuples, size_t tuple_count)
{
    if (tuples == NULL) {
        return;
    }
    for (size_t i = 0; i < tuple_count; ++i) {
        free(tuples[i].elements);
        tuples[i].elements = NULL;
        tuples[i].count = 0;
    }
    free(tuples);
}

static int init_tuples(Tuple **out_tuples, size_t tuple_count)
{
    if (out_tuples == NULL || tuple_count == 0) {
        return -1;
    }

    Tuple *tuples = calloc(tuple_count, sizeof(*tuples));
    if (tuples == NULL) {
        return -1;
    }

    for (size_t i = 0; i < tuple_count; ++i) {
        size_t count = i + 2;
        tuples[i].elements = malloc(count * sizeof(*tuples[i].elements));
        if (tuples[i].elements == NULL) {
            free_tuples(tuples, tuple_count);
            return -1;
        }
        tuples[i].count = count;
        for (size_t j = 0; j < count; ++j) {
            tuples[i].elements[j] = (int)(i * 10 + j);
        }
    }

    *out_tuples = tuples;
    return 0;
}

int main(void)
{
    Tuple *tuples = NULL;
    size_t tuple_count = 3;

    if (init_tuples(&tuples, tuple_count) != 0) {
        fprintf(stderr, "Failed to initialize tuples\n");
        return EXIT_FAILURE;
    }

    int max_val = 0;
    if (find_max_in_tuples(tuples, tuple_count, &max_val) != 0) {
        fprintf(stderr, "Failed to find maximum element\n");
        free_tuples(tuples, tuple_count);
        return EXIT_FAILURE;
    }

    printf("Maximum element: %d\n", max_val);

    free_tuples(tuples, tuple_count);
    return EXIT_SUCCESS;
}