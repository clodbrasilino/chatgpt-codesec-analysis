#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
    int value;
} DictItem;

int compare_items(const void *x, const void *y) {
    const DictItem *item_x = (const DictItem *)x;
    const DictItem *item_y = (const DictItem *)y;
    int product_x = item_x->a * item_x->b;
    int product_y = item_y->a * item_y->b;
    if (product_x < product_y) return -1;
    if (product_x > product_y) return 1;
    return 0;
}

void sort_dictionary_by_key_product(DictItem *items, int count) {
    if (items == NULL || count <= 0) {
        return;
    }
    qsort(items, count, sizeof(DictItem), compare_items);
}

int main(void) {
    DictItem items[] = {
        {3, 4, 100},
        {1, 5, 200},
        {2, 2, 300},
        {0, 7, 400},
        {6, 1, 500}
    };
    int count = sizeof(items) / sizeof(items[0]);
    int i;

    sort_dictionary_by_key_product(items, count);

    for (i = 0; i < count; i++) {
        printf("(%d, %d): %d\n", items[i].a, items[i].b, items[i].value);
    }

    return 0;
}