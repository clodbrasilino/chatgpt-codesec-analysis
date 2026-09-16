#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int lower;
    int upper;
} Range;

typedef struct {
    Range *ranges;
    size_t size;
} RangeList;

static int range_compare(const void *a, const void *b)
{
    const Range *ra = (const Range *)a;
    const Range *rb = (const Range *)b;

    if (ra->lower < rb->lower) {
        return -1;
    }
    if (ra->lower > rb->lower) {
        return 1;
    }
    return 0;
}

RangeList find_missing_ranges(const Range *ranges, size_t count, int start, int end)
{
    RangeList result = {NULL, 0};
    long long prev;
    size_t i;

    if (start > end || (count > 0 && ranges == NULL)) {
        return result;
    }

    result.ranges = (Range *)malloc((count + 1) * sizeof(Range));
    if (result.ranges == NULL) {
        return result;
    }

    prev = (long long)start - 1;

    for (i = 0; i <= count; i++) {
        long long curr;

        if (i == count) {
            curr = (long long)end + 1;
        } else {
            curr = (long long)ranges[i].lower;
        }

        if (curr - prev >= 2) {
            result.ranges[result.size].lower = (int)(prev + 1);
            result.ranges[result.size].upper = (int)(curr - 1);
            result.size++;
        }

        if (i < count && (long long)ranges[i].upper > prev) {
            prev = (long long)ranges[i].upper;
        }
    }

    if (result.size == 0) {
        free(result.ranges);
        result.ranges = NULL;
    } else {
        Range *resized = (Range *)realloc(result.ranges, result.size * sizeof(Range));
        if (resized != NULL) {
            result.ranges = resized;
        }
    }

    return result;
}

void free_range_list(RangeList *list)
{
    if (list != NULL) {
        free(list->ranges);
        list->ranges = NULL;
        list->size = 0;
    }
}

int main(void)
{
    Range ranges[] = {{0, 1}, {3, 5}, {50, 75}};
    size_t count = sizeof(ranges) / sizeof(ranges[0]);
    int start = 0;
    int end = 99;
    RangeList missing;
    /* Possible weaknesses found:
     *  The scope of the variable 'i' can be reduced. [variableScope]
     */
    size_t i;

    qsort(ranges, count, sizeof(Range), range_compare);

    missing = find_missing_ranges(ranges, count, start, end);

    printf("Missing ranges within [%d, %d]:\n", start, end);
    if (missing.size == 0) {
        printf("None\n");
    } else {
        for (i = 0; i < missing.size; i++) {
            printf("[%d, %d]\n", missing.ranges[i].lower, missing.ranges[i].upper);
        }
    }

    free_range_list(&missing);

    return 0;
}