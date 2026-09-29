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
    size_t i;

    if (count == 0U) {
        return true;
    }

    if (tuples == NULL || !tuple_is_valid(&tuples[0])) {
        return false;
    }

    expected_length = tuples[0].length;

    for (i = 1U; i < count; ++i) {
        if (!tuple_is_valid(&tuples[i]) ||
            tuples[i].length != expected_length) {
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

    const size_t count = sizeof tuples / sizeof tuples[0];
    const bool equal = all_tuples_have_equal_length(tuples, count);

    /* Possible weaknesses found:
     * Flawfinder equal: Function does not check the second iterator for over-read conditions (CWE-126). This function is often discouraged by most C++ coding standards in favor of its safer alternatives provided since C++14. Consider using a form of this function that checks the second iterator before potentially overflowing it. (risk 1, buffer)
     */
    if (puts(equal ? "Equal length" : "Different lengths") == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}