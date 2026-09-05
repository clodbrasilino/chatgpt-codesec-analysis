#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int key[2];
    int value;
} DictItem;

int compare(const void *a, const void *b) {
    const DictItem *ia = (const DictItem *)a;
    const DictItem *ib = (const DictItem *)b;
    long prod_a = (long)ia->key[0] * ia->key[1];
    long prod_b = (long)ib->key[0] * ib->key[1];
    if (prod_a < prod_b) return -1;
    if (prod_a > prod_b) return 1;
    return 0;
}

void sort_dict(DictItem *items, size_t n) {
    if (items == NULL || n == 0) return;
    qsort(items, n, sizeof(DictItem), compare);
}

int main(void) {
    DictItem items[] = {
        {{3, 4}, 100},
        {{1, 10}, 200},
        {{2, 2}, 300},
        {{5, 1}, 400}
    };
    size_t n = sizeof(items) / sizeof(items[0]);

    sort_dict(items, n);

    for (size_t i = 0; i < n; i++) {
        printf("(%d, %d) : %d\n", items[i].key[0], items[i].key[1], items[i].value);
    }

    return 0;
}