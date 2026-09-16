#include <stdio.h>
#include <stdlib.h>

struct Tuple {
    int first;
    int second;
};

int find_max_of_tuples(const struct Tuple *records, size_t count, int *max_out)
{
    size_t i;
    int max_val;

    if (records == NULL || max_out == NULL || count == 0U) {
        return -1;
    }

    max_val = records[0].first;
    if (records[0].second > max_val) {
        max_val = records[0].second;
    }

    for (i = 1U; i < count; i++) {
        if (records[i].first > max_val) {
            max_val = records[i].first;
        }
        if (records[i].second > max_val) {
            max_val = records[i].second;
        }
    }

    *max_out = max_val;
    return 0;
}

int main(void)
{
    struct Tuple records[] = {
        {3, 7},
        {12, 5},
        {9, 21},
        {14, 2}
    };
    size_t count = sizeof(records) / sizeof(records[0]);
    int max_val = 0;

    if (find_max_of_tuples(records, count, &max_val) != 0) {
        fprintf(stderr, "Error: invalid input to find_max_of_tuples\n");
        return EXIT_FAILURE;
    }

    if (printf("Maximum element: %d\n", max_val) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}