#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

static int *extract_elementwise(const Tuple *tuple1, size_t size1,
                                const Tuple *tuple2, size_t size2,
                                size_t *result_size)
{
    int *result;
    size_t pair_count;
    size_t i;

    if (result_size == NULL ||
        (tuple1 == NULL && size1 != 0) ||
        (tuple2 == NULL && size2 != 0)) {
        return NULL;
    }

    *result_size = 0;
    pair_count = size1 < size2 ? size1 : size2;

    if (pair_count == 0) {
        return NULL;
    }

    if (pair_count > SIZE_MAX / (4U * sizeof(*result))) {
        return NULL;
    }

    result = malloc(pair_count * 4U * sizeof(*result));
    if (result == NULL) {
        return NULL;
    }

    for (i = 0; i < pair_count; ++i) {
        result[i * 4U] = tuple1[i].first;
        result[i * 4U + 1U] = tuple1[i].second;
        result[i * 4U + 2U] = tuple2[i].first;
        result[i * 4U + 3U] = tuple2[i].second;
    }

    *result_size = pair_count * 4U;
    return result;
}

static Tuple *extract_tuples(const Tuple *tuple1, size_t size1,
                             const Tuple *tuple2, size_t size2,
                             size_t *result_size)
{
    Tuple *result;
    size_t total_size;
    size_t i;

    if (result_size == NULL ||
        (tuple1 == NULL && size1 != 0) ||
        (tuple2 == NULL && size2 != 0)) {
        return NULL;
    }

    *result_size = 0;

    if (size1 > SIZE_MAX - size2) {
        return NULL;
    }

    total_size = size1 + size2;

    if (total_size == 0) {
        return NULL;
    }

    if (total_size > SIZE_MAX / sizeof(*result)) {
        return NULL;
    }

    result = malloc(total_size * sizeof(*result));
    if (result == NULL) {
        return NULL;
    }

    for (i = 0; i < size1; ++i) {
        result[i] = tuple1[i];
    }

    for (i = 0; i < size2; ++i) {
        result[size1 + i] = tuple2[i];
    }

    *result_size = total_size;
    return result;
}

int main(void)
{
    const Tuple first[] = {{1, 2}, {3, 4}};
    const Tuple second[] = {{5, 6}, {7, 8}};
    const size_t first_size = sizeof(first) / sizeof(first[0]);
    const size_t second_size = sizeof(second) / sizeof(second[0]);
    size_t element_count;
    size_t tuple_count;
    int *elements;
    Tuple *tuples;
    size_t i;

    elements = extract_elementwise(first, first_size, second, second_size,
                                   &element_count);
    if (elements == NULL && element_count != 0) {
        return EXIT_FAILURE;
    }

    tuples = extract_tuples(first, first_size, second, second_size,
                            &tuple_count);
    if (tuples == NULL && tuple_count != 0) {
        free(elements);
        return EXIT_FAILURE;
    }

    for (i = 0; i < element_count; ++i) {
        if (printf("%d%c", elements[i],
                   i + 1U == element_count ? '\n' : ' ') < 0) {
            free(tuples);
            free(elements);
            return EXIT_FAILURE;
        }
    }

    for (i = 0; i < tuple_count; ++i) {
        if (printf("(%d, %d)%c", tuples[i].first, tuples[i].second,
                   i + 1U == tuple_count ? '\n' : ' ') < 0) {
            free(tuples);
            free(elements);
            return EXIT_FAILURE;
        }
    }

    free(tuples);
    free(elements);
    return EXIT_SUCCESS;
}