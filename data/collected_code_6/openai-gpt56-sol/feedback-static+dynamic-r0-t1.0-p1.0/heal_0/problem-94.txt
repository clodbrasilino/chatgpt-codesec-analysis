#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int index;
    double value;
} Record;

static int find_min_value_record(const Record *records, size_t count, size_t *result_index)
{
    if (records == NULL || result_index == NULL || count == 0U) {
        return -1;
    }

    size_t min_index = 0U;

    for (size_t i = 1U; i < count; ++i) {
        if (records[i].value < records[min_index].value) {
            min_index = i;
        }
    }

    *result_index = min_index;
    return 0;
}

int main(void)
{
    Record records[] = {
        {10, 4.5},
        {20, 1.2},
        {30, 3.8},
        {40, -2.4},
        {50, 0.0}
    };
    size_t min_index;

    if (find_min_value_record(
            records,
            sizeof(records) / sizeof(records[0]),
            &min_index) != 0) {
        fputs("Failed to find the minimum value record.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("index=%d value=%.6f\n",
               records[min_index].index,
               records[min_index].value) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}