#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key1;
    int key2;
    int value;
} DictItem;

int compare(const void *a, const void *b) {
    DictItem *itemA = (DictItem *)a;
    DictItem *itemB = (DictItem *)b;
    return (itemA->key1 * itemA->key2) - (itemB->key1 * itemB->key2);
}

void sortDictItems(DictItem *items, int size) {
    qsort(items, size, sizeof(DictItem), compare);
}

int main() {
    DictItem items[] = {
        {2, 3, 10},
        {1, 5, 20},
        {4, 1, 30},
        {3, 2, 40}
    };
    int size = sizeof(items) / sizeof(DictItem);

    sortDictItems(items, size);

    for(int i = 0; i < size; i++) {
        printf("Key1: %d, Key2: %d, Value: %d\n", items[i].key1, items[i].key2, items[i].value);
    }

    return 0;
}