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

static void merge_ranges(Range *ranges, int *count) {
    if (*count <= 1) {
        return;
    }
    
    qsort(ranges, *count, sizeof(Range), compare_ranges);
    
    int write_index = 0;
    for (int read_index = 1; read_index < *count; read_index++) {
        if (ranges[read_index].start <= ranges[write_index].end) {
            if (ranges[read_index].end > ranges[write_index].end) {
                ranges[write_index].end = ranges[read_index].end;
            }
        } else {
            write_index++;
            ranges[write_index] = ranges[read_index];
        }
    }
    *count = write_index + 1;
}

static int add_range(RangeList *list, int start, int end) {
    if (list->count >= list->capacity) {
        int new_capacity = list->capacity == 0 ? 8 : list->capacity * 2;
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

RangeList find_missing_ranges(const Range *ranges, int count, int start_range, int end_range) {
    RangeList missing;
    missing.ranges = NULL;
    missing.count = 0;
    missing.capacity = 0;
    
    if (start_range > end_range) {
        return missing;
    }
    
    if (count == 0) {
        if (!add_range(&missing, start_range, end_range)) {
            free_range_list(&missing);
        }
        return missing;
    }
    
    Range *sorted_ranges = (Range *)malloc(count * sizeof(Range));
    if (sorted_ranges == NULL) {
        return missing;
    }
    
    for (int i = 0; i < count; i++) {
        sorted_ranges[i] = ranges[i];
    }
    
    int sorted_count = count;
    merge_ranges(sorted_ranges, &sorted_count);
    
    int current = start_range;
    
    for (int i = 0; i < sorted_count; i++) {
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
            if (!add_range(&missing, current, missing_end)) {
                free(sorted_ranges);
                free_range_list(&missing);
                return missing;
            }
        }
        
        if (sorted_ranges[i].end >= end_range) {
            current = end_range + 1;
            break;
        }
        
        current = sorted_ranges[i].end + 1;
    }
    
    if (current <= end_range) {
        if (!add_range(&missing, current, end_range)) {
            free(sorted_ranges);
            free_range_list(&missing);
            return missing;
        }
    }
    
    free(sorted_ranges);
    return missing;
}

int main(void) {
    Range input_ranges[] = {
        {2, 5},
        {8, 10},
        {15, 20},
        {25, 30}
    };
    int input_count = sizeof(input_ranges) / sizeof(input_ranges[0]);
    
    int start_range = 1;
    int end_range = 35;
    
    RangeList missing = find_missing_ranges(input_ranges, input_count, start_range, end_range);
    
    printf("Missing ranges between %d and %d:\n", start_range, end_range);
    for (int i = 0; i < missing.count; i++) {
        printf("[%d, %d]\n", missing.ranges[i].start, missing.ranges[i].end);
    }
    
    free_range_list(&missing);
    
    return 0;
}