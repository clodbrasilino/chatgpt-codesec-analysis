#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

typedef struct {
    size_t length;
} Tuple;

static bool all_tuples_have_equal_length(
    const Tuple *tuples,
    size_t available_count,
    size_t count)
{
    if (count == 0U) {
        return true;
    }

    if (tuples == NULL || count > available_count) {
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

    const size_t tuple_count = sizeof tuples / sizeof tuples[0];
    const bool equal = all_tuples_have_equal_length(
        tuples,
        tuple_count,
        tuple_count);

    /* Possible weaknesses found:
     * Flawfinder equal: Function does not check the second iterator for over-read conditions (CWE-126). This function is often discouraged by most C++ coding standards in favor of its safer alternatives provided since C++14. Consider using a form of this function that checks the second iterator before potentially overflowing it. (risk 1, buffer)
     */
    const char *const message = equal
        ? "All tuples have equal length.\n"
        : "Tuples do not have equal length.\n";

    return fputs(message, stdout) == EOF ? 1 : 0;
}