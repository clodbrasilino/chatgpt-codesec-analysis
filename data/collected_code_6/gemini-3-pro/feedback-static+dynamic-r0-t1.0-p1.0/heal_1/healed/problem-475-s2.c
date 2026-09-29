#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    int value;
} CounterItem;

int compare_items(const void *a, const void *b) {
    const CounterItem *itemA = (const CounterItem *)a;
    const CounterItem *itemB = (const CounterItem *)b;
    return itemA->value - itemB->value;
}

void sort_counter(CounterItem *counter, size_t size) {
    if (counter == NULL || size == 0) {
        return;
    }
    qsort(counter, size, sizeof(CounterItem), compare_items);
}

int main(void) {
    size_t size = 4;
    CounterItem *counter = (CounterItem *)malloc(size * sizeof(CounterItem));
    
    if (counter == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    counter[0].key = strdup("apple");
    counter[0].value = 5;
    
    counter[1].key = strdup("banana");
    counter[1].value = 2;
    
    counter[2].key = strdup("cherry");
    counter[2].value = 8;
    
    counter[3].key = strdup("date");
    counter[3].value = 1;

    for (size_t i = 0; i < size; i++) {
        if (counter[i].key == NULL) {
            fprintf(stderr, "Memory allocation failed for key\n");
            for (size_t j = 0; j < i; j++) {
                free(counter[j].key);
            }
            free(counter);
            return 1;
        }
    }

    sort_counter(counter, size);

    for (size_t i = 0; i < size; i++) {
        printf("%s: %d\n", counter[i].key, counter[i].value);
    }

    for (size_t i = 0; i < size; i++) {
        free(counter[i].key);
    }
    free(counter);

    return 0;
}