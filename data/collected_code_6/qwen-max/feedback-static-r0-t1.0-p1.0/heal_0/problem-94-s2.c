#include <stdio.h>
#include <limits.h>

typedef struct {
    int index;
    int value;
} Record;

Record find_min_index(const Record *records, int n) {
    Record min = {0, INT_MAX};
    for (int i = 0; i < n; i++) {
        if (records[i].value < min.value) {
            min = records[i];
        }
    }
    return min;
}

int main() {
    Record data[] = {{0, 10}, {1, 5}, {2, 15}, {3, 3}};
    int n = sizeof(data) / sizeof(data[0]);
    Record min_record = find_min_index(data, n);
    printf("Min index: %d, Min value: %d\n", min_record.index, min_record.value);
    return 0;
}