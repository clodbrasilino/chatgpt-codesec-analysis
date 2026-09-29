#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

static int create_elementwise_tuples(const int *left, size_t left_size,
                                     const int *right, size_t right_size,
                                     Tuple **result, size_t *result_size)
{
    Tuple *tuples;
    size_t count;
    size_t i;

    if (left == NULL || right == NULL || result == NULL || result_size == NULL) {
        return -1;
    }

    *result = NULL;
    *result_size = 0;

    count = left_size < right_size ? left_size : right_size;

    if (count == 0) {
        return 0;
    }

    if (count > SIZE_MAX / sizeof(*tuples)) {
        return -1;
    }

    tuples = malloc(count * sizeof(*tuples));
    if (tuples == NULL) {
        return -1;
    }

    for (i = 0; i < count; ++i) {
        tuples[i].first = left[i];
        tuples[i].second = right[i];
    }

    *result = tuples;
    *result_size = count;
    return 0;
}

int main(void)
{
    const int first_tuple[] = {1, 2, 3, 4};
    const int second_tuple[] = {5, 6, 7, 8};
    Tuple *result = NULL;
    size_t result_size = 0;
    size_t i;

    if (create_elementwise_tuples(
            first_tuple,
            sizeof(first_tuple) / sizeof(first_tuple[0]),
            second_tuple,
            sizeof(second_tuple) / sizeof(second_tuple[0]),
            &result,
            &result_size) != 0) {
        fputs("Failed to create elementwise tuples.\n", stderr);
        return EXIT_FAILURE;
    }

    for (i = 0; i < result_size; ++i) {
        if (printf("(%d, %d)%s",
                   result[i].first,
                   result[i].second,
                   i + 1 == result_size ? "\n" : ", ") < 0) {
            free(result);
            return EXIT_FAILURE;
        }
    }

    free(result);
    return EXIT_SUCCESS;
}