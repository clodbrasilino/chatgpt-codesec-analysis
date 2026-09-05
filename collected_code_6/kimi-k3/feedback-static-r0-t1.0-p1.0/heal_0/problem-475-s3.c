#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    int count;
} Counter;

int compare_counters(const void *a, const void *b) {
    const Counter *ca = (const Counter *)a;
    const Counter *cb = (const Counter *)b;
    if (ca->count < cb->count) {
        return -1;
    }
    if (ca->count > cb->count) {
        return 1;
    }
    return 0;
}

int sort_counter_by_value(Counter *counters, size_t size) {
    if (counters == NULL) {
        return -1;
    }
    qsort(counters, size, sizeof(Counter), compare_counters);
    return 0;
}

int main(void) {
    Counter counters[] = {
        {1, 5},
        {2, 3},
        {3, 8},
        {4, 1},
        {5, 6}
    };
    size_t size = sizeof(counters) / sizeof(counters[0]);
    size_t i;

    if (sort_counter_by_value(counters, size) != 0) {
        return EXIT_FAILURE;
    }

    for (i = 0; i < size; ++i) {
        printf("Value: %d, Count: %d\n", counters[i].value, counters[i].count);
    }

    return EXIT_SUCCESS;
}