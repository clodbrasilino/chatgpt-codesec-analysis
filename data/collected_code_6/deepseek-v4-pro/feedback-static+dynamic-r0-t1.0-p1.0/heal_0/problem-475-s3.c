#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *key;
    int value;
} CounterItem;

typedef struct {
    CounterItem *items;
    size_t size;
    size_t capacity;
} Counter;

static int compare_counter_items(const void *a, const void *b) {
    const CounterItem *item_a = (const CounterItem *)a;
    const CounterItem *item_b = (const CounterItem *)b;
    
    if (item_a->value < item_b->value) return 1;
    if (item_a->value > item_b->value) return -1;
    return 0;
}

void sort_counter_by_value(Counter *counter) {
    if (counter == NULL || counter->items == NULL || counter->size <= 1) {
        return;
    }
    
    qsort(counter->items, counter->size, sizeof(CounterItem), compare_counter_items);
}

int init_counter(Counter *counter, size_t initial_capacity) {
    if (counter == NULL || initial_capacity == 0) {
        return 0;
    }
    
    counter->items = (CounterItem *)malloc(initial_capacity * sizeof(CounterItem));
    if (counter->items == NULL) {
        return 0;
    }
    
    counter->size = 0;
    counter->capacity = initial_capacity;
    return 1;
}

void free_counter(Counter *counter) {
    if (counter == NULL) {
        return;
    }
    
    if (counter->items != NULL) {
        free(counter->items);
        counter->items = NULL;
    }
    
    counter->size = 0;
    counter->capacity = 0;
}

int add_counter_item(Counter *counter, const char *key, int value) {
    if (counter == NULL || counter->items == NULL || key == NULL) {
        return 0;
    }
    
    if (counter->size >= counter->capacity) {
        size_t new_capacity = counter->capacity * 2;
        CounterItem *new_items = (CounterItem *)realloc(counter->items, new_capacity * sizeof(CounterItem));
        if (new_items == NULL) {
            return 0;
        }
        counter->items = new_items;
        counter->capacity = new_capacity;
    }
    
    counter->items[counter->size].key = (char *)key;
    counter->items[counter->size].value = value;
    counter->size++;
    
    return 1;
}

void print_counter(const Counter *counter) {
    if (counter == NULL || counter->items == NULL) {
        return;
    }
    
    for (size_t i = 0; i < counter->size; i++) {
        printf("%s: %d\n", counter->items[i].key, counter->items[i].value);
    }
}

int main(void) {
    Counter counter;
    
    if (!init_counter(&counter, 4)) {
        return 1;
    }
    
    if (!add_counter_item(&counter, "apple", 5) ||
        !add_counter_item(&counter, "banana", 2) ||
        !add_counter_item(&counter, "cherry", 8) ||
        !add_counter_item(&counter, "date", 3) ||
        !add_counter_item(&counter, "elderberry", 1)) {
        free_counter(&counter);
        return 1;
    }
    
    printf("Before sorting:\n");
    print_counter(&counter);
    
    sort_counter_by_value(&counter);
    
    printf("\nAfter sorting by value (descending):\n");
    print_counter(&counter);
    
    free_counter(&counter);
    
    return 0;
}