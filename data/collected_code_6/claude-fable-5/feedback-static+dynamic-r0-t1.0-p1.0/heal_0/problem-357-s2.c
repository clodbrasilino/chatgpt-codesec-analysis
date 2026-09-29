#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

int find_max_element(const Tuple *records, size_t count, int *result)
{
    size_t i;
    int max;

    if (records == NULL || result == NULL || count == 0U) {
        return -1;
    }

    max = records[0].first;
    if (records[0].second > max) {
        max = records[0].second;
    }

    for (i = 1U; i < count; i++) {
        if (records[i].first > max) {
            max = records[i].first;
        }
        if (records[i].second > max) {
            max = records[i].second;
        }
    }

    *result = max;
    return 0;
}

int main(void)
{
    Tuple records[] = {
        {3, 7},
        {12, 5},
        {9, 14},
        {2, 8}
    };
    size_t count = sizeof(records) / sizeof(records[0]);
    int max_value = 0;

    if (find_max_element(records, count, &max_value) != 0) {
        fprintf(stderr, "Error: unable to find maximum element\n");
        return EXIT_FAILURE;
    }

    if (printf("Maximum element: %d\n", max_value) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}