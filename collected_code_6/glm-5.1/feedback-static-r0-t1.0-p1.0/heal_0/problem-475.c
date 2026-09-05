#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
    int value;
} Counter;

int compare_counters(const void *a, const void *b) {
    const Counter *ca = (const Counter *)a;
    const Counter *cb = (const Counter *)b;
    if (ca->value < cb->value) return -1;
    if (ca->value > cb->value) return 1;
    return 0;
}

void sort_counters(Counter *counters, size_t count) {
    if (counters == NULL || count == 0) {
        return;
    }
    qsort(counters, count, sizeof(Counter), compare_counters);
}

int main(void) {
    Counter counters[] = {
        {1, 5},
        {2, 2},
        {3, 8},
        {4, 1},
        {5, 9}
    };
    size_t count = sizeof(counters) / sizeof(counters[0]);

    sort_counters(counters, count);

    for (size_t i = 0; i < count; i++) {
        printf("Key: %d, Value: %d\n", counters[i].key, counters[i].value);
    }

    return 0;
}