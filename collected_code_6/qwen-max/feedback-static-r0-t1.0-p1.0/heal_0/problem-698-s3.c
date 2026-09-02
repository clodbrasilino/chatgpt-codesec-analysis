#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int first;
    int second;
} Tuple;

typedef struct {
    Tuple key;
    char *value;
} DictionaryItem;

int compare(const void *a, const void *b) {
    DictionaryItem *itemA = (DictionaryItem *)a;
    DictionaryItem *itemB = (DictionaryItem *)b;
    int productA = itemA->key.first * itemA->key.second;
    int productB = itemB->key.first * itemB->key.second;
    return (productA > productB) - (productA < productB);
}

void sortDictionary(DictionaryItem *items, size_t count) {
    qsort(items, count, sizeof(DictionaryItem), compare);
}

int main() {
    DictionaryItem items[] = {
        {{2, 5}, "apple"},
        {{3, 3}, "banana"},
        {{1, 10}, "cherry"},
        {{4, 4}, "date"},
        {{5, 2}, "fig"}
    };
    size_t count = sizeof(items) / sizeof(items[0]);

    sortDictionary(items, count);

    for (size_t i = 0; i < count; ++i) {
        printf("(%d, %d): %s\n", items[i].key.first, items[i].key.second, items[i].value);
    }

    return 0;
}