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
    if (ra->start != rb->start) {
        return ra->start - rb->start;
    }
    return ra->end - rb->end;
}

static void init_range_list(RangeList *list) {
    list->ranges = NULL;
    list->count = 0;
    list->capacity = 0;
}

static int add_range(RangeList *list, int start, int end) {
    if (list->count >= list->capacity) {
        int new_capacity = list->capacity == 0 ? 16 : list->capacity * 2;
        Range *new_ranges = (Range *)realloc(list->ranges, new_capacity * sizeof(Range));
        if (new_ranges == NULL) {
            return 0;
        }
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
    RangeList result;
    init_range_list(&result);

    if (range_count <= 0 || start_range > end_range) {
        return result;
    }

    Range *sorted_ranges = (Range *)malloc(range_count * sizeof(Range));
    if (sorted_ranges == NULL) {
        return result;
    }

    for (int i = 0; i < range_count; i++) {
        sorted_ranges[i] = ranges[i];
    }

    qsort(sorted_ranges, range_count, sizeof(Range), compare_ranges);

    int current = start_range;

    for (int i = 0; i < range_count; i++) {
        if (sorted_ranges[i].end < current) {
            continue;
        }

        if (sorted_ranges[i].start > end_range) {
            break;
        }

        if (sorted_ranges[i].start > current) {
            int missing_end = sorted_ranges[i].start - 1;
            if (missing_end > end_range) {
                missing_end = end_range;
            }
            if (!add_range(&result, current, missing_end)) {
                free(sorted_ranges);
                free_range_list(&result);
                init_range_list(&result);
                return result;
            }
        }

        if (sorted_ranges[i].end >= end_range) {
            current = end_range + 1;
            break;
        }

        current = sorted_ranges[i].end + 1;
    }

    if (current <= end_range) {
        if (!add_range(&result, current, end_range)) {
            free(sorted_ranges);
            free_range_list(&result);
            init_range_list(&result);
            return result;
        }
    }

    free(sorted_ranges);
    return result;
}

int main(void) {
    Range input_ranges[] = {
        {1, 3},
        {5, 7},
        {10, 12},
        {15, 18}
    };
    int input_count = sizeof(input_ranges) / sizeof(input_ranges[0]);
    int start_range = 2;
    int end_range = 20;

    RangeList missing = find_missing_ranges(input_ranges, input_count, start_range, end_range);

    printf("Missing ranges from %d to %d:\n", start_range, end_range);
    for (int i = 0; i < missing.count; i++) {
        printf("[%d, %d]\n", missing.ranges[i].start, missing.ranges[i].end);
    }

    free_range_list(&missing);

    return 0;
}