#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    size_t length;
} Tuple;

static bool all_tuples_have_equal_length(const Tuple *tuples, size_t count)
{
    size_t index;
    size_t expected_length;

    if (count == 0U) {
        return true;
    }

    if (tuples == NULL) {
        return false;
    }

    expected_length = tuples[0].length;

    for (index = 1U; index < count; ++index) {
        if (tuples[index].length != expected_length) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    const Tuple tuples[] = {
        {3U},
        {3U},
        {3U}
    };
    const size_t tuple_count = sizeof(tuples) / sizeof(tuples[0]);

    if (all_tuples_have_equal_length(tuples, tuple_count)) {
        puts("All tuples have equal length.");
    } else {
        puts("The tuples do not have equal length.");
    }

    return EXIT_SUCCESS;
}