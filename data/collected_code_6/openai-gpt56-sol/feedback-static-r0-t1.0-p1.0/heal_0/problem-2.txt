#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int first;
    int second;
} Tuple;

static bool tuples_equal(const Tuple *left, const Tuple *right)
{
    return left->first == right->first && left->second == right->second;
}

static bool contains_tuple(const Tuple *tuples, size_t count, const Tuple *target)
{
    for (size_t i = 0; i < count; ++i) {
        if (tuples_equal(&tuples[i], target)) {
            return true;
        }
    }

    return false;
}

static int find_similar_elements(const Tuple *first_list,
                                 size_t first_count,
                                 const Tuple *second_list,
                                 size_t second_count,
                                 Tuple **result,
                                 size_t *result_count)
{
    Tuple *matches = NULL;
    size_t count = 0;

    if (result == NULL || result_count == NULL) {
        return -1;
    }

    *result = NULL;
    *result_count = 0;

    if ((first_list == NULL && first_count != 0) ||
        (second_list == NULL && second_count != 0)) {
        return -1;
    }

    if (first_count == 0 || second_count == 0) {
        return 0;
    }

    if (first_count > SIZE_MAX / sizeof(*matches)) {
        return -1;
    }

    matches = malloc(first_count * sizeof(*matches));
    if (matches == NULL) {
        return -1;
    }

    for (size_t i = 0; i < first_count; ++i) {
        if (contains_tuple(second_list, second_count, &first_list[i]) &&
            !contains_tuple(matches, count, &first_list[i])) {
            matches[count++] = first_list[i];
        }
    }

    if (count == 0) {
        free(matches);
        return 0;
    }

    Tuple *resized = realloc(matches, count * sizeof(*matches));
    if (resized != NULL) {
        matches = resized;
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
        {7, 8},
        {3, 4},
        {5, 6},
        {9, 10}
    };
    Tuple *similar = NULL;
    size_t similar_count = 0;

    if (find_similar_elements(first_list,
                              sizeof(first_list) / sizeof(first_list[0]),
                              second_list,
                              sizeof(second_list) / sizeof(second_list[0]),
                              &similar,
                              &similar_count) != 0) {
        fputs("Failed to find similar elements.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < similar_count; ++i) {
        if (printf("(%d, %d)\n", similar[i].first, similar[i].second) < 0) {
            free(similar);
            return EXIT_FAILURE;
        }
    }

    free(similar);
    return EXIT_SUCCESS;
}