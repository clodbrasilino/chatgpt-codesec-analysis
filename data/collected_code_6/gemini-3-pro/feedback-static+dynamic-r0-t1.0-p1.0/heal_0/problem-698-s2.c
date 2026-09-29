#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key1;
    int key2;
} TupleKey;

typedef struct {
    TupleKey key;
    char* value;
} DictionaryItem;

int compare_items(const void* a, const void* b) {
    const DictionaryItem* itemA = (const DictionaryItem*)a;
    const DictionaryItem* itemB = (const DictionaryItem*)b;
    
    long long prodA = (long long)itemA->key.key1 * itemA->key.key2;
    long long prodB = (long long)itemB->key.key1 * itemB->key.key2;
    
    if (prodA < prodB) return -1;
    if (prodA > prodB) return 1;
    return 0;
}

void sort_dictionary(DictionaryItem* dict, size_t size) {
    if (dict == NULL || size <= 1) {
        return;
    }
    qsort(dict, size, sizeof(DictionaryItem), compare_items);
}

int main() {
    DictionaryItem dict[] = {
        {{3, 4}, "Three Four"},
        {{1, 2}, "One Two"},
        {{5, 6}, "Five Six"},
        {{2, 2}, "Two Two"},
        {{-1, 10}, "Minus One Ten"}
    };
    
    size_t size = sizeof(dict) / sizeof(dict[0]);
    
    sort_dictionary(dict, size);
    
    for (size_t i = 0; i < size; ++i) {
        printf("Key: (%d, %d), Product: %lld, Value: %s\n", 
               dict[i].key.key1, dict[i].key.key2, 
               (long long)dict[i].key.key1 * dict[i].key.key2, 
               dict[i].value);
    }
    
    return 0;
}