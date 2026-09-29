#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int index;
    double value;
} Tuple;

static int find_min_value_index(const Tuple *tuples, size_t count, int *result)
{
    size_t min_position;

    if (tuples == NULL || result == NULL || count == 0U) {
        return -1;
    }

    min_position = 0U;

    for (size_t i = 1U; i < count; ++i) {
        if (tuples[i].value < tuples[min_position].value) {
            min_position = i;
        }
    }

    *result = tuples[min_position].index;
    return 0;
}

int main(void)
{
    Tuple tuples[] = {
        {10, 4.5},
        {20, 1.2},
        {30, 3.8},
        {40, -2.0}
    };
    const size_t count = sizeof tuples / sizeof tuples[0];
    int index;

    if (find_min_value_index(tuples, count, &index) != 0) {
        errno = EINVAL;
        perror("find_min_value_index");
        return EXIT_FAILURE;
    }

    if (printf("%d\n", index) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}