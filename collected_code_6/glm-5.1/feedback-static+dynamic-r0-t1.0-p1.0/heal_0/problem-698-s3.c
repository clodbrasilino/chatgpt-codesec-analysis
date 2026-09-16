#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key1;
    int key2;
    int value;
} DictionaryItem;

int compare_items(const void *a, const void *b) {
    const DictionaryItem *item_a = (const DictionaryItem *)a;
    const DictionaryItem *item_b = (const DictionaryItem *)b;
    
    long long product_a = (long long)item_a->key1 * (long long)item_a->key2;
    long long product_b = (long long)item_b->key1 * (long long)item_b->key2;

    if (product_a < product_b) {
        return -1;
    }
    if (product_a > product_b) {
        return 1;
    }
    return 0;
}

void sort_dictionary_by_tuple_product(DictionaryItem *items, size_t count) {
    if (items == NULL || count == 0) {
        return;
    }
    qsort(items, count, sizeof(DictionaryItem), compare_items);
}

int main(void) {
    DictionaryItem dictionary[] = {
        {3, 4, 10},
        {1, 2, 20},
        {5, -1, 30},
        {2, 2, 40},
        {0, 10, 50}
    };
    
    size_t count = sizeof(dictionary) / sizeof(dictionary[0]);
    
    sort_dictionary_by_tuple_product(dictionary, count);
    
    for (size_t i = 0; i < count; i++) {
        printf("Key: (%d, %d), Product: %d, Value: %d\n", 
               dictionary[i].key1, 
               dictionary[i].key2, 
               dictionary[i].key1 * dictionary[i].key2, 
               dictionary[i].value);
    }
    
    return 0;
}