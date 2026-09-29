#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

static int tuple_equal(const Tuple *left, const Tuple *right)
{
    return left->first == right->first && left->second == right->second;
}

static int contains_tuple(const Tuple *tuples, size_t count, const Tuple *target)
{
    size_t i;

    for (i = 0; i < count; ++i) {
        if (tuple_equal(&tuples[i], target)) {
            return 1;
        }
    }

    return 0;
}

static int find_similar_elements(
    const Tuple *first_list,
    size_t first_count,
    const Tuple *second_list,
    size_t second_count,
    Tuple **result,
    size_t *result_count)
{
    Tuple *matches;
    size_t capacity;
    size_t count = 0;
    size_t i;

    if (result == NULL || result_count == NULL) {
        return -1;
    }

    *result = NULL;
    *result_count = 0;

    if ((first_list == NULL && first_count != 0) ||
        (second_list == NULL && second_count != 0)) {
        return -1;
    }

    capacity = first_count < second_count ? first_count : second_count;

    if (capacity == 0) {
        return 0;
    }

    if (capacity > SIZE_MAX / sizeof(*matches)) {
        return -1;
    }

    matches = malloc(capacity * sizeof(*matches));
    if (matches == NULL) {
        return -1;
    }

    for (i = 0; i < first_count; ++i) {
        if (contains_tuple(second_list, second_count, &first_list[i]) &&
            !contains_tuple(matches, count, &first_list[i])) {
            matches[count++] = first_list[i];
        }
    }

    if (count == 0) {
        free(matches);
        return 0;
    }

    *result = matches;
    *result_count = count;
    return 0;
}

int main(void)
{
    const Tuple first_list[] = {
        {1, 2},
        {3, 4},
        {5, 6},
        {3, 4}
    };
    const Tuple second_list[] = {
        {3, 4},
        {7, 8},
        {1, 2}
    };
    Tuple *similar = NULL;
    size_t similar_count = 0;
    size_t i;
    int status;

    status = find_similar_elements(
        first_list,
        sizeof(first_list) / sizeof(first_list[0]),
        second_list,
        sizeof(second_list) / sizeof(second_list[0]),
        &similar,
        &similar_count);

    if (status != 0) {
        fputs("Failed to find similar elements.\n", stderr);
        return EXIT_FAILURE;
    }

    for (i = 0; i < similar_count; ++i) {
        if (printf("(%d, %d)\n", similar[i].first, similar[i].second) < 0) {
            free(similar);
            return EXIT_FAILURE;
        }
    }

    free(similar);
    return EXIT_SUCCESS;
}