#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

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
    const Tuple tuples[] = {
        {3U},
        {3U},
        {3U}
    };

    const size_t tuple_count = sizeof(tuples) / sizeof(tuples[0]);

    puts(all_tuples_have_equal_length(tuples, tuple_count) ? "true" : "false");

    return EXIT_SUCCESS;
}