#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int element;
    int count;
} Item;

void iterate_repeating(Item *items, size_t num_items) {
    if (items == NULL) {
        return;
    }
    for (size_t i = 0; i < num_items; i++) {
        if (items[i].count < 0) {
            continue;
        }
        for (int j = 0; j < items[i].count; j++) {
            printf("%d\n", items[i].element);
        }
    }
}

int main(void) {
    Item items[] = {
        {1, 3},
        {2, 0},
        {3, 2},
        {4, -1}
    };
    size_t num_items = sizeof(items) / sizeof(items[0]);
    iterate_repeating(items, num_items);
    return 0;
}