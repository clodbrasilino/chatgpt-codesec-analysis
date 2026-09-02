#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *key;
    int value;
} CounterItem;

int compare_counter_items(const void *a, const void *b) {
    const CounterItem *item_a = (const CounterItem *)a;
    const CounterItem *item_b = (const CounterItem *)b;
    return item_b->value - item_a->value;
}

void sort_counter_by_value(CounterItem *counter, size_t size) {
    if (counter == NULL || size == 0 || size == 1) {
        return;
    }
    qsort(counter, size, sizeof(CounterItem), compare_counter_items);
}

int main(void) {
    CounterItem counter[] = {
        {"apple", 5},
        {"banana", 2},
        {"cherry", 8},
        {"date", 3},
        {"elderberry", 1}
    };
    size_t size = sizeof(counter) / sizeof(counter[0]);

    sort_counter_by_value(counter, size);

    for (size_t i = 0; i < size; i++) {
        printf("%s: %d\n", counter[i].key, counter[i].value);
    }

    return 0;
}