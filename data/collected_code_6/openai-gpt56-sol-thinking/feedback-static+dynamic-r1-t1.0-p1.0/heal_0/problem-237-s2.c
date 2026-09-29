#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static bool records_equal(const int *tuples, size_t width, size_t first, size_t second)
{
    size_t field;

    for (field = 0; field < width; ++field) {
        if (tuples[first * width + field] != tuples[second * width + field]) {
            return false;
        }
    }

    return true;
}

static size_t record_occurrences(const int *tuples, size_t count, size_t width, size_t index)
{
    size_t occurrences = 0;
    size_t current;

    for (current = 0; current < count; ++current) {
        if (records_equal(tuples, width, index, current)) {
            ++occurrences;
        }
    }

    return occurrences;
}

static bool is_first_occurrence(const int *tuples, size_t width, size_t index)
{
    size_t current;

    for (current = 0; current < index; ++current) {
        if (records_equal(tuples, width, index, current)) {
            return false;
        }
    }

    return true;
}

static bool records_have_similar_occurrences(const int *tuples, size_t count, size_t width)
{
    size_t first;
    size_t second;

    if ((tuples == NULL && count != 0) || width == 0) {
        return false;
    }

    for (first = 0; first < count; ++first) {
        size_t first_count;

        if (!is_first_occurrence(tuples, width, first)) {
            continue;
        }

        first_count = record_occurrences(tuples, count, width, first);

        for (second = first + 1; second < count; ++second) {
            size_t second_count;

            if (!is_first_occurrence(tuples, width, second)) {
                continue;
            }

            second_count = record_occurrences(tuples, count, width, second);

            if (first_count == second_count) {
                return true;
            }
        }
    }

    return false;
}

int main(void)
{
    int *tuples = NULL;
    size_t tuple_count;
    size_t tuple_width;
    size_t element_count;
    size_t index;
    bool result;

    if (scanf("%zu %zu", &tuple_count, &tuple_width) != 2 || tuple_width == 0) {
        return EXIT_FAILURE;
    }

    if (tuple_count > SIZE_MAX / tuple_width) {
        return EXIT_FAILURE;
    }

    element_count = tuple_count * tuple_width;

    if (element_count > SIZE_MAX / sizeof(*tuples)) {
        return EXIT_FAILURE;
    }

    if (element_count != 0) {
        tuples = malloc(element_count * sizeof(*tuples));
        if (tuples == NULL) {
            return EXIT_FAILURE;
        }
    }

    for (index = 0; index < element_count; ++index) {
        if (scanf("%d", &tuples[index]) != 1) {
            free(tuples);
            return EXIT_FAILURE;
        }
    }

    result = records_have_similar_occurrences(tuples, tuple_count, tuple_width);
    printf("%s\n", result ? "true" : "false");

    free(tuples);
    return EXIT_SUCCESS;
}