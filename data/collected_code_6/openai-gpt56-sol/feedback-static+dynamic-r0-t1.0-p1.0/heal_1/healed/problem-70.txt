#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

typedef struct {
    size_t length;
} Tuple;

bool all_tuples_have_equal_length(const Tuple *tuples, size_t count)
{
    if (count == 0U) {
        return true;
    }

    if (tuples == NULL) {
        return false;
    }

    const size_t expected_length = tuples[0].length;

    for (size_t i = 1U; i < count; ++i) {
        if (tuples[i].length != expected_length) {
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
        {sizeof first / sizeof first[0]},
        {sizeof second / sizeof second[0]},
        {sizeof third / sizeof third[0]}
    };

    const size_t tuple_count = sizeof tuples / sizeof tuples[0];
    const char *message = all_tuples_have_equal_length(tuples, tuple_count)
                              ? "All tuples have equal length."
                              : "The tuples do not have equal length.";

    return puts(message) == EOF ? 1 : 0;
}