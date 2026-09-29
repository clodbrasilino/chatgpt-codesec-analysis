#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int start;
    int end;
} Range;

int compare_ranges(const void *a, const void *b) {
    const Range *ra = (const Range *)a;
    const Range *rb = (const Range *)b;
    if (ra->start < rb->start) return -1;
    if (ra->start > rb->start) return 1;
    if (ra->end < rb->end) return -1;
    if (ra->end > rb->end) return 1;
    return 0;
}

Range* get_missing_ranges(const Range *input_ranges, size_t num_ranges, int bound_start, int bound_end, size_t *out_num_missing) {
    if (!out_num_missing) {
        return NULL;
    }
    
    *out_num_missing = 0;
    
    if (bound_start > bound_end) {
        return NULL;
    }

    Range *sorted_ranges = NULL;
    if (num_ranges > 0 && input_ranges) {
        sorted_ranges = malloc(num_ranges * sizeof(Range));
        if (!sorted_ranges) {
            return NULL;
        }
        for (size_t i = 0; i < num_ranges; i++) {
            sorted_ranges[i] = input_ranges[i];
        }
        qsort(sorted_ranges, num_ranges, sizeof(Range), compare_ranges);
    }

    size_t max_missing = num_ranges + 1;
    Range *missing = malloc(max_missing * sizeof(Range));
    if (!missing) {
        free(sorted_ranges);
        return NULL;
    }

    int current = bound_start;
    size_t missing_count = 0;
    int end_reached = 0;

    for (size_t i = 0; i < num_ranges; i++) {
        if (sorted_ranges[i].end < current) {
            continue;
        }
        
        if (sorted_ranges[i].start > current) {
            int end_missing = (sorted_ranges[i].start - 1 < bound_end) ? sorted_ranges[i].start - 1 : bound_end;
            if (current <= end_missing) {
                missing[missing_count].start = current;
                missing[missing_count].end = end_missing;
                missing_count++;
            }
        }
        
        if (sorted_ranges[i].end >= bound_end) {
            end_reached = 1;
            break;
        }
        
        if (sorted_ranges[i].end == INT_MAX) {
            end_reached = 1;
            break;
        }
        
        current = sorted_ranges[i].end + 1;
    }

    if (!end_reached && current <= bound_end) {
        missing[missing_count].start = current;
        missing[missing_count].end = bound_end;
        missing_count++;
    }

    free(sorted_ranges);

    if (missing_count == 0) {
        free(missing);
        return NULL;
    }

    Range *resized_missing = realloc(missing, missing_count * sizeof(Range));
    if (resized_missing) {
        missing = resized_missing;
    }

    *out_num_missing = missing_count;
    return missing;
}

int main(void) {
    Range input[] = {
        {2, 3},
        {7, 10},
        {15, 20}
    };
    size_t num_input = sizeof(input) / sizeof(input[0]);
    int bound_start = 1;
    int bound_end = 25;
    size_t num_missing = 0;
    
    Range *missing = get_missing_ranges(input, num_input, bound_start, bound_end, &num_missing);

    if (missing) {
        for (size_t i = 0; i < num_missing; i++) {
            printf("[%d, %d]\n", missing[i].start, missing[i].end);
        }
        free(missing);
    } else if (num_missing == 0) {
        printf("No missing ranges.\n");
    } else {
        printf("Error processing ranges.\n");
    }

    return 0;
}