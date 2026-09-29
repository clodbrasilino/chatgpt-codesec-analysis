#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int start;
    int end;
} Range;

typedef struct {
    Range *ranges;
    int count;
    int capacity;
} RangeList;

static int compare_ranges(const void *a, const void *b) {
    const Range *ra = (const Range *)a;
    const Range *rb = (const Range *)b;
    if (ra->start != rb->start)
        return ra->start - rb->start;
    return ra->end - rb->end;
}

static void init_range_list(RangeList *list) {
    list->ranges = NULL;
    list->count = 0;
    list->capacity = 0;
}

static int add_range(RangeList *list, int start, int end) {
    if (list->count >= list->capacity) {
        int new_capacity = list->capacity == 0 ? 8 : list->capacity * 2;
        Range *new_ranges = (Range *)realloc(list->ranges, new_capacity * sizeof(Range));
        if (new_ranges == NULL)
            return 0;
        list->ranges = new_ranges;
        list->capacity = new_capacity;
    }
    list->ranges[list->count].start = start;
    list->ranges[list->count].end = end;
    list->count++;
    return 1;
}

static void free_range_list(RangeList *list) {
    free(list->ranges);
    list->ranges = NULL;
    list->count = 0;
    list->capacity = 0;
}

RangeList find_missing_ranges(const Range *ranges, int range_count, int start_range, int end_range) {
    RangeList missing;
    init_range_list(&missing);

    if (range_count <= 0 || ranges == NULL) {
        if (start_range <= end_range) {
            if (!add_range(&missing, start_range, end_range)) {
                free_range_list(&missing);
                return missing;
            }
        }
        return missing;
    }

    Range *sorted = (Range *)malloc(range_count * sizeof(Range));
    if (sorted == NULL)
        return missing;

    for (int i = 0; i < range_count; i++) {
        sorted[i] = ranges[i];
    }

    qsort(sorted, range_count, sizeof(Range), compare_ranges);

    int current = start_range;

    for (int i = 0; i < range_count; i++) {
        if (sorted[i].end < current)
            continue;

        if (sorted[i].start > current) {
            int missing_end = sorted[i].start - 1;
            if (missing_end > end_range)
                missing_end = end_range;
            if (current <= missing_end) {
                if (!add_range(&missing, current, missing_end)) {
                    free(sorted);
                    free_range_list(&missing);
                    return missing;
                }
            }
            current = sorted[i].end + 1;
        } else {
            if (sorted[i].end + 1 > current)
                current = sorted[i].end + 1;
        }

        if (current > end_range)
            break;
    }

    if (current <= end_range) {
        if (!add_range(&missing, current, end_range)) {
            free(sorted);
            free_range_list(&missing);
            return missing;
        }
    }

    free(sorted);
    return missing;
}

int main(void) {
    Range ranges[] = {
        {2, 5},
        {8, 10},
        {15, 18},
        {20, 20}
    };
    int range_count = sizeof(ranges) / sizeof(ranges[0]);
    int start_range = 1;
    int end_range = 25;

    RangeList missing = find_missing_ranges(ranges, range_count, start_range, end_range);

    printf("Missing ranges:\n");
    for (int i = 0; i < missing.count; i++) {
        printf("[%d, %d]\n", missing.ranges[i].start, missing.ranges[i].end);
    }

    free_range_list(&missing);

    return 0;
}