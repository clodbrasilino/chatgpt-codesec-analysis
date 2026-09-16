#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key1;
    int key2;
    int value;
} DictItem;

int compare_items(const void *a, const void *b) {
    const DictItem *item_a = (const DictItem *)a;
    const DictItem *item_b = (const DictItem *)b;
    long prod_a = (long)item_a->key1 * item_a->key2;
    long prod_b = (long)item_b->key1 * item_b->key2;
    if (prod_a < prod_b) return -1;
    if (prod_a > prod_b) return 1;
    return 0;
}

void sort_dictionary(DictItem *items, size_t count) {
    if (items == NULL || count == 0) {
        return;
    }
    qsort(items, count, sizeof(DictItem), compare_items);
}

int main(void) {
    DictItem dictionary[] = {
        {5, 6, 10},
        {2, 3, 20},
        {4, -1, 30},
        {1, 1, 40},
        {0, 9, 50},
        {-2, 3, 60}
    };
    size_t count = sizeof(dictionary) / sizeof(dictionary[0]);

    sort_dictionary(dictionary, count);

    for (size_t i = 0; i < count; i++) {
        printf("(%d, %d): %d\n", dictionary[i].key1, dictionary[i].key2, dictionary[i].value);
    }

    return 0;
}