#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    int value;
} Record;

int findMaxValue(Record *list, size_t length) {
    if (length == 0) return -1;
    int max = list[0].value;
    for (size_t i = 1; i < length; ++i) {
        if (list[i].value > max) {
            max = list[i].value;
        }
    }
    return max;
}

int main() {
    Record records[] = {{1, 10}, {2, 20}, {3, 15}};
    size_t num_records = sizeof(records) / sizeof(records[0]);
    int max_value = findMaxValue(records, num_records);
    printf("Maximum value: %d\n", max_value);
    return 0;
}