#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

static bool tuples_equal(const Tuple *left, const Tuple *right)
{
    return left->first == right->first && left->second == right->second;
}

static bool remove_matching_tuples(
    Tuple *first,
    size_t *first_count,
    Tuple *second,
    size_t *second_count)
{
    bool *remove_first = NULL;
    bool *remove_second = NULL;
    size_t i;
    size_t j;
    size_t write_index;

    if (first_count == NULL || second_count == NULL) {
        return false;
    }

    if ((*first_count > 0 && first == NULL) ||
        (*second_count > 0 && second == NULL)) {
        return false;
    }

    if (*first_count > 0) {
        remove_first = calloc(*first_count, sizeof(*remove_first));
        if (remove_first == NULL) {
            return false;
        }
    }

    if (*second_count > 0) {
        remove_second = calloc(*second_count, sizeof(*remove_second));
        if (remove_second == NULL) {
            free(remove_first);
            return false;
        }
    }

    for (i = 0; i < *first_count; ++i) {
        for (j = 0; j < *second_count; ++j) {
            if (tuples_equal(&first[i], &second[j])) {
                remove_first[i] = true;
                remove_second[j] = true;
            }
        }
    }

    write_index = 0;
    for (i = 0; i < *first_count; ++i) {
        if (!remove_first[i]) {
            first[write_index++] = first[i];
        }
    }
    *first_count = write_index;

    write_index = 0;
    for (j = 0; j < *second_count; ++j) {
        if (!remove_second[j]) {
            second[write_index++] = second[j];
        }
    }
    *second_count = write_index;

    free(remove_first);
    free(remove_second);
    return true;
}

static bool print_tuples(const Tuple *tuples, size_t count)
{
    size_t i;

    for (i = 0; i < count; ++i) {
        if (printf("(%d, %d)%s",
                   tuples[i].first,
                   tuples[i].second,
                   i + 1 < count ? " " : "\n") < 0) {
            return false;
        }
    }

    if (count == 0 && printf("Empty\n") < 0) {
        return false;
    }

    return true;
}

int main(void)
{
    Tuple first[] = {
        {1, 2},
        {3, 4},
        {5, 6},
        {7, 8}
    };
    Tuple second[] = {
        {3, 4},
        {7, 8},
        {9, 10}
    };
    size_t first_count = sizeof(first) / sizeof(first[0]);
    size_t second_count = sizeof(second) / sizeof(second[0]);

    if (!remove_matching_tuples(
            first, &first_count, second, &second_count)) {
        return EXIT_FAILURE;
    }

    if (!print_tuples(first, first_count) ||
        !print_tuples(second, second_count)) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}