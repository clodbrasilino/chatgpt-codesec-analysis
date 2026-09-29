#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int start;
    int end;
} Range;

bool is_within_range(int value, Range *range) {
    return (value >= range->start && value <= range->end);
}

void insert_sorted(Range **ranges, int *size, Range new_range) {
    int i = 0;
    for (; i < *size; ++i) {
        if (new_range.start < (*ranges)[i].start) {
            break;
        }
    }
    for (int j = *size; j > i; --j) {
        (*ranges)[j] = (*ranges)[j - 1];
    }
    (*ranges)[i] = new_range;
    (*size)++;
}

Range *extract_missing_ranges(Range *list, int list_size, Range full_range, int *out_size) {
    int last_value = full_range.start - 1;
    *out_size = 0;
    Range *missing_ranges = NULL;

    for (int i = 0; i < list_size; ++i) {
        if (list[i].start > last_value + 1) {
            Range missing = {last_value + 1, list[i].start - 1};
            insert_sorted(&missing_ranges, out_size, missing);
        }
        last_value = list[i].end;
    }

    if (full_range.end > last_value) {
        Range missing = {last_value + 1, full_range.end};
        insert_sorted(&missing_ranges, out_size, missing);
    }

    return missing_ranges;
}

void print_ranges(Range *ranges, int size) {
    for (int i = 0; i < size; ++i) {
        printf("%d-%d ", ranges[i].start, ranges[i].end);
    }
    printf("\n");
}

int main() {
    Range list[] = {{5, 10}, {20, 25}, {30, 35}};
    int list_size = sizeof(list) / sizeof(list[0]);
    Range full_range = {1, 40};
    int out_size;

    Range *missing_ranges = extract_missing_ranges(list, list_size, full_range, &out_size);

    print_ranges(missing_ranges, out_size);

    free(missing_ranges);

    return 0;
}