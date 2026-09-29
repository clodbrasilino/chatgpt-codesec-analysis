#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const int *elements;
    size_t length;
} Tuple;

static bool tuple_is_valid(const Tuple *tuple)
{
    return tuple != NULL &&
           (tuple->length == 0U || tuple->elements != NULL);
}

static bool all_tuples_have_equal_length(const Tuple *tuples, size_t count)
{
    size_t expected_length;

    if (count == 0U) {
        return true;
    }

    if (tuples == NULL || !tuple_is_valid(&tuples[0])) {
        return false;
    }

    expected_length = tuples[0].length;

    for (size_t index = 1U; index < count; ++index) {
        if (!tuple_is_valid(&tuples[index]) ||
            tuples[index].length != expected_length) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    const int first[] = {1, 2, 3};
    const int second[] = {4, 5, 6};
    const int third[] = {7, 8, 9};

    const Tuple tuples[] = {
        {first, sizeof first / sizeof first[0]},
        {second, sizeof second / sizeof second[0]},
        {third, sizeof third / sizeof third[0]}
    };

    const size_t tuple_count = sizeof tuples / sizeof tuples[0];

    if (all_tuples_have_equal_length(tuples, tuple_count)) {
        puts("All tuples have equal length.");
    } else {
        puts("The tuples do not have equal length.");
    }

    return EXIT_SUCCESS;
}