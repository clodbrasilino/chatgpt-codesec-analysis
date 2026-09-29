#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int id;
    int value;
} Record;

typedef struct {
    int num_records;
    Record *records;
} Tuple;

int find_max_value(Tuple t) {
    if (t.num_records == 0 || t.records == NULL) {
        return INT_MIN;
    }
    int max_val = t.records[0].value;
    for (int i = 1; i < t.num_records; ++i) {
        if (t.records[i].value > max_val) {
            max_val = t.records[i].value;
        }
    }
    return max_val;
}

int main() {
    int n;
    scanf("%d", &n);
    Tuple t = { .num_records = n, .records = (Record*)malloc(n * sizeof(Record)) };
    for (int i = 0; i < n; ++i) {
        scanf("%d %d", &t.records[i].id, &t.records[i].value);
    }
    int max_value = find_max_value(t);
    printf("%d\n", max_value);
    free(t.records);
    return 0;
}