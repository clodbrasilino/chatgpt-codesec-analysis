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

static int find_similar_elements(const Tuple *first_list, size_t first_count,
                                 const Tuple *second_list, size_t second_count,
                                 Tuple **result, size_t *result_count)
{
    Tuple *matches = NULL;
    size_t count = 0;

    if (result == NULL || result_count == NULL) {
        return -1;
    }

    *result = NULL;
    *result_count = 0;

    if ((first_count > 0 && first_list == NULL) ||
        (second_count > 0 && second_list == NULL)) {
        return -1;
    }

    if (first_count > SIZE_MAX / sizeof(*matches)) {
        return -1;
    }

    if (first_count > 0) {
        matches = malloc(first_count * sizeof(*matches));
        if (matches == NULL) {
            return -1;
        }
    }

    for (size_t i = 0; i < first_count; ++i) {
        bool present_in_second = false;
        bool already_added = false;

        for (size_t j = 0; j < second_count; ++j) {
            if (tuples_equal(&first_list[i], &second_list[j])) {
                present_in_second = true;
                break;
            }
        }

        if (!present_in_second) {
            continue;
        }

        for (size_t j = 0; j < count; ++j) {
            if (tuples_equal(&first_list[i], &matches[j])) {
                already_added = true;
                break;
            }
        }

        if (!already_added) {
            matches[count++] = first_list[i];
        }
    }

    if (count == 0) {
        free(matches);
        matches = NULL;
    } else {
        Tuple *resized = realloc(matches, count * sizeof(*matches));
        if (resized != NULL) {
            matches = resized;
        }
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