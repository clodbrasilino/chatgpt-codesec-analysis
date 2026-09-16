#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char key[64];
    int value;
} Counter;

int compare_counters(const void *a, const void *b) {
    const Counter *ca = (const Counter *)a;
    const Counter *cb = (const Counter *)b;
    return (ca->value > cb->value) - (ca->value < cb->value);
}

int sort_counter_by_value(Counter *counters, size_t count) {
    if (counters == NULL || count == 0) {
        return -1;
    }
    qsort(counters, count, sizeof(Counter), compare_counters);
    return 0;
}

int main(void) {
    Counter counters[] = {
        {"apple", 5},
        {"banana", 2},
        {"cherry", 9},
        {"date", 1},
        {"elderberry", 7}
    };
    size_t count = sizeof(counters) / sizeof(counters[0]);

    if (sort_counter_by_value(counters, count) != 0) {
        fprintf(stderr, "Error: failed to sort counters\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; i++) {
        printf("%s: %d\n", counters[i].key, counters[i].value);
    }

    return EXIT_SUCCESS;
}