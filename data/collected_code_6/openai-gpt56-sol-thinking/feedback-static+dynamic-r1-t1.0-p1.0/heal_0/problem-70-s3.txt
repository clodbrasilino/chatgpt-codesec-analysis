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
    size_t i;

    if (count == 0U) {
        return true;
    }

    if (tuples == NULL) {
        return false;
    }

    for (i = 0U; i < count; ++i) {
        if (tuples[i].length > 0U && tuples[i].elements == NULL) {
            return false;
        }

        if (i > 0U && tuples[i].length != tuples[0].length) {
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
        {first, sizeof(first) / sizeof(first[0])},
        {second, sizeof(second) / sizeof(second[0])},
        {third, sizeof(third) / sizeof(third[0])}
    };
    const size_t count = sizeof(tuples) / sizeof(tuples[0]);
    const bool equal = all_tuples_have_equal_length(tuples, count);

    if (printf("%s\n", equal ? "Equal length" : "Different lengths") < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}