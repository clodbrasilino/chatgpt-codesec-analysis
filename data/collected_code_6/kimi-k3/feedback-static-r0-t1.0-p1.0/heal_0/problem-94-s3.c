#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int index;
    int value;
} Tuple;

int find_min_index(const Tuple *records, size_t count)
{
    size_t i;
    size_t min_pos;
    int min_val;

    if (records == NULL || count == 0U) {
        return -1;
    }

    min_val = INT_MAX;
    min_pos = 0U;

    for (i = 0U; i < count; ++i) {
        if (records[i].value < min_val) {
            min_val = records[i].value;
            min_pos = i;
        }
    }

    return records[min_pos].index;
}

int main(void)
{
    Tuple records[] = {
        {0, 45},
        {1, 12},
        {2, 78},
        {3, 5},
        {4, 23}
    };
    size_t count = sizeof(records) / sizeof(records[0]);
    int result;

    result = find_min_index(records, count);

    if (result >= 0) {
        printf("Index of minimum value: %d\n", result);
    } else {
        printf("No valid records found.\n");
    }

    return 0;
}