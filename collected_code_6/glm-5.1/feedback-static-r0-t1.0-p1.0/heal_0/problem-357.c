#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} TupleRecord;

int find_max_element(TupleRecord *records, size_t count) {
    if (records == NULL || count == 0) {
        return 0;
    }

    int max_val = records[0].a;
    if (records[0].b > max_val) {
        max_val = records[0].b;
    }

    for (size_t i = 1; i < count; i++) {
        if (records[i].a > max_val) {
            max_val = records[i].a;
        }
        if (records[i].b > max_val) {
            max_val = records[i].b;
        }
    }

    return max_val;
}

int main(void) {
    TupleRecord records[] = {{3, 7}, {15, 2}, {8, 9}, {4, 5}};
    size_t count = sizeof(records) / sizeof(records[0]);

    int max = find_max_element(records, count);

    printf("%d\n", max);

    return 0;
}