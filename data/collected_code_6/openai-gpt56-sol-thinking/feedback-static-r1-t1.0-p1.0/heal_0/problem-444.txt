#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *elements;
    size_t length;
} Tuple;

bool trim_tuple_list(Tuple *tuples, size_t tuple_count, size_t k)
{
    if (tuples == NULL && tuple_count != 0) {
        return false;
    }

    for (size_t i = 0; i < tuple_count; ++i) {
        if ((tuples[i].elements == NULL && tuples[i].length != 0) ||
            tuples[i].length > SIZE_MAX / sizeof(*tuples[i].elements)) {
            return false;
        }
    }

    for (size_t i = 0; i < tuple_count; ++i) {
        size_t length = tuples[i].length;

        if (k >= length || k >= length - k) {
            tuples[i].length = 0;
            continue;
        }

        size_t new_length = length - (2 * k);

        memmove(
            tuples[i].elements,
            tuples[i].elements + k,
            new_length * sizeof(*tuples[i].elements)
        );

        tuples[i].length = new_length;
    }

    return true;
}

bool print_tuple_list(const Tuple *tuples, size_t tuple_count)
{
    if (tuples == NULL && tuple_count != 0) {
        return false;
    }

    if (putchar('[') == EOF) {
        return false;
    }

    for (size_t i = 0; i < tuple_count; ++i) {
        if (putchar('(') == EOF) {
            return false;
        }

        for (size_t j = 0; j < tuples[i].length; ++j) {
            if (printf("%d%s", tuples[i].elements[j],
                       j + 1 < tuples[i].length ? ", " : "") < 0) {
                return false;
            }
        }

        if (printf(")%s", i + 1 < tuple_count ? ", " : "") < 0) {
            return false;
        }
    }

    return puts("]") != EOF;
}

int main(void)
{
    int first[] = {1, 2, 3, 4, 5};
    int second[] = {6, 7, 8, 9, 10, 11};
    int third[] = {12, 13, 14};

    Tuple tuples[] = {
        {first, sizeof(first) / sizeof(first[0])},
        {second, sizeof(second) / sizeof(second[0])},
        {third, sizeof(third) / sizeof(third[0])}
    };

    size_t tuple_count = sizeof(tuples) / sizeof(tuples[0]);
    size_t k = 1;

    if (!trim_tuple_list(tuples, tuple_count, k)) {
        if (fputs("Failed to trim tuple list\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (!print_tuple_list(tuples, tuple_count)) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}