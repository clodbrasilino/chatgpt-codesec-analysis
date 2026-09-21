#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const int *elements;
    size_t length;
} Tuple;

static bool all_tuples_have_equal_length(const Tuple *tuples, size_t count)
{
    size_t expected_length;
    size_t i;

    if (count == 0U) {
        return true;
    }

    if (tuples == NULL) {
        return false;
    }

    expected_length = tuples[0].length;

    for (i = 0U; i < count; ++i) {
        if (tuples[i].length > 0U && tuples[i].elements == NULL) {
            return false;
        }

        if (tuples[i].length != expected_length) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    static const int first[] = {1, 2, 3};
    static const int second[] = {4, 5, 6};
    static const int third[] = {7, 8, 9};

    static const Tuple tuples[] = {
        {first, sizeof first / sizeof first[0]},
        {second, sizeof second / sizeof second[0]},
        {third, sizeof third / sizeof third[0]}
    };

    const size_t tuple_count = sizeof tuples / sizeof tuples[0];
    const bool same_length =
        all_tuples_have_equal_length(tuples, tuple_count);

    if (puts(same_length ? "Equal length" : "Different lengths") == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}