#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
    int value;
} Counter;

int compare(const void *a, const void *b) {
    const Counter *counterA = a;
    const Counter *counterB = b;
    return (counterB->value - counterA->value);
}

void sort_counter(Counter *arr, size_t n) {
    qsort(arr, n, sizeof(Counter), compare);
}

int main() {
    Counter counters[] = {{1, 3}, {2, 1}, {3, 4}, {4, 2}};
    size_t n = sizeof(counters) / sizeof(counters[0]);

    sort_counter(counters, n);

    for (size_t i = 0; i < n; i++) {
        printf("%d: %d\n", counters[i].key, counters[i].value);
    }

    return 0;
}