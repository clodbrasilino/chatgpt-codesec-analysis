#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int start;
    int end;
} Range;

typedef struct {
    Range *ranges;
    size_t count;
    size_t capacity;
} RangeList;

int compare_ranges(const void *a, const void *b);
int add_range(RangeList *list, int start, int end);
void free_rangelist(RangeList *list);
RangeList extract_missing_ranges(const Range *input, size_t input_count, int start_range, int end_range);

int compare_ranges(const void *a, const void *b) {
    const Range *ra = (const Range *)a;
    const Range *rb = (const Range *)b;
    if (ra->start < rb->start) {
        return -1;
    }
    if (ra->start > rb->start) {
        return 1;
    }
    return 0;
}

int add_range(RangeList *list, int start, int end) {
    if (!list) {
        return -1;
    }
    if (list->count >= list->capacity) {
        size_t new_cap = list->capacity == 0 ? 4 : list->capacity * 2;
        Range *new_arr = realloc(list->ranges, new_cap * sizeof(Range));
        if (!new_arr) {
            return -1;
        }
        list->ranges = new_arr;
        list->capacity = new_cap;
    }
    list->ranges[list->count].start = start;
    list->ranges[list->count].end = end;
    list->count++;
    return 0;
}

void free_rangelist(RangeList *list) {
    if (list && list->ranges) {
        free(list->ranges);
        list->ranges = NULL;
        list->count = 0;
        list->capacity = 0;
    }
}

RangeList extract_missing_ranges(const Range *input, size_t input_count, int start_range, int end_range) {
    RangeList missing = {NULL, 0, 0};

    if (start_range > end_range) {
        return missing;
    }

    if (input_count == 0) {
        if (add_range(&missing, start_range, end_range) != 0) {
            free_rangelist(&missing);
        }
        return missing;
    }

    Range *sorted_input = malloc(input_count * sizeof(Range));
    if (!sorted_input) {
        return missing;
    }

    for (size_t i = 0; i < input_count; i++) {
        sorted_input[i] = input[i];
    }

    qsort(sorted_input, input_count, sizeof(Range), compare_ranges);

    long long current = (long long)start_range;

    for (size_t i = 0; i < input_count; i++) {
        if (current > (long long)end_range) {
            break;
        }
        if (sorted_input[i].end < current) {
            continue;
        }
        if (sorted_input[i].start > current) {
            long long gap_end = (long long)sorted_input[i].start - 1;
            if (gap_end > (long long)end_range) {
                gap_end = (long long)end_range;
            }
            if (add_range(&missing, (int)current, (int)gap_end) != 0) {
                free(sorted_input);
                free_rangelist(&missing);
                return missing;
            }
        }
        if (sorted_input[i].end >= current) {
            current = (long long)sorted_input[i].end + 1;
        }
    }

    if (current <= (long long)end_range) {
        if (add_range(&missing, (int)current, end_range) != 0) {
            free(sorted_input);
            free_rangelist(&missing);
            return missing;
        }
    }

    free(sorted_input);
    return missing;
}

int main(void) {
    Range input[] = {
        {10, 15},
        {20, 25},
        {22, 28},
        {40, 50}
    };
    size_t input_count = sizeof(input) / sizeof(input[0]);
    int start_range = 5;
    int end_range = 45;

    RangeList missing = extract_missing_ranges(input, input_count, start_range, end_range);

    if (!missing.ranges && missing.capacity > 0) {
        fprintf(stderr, "Memory allocation failure.\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < missing.count; i++) {
        printf("[%d, %d]\n", missing.ranges[i].start, missing.ranges[i].end);
    }

    free_rangelist(&missing);

    return EXIT_SUCCESS;
}