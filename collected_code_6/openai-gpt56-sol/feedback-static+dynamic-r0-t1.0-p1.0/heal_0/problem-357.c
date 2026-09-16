#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct {
    int *elements;
    size_t count;
} Tuple;

int find_maximum(const Tuple *tuples, size_t tuple_count, int *maximum)
{
    size_t i;
    size_t j;
    int found = 0;

    if (tuples == NULL || maximum == NULL) {
        return -1;
    }

    for (i = 0; i < tuple_count; ++i) {
        if (tuples[i].count > 0U && tuples[i].elements == NULL) {
            return -1;
        }

        for (j = 0; j < tuples[i].count; ++j) {
            if (!found || tuples[i].elements[j] > *maximum) {
                *maximum = tuples[i].elements[j];
                found = 1;
            }
        }
    }

    return found ? 0 : -1;
}

int main(void)
{
    int first[] = {3, 8, 2};
    int second[] = {-4, 12, 5, 7};
    int third[] = {6, 1};
    Tuple tuples[] = {
        {first, sizeof first / sizeof first[0]},
        {second, sizeof second / sizeof second[0]},
        {third, sizeof third / sizeof third[0]}
    };
    int maximum;

    if (find_maximum(tuples, sizeof tuples / sizeof tuples[0], &maximum) != 0) {
        fputs("Unable to find a maximum element.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%d\n", maximum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}