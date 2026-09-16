#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const int *elements;
    size_t length;
} Tuple;

bool all_tuples_have_k_elements(const Tuple *tuples, size_t tuple_count, size_t k)
{
    if (tuples == NULL && tuple_count != 0U) {
        return false;
    }

    for (size_t i = 0U; i < tuple_count; ++i) {
        if (tuples[i].length != k) {
            return false;
        }

        if (k != 0U && tuples[i].elements == NULL) {
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
    const size_t k = 3U;
    const bool result = all_tuples_have_k_elements(tuples, tuple_count, k);

    if (printf("%s\n", result ? "true" : "false") < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}