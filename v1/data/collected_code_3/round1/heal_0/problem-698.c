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

void sortDictItems(DictItem *items, int itemCount) {
    qsort(items, itemCount, sizeof(DictItem), compare);
}

int main() {
    DictItem items[] = {
        {2, 3, 10},
        {1, 4, 20},
        {3, 2, 30},
        {4, 1, 40}
    };
    int itemCount = sizeof(items) / sizeof(DictItem);

    sortDictItems(items, itemCount);

    for(int i = 0; i < itemCount; i++) {
        printf("Key1: %d, Key2: %d, Value: %d\n", items[i].key1, items[i].key2, items[i].value);
    }

    return 0;
}