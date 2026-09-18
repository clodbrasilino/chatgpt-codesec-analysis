#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int start;
    int end;
} Range;

void find_missing_ranges(int* arr, int size, int start_range, int end_range, Range** missing_ranges, int* missing_count) {
    if (arr == NULL || missing_ranges == NULL || missing_count == NULL) {
        return;
    }

    int capacity = 10;
    *missing_ranges = (Range*)malloc(capacity * sizeof(Range));
    if (*missing_ranges == NULL) {
        *missing_count = 0;
        return;
    }

    *missing_count = 0;
    int current = start_range;

    for (int i = 0; i < size; i++) {
        if (arr[i] > current) {
            if (*missing_count >= capacity) {
                capacity *= 2;
                Range* temp = (Range*)realloc(*missing_ranges, capacity * sizeof(Range));
                if (temp == NULL) {
                    free(*missing_ranges);
                    *missing_ranges = NULL;
                    *missing_count = 0;
                    return;
                }
                *missing_ranges = temp;
            }
            (*missing_ranges)[*missing_count].start = current;
            (*missing_ranges)[*missing_count].end = arr[i] - 1;
            (*missing_count)++;
        }
        if (arr[i] >= current) {
            current = arr[i] + 1;
        }
    }

    if (current <= end_range) {
        if (*missing_count >= capacity) {
            capacity += 1;
            Range* temp = (Range*)realloc(*missing_ranges, capacity * sizeof(Range));
            if (temp == NULL) {
                free(*missing_ranges);
                *missing_ranges = NULL;
                *missing_count = 0;
                return;
            }
            *missing_ranges = temp;
        }
        (*missing_ranges)[*missing_count].start = current;
        (*missing_ranges)[*missing_count].end = end_range;
        (*missing_count)++;
    }
}

int main() {
    int arr[] = {3, 5, 10, 11, 15};
    int size = sizeof(arr) / sizeof(arr[0]);
    int start_range = 0;
    int end_range = 20;

    Range* missing_ranges = NULL;
    int missing_count = 0;

    find_missing_ranges(arr, size, start_range, end_range, &missing_ranges, &missing_count);

    if (missing_ranges != NULL) {
        for (int i = 0; i < missing_count; i++) {
            if (missing_ranges[i].start == missing_ranges[i].end) {
                printf("%d\n", missing_ranges[i].start);
            } else {
                printf("%d->%d\n", missing_ranges[i].start, missing_ranges[i].end);
            }
        }
        free(missing_ranges);
    }

    return 0;
}