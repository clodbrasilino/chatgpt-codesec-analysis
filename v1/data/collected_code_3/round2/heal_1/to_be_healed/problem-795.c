#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int price;
    int id;
} Item;

typedef struct {
    Item* items;
    int len;
    int size;
} Heap;

Heap* createHeap(int size) {
    Heap* h = (Heap*)malloc(sizeof(Heap));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'h' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    h->items = (Item*)malloc(sizeof(Item) * size);
    h->len = 0;
    h->size = size;
    return h;
}

void push(Heap* h, Item item) {
    if (h->len == h->size) {
        /* Possible weaknesses found:
         *  leak of '<unknown>' [CWE-401] [-Wanalyzer-malloc-leak]
         */
        h->items = (Item*)realloc(h->items, sizeof(Item) * h->size * 2);
        h->size *= 2;
    }
    /* Possible weaknesses found:
     *  dereference of possibly-NULL '*h.items + (long unsigned int)*h.len * 8' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    h->items[h->len] = item;
    int i = h->len;
    while (i > 0) {
        int p = (i - 1) / 2;
        if (h->items[p].price <= h->items[i].price) break;
        Item temp = h->items[i];
        h->items[i] = h->items[p];
        h->items[p] = temp;
        i = p;
    }
    h->len++;
}

Item pop(Heap* h) {
    Item ret = h->items[0];
    h->len--;
    h->items[0] = h->items[h->len];
    int i = 0;
    while (i * 2 + 1 < h->len) {
        int child;
        if (i * 2 + 2 == h->len) {
            child = i * 2 + 1;
        } else {
            child = h->items[i * 2 + 1].price < h->items[i * 2 + 2].price ? i * 2 + 1 : i * 2 + 2;
        }
        if (h->items[child].price >= h->items[i].price) break;
        Item temp = h->items[i];
        h->items[i] = h->items[child];
        h->items[child] = temp;
        i = child;
    }
    return ret;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    Heap* h = createHeap(n);
    for (int i = 0; i < n; i++) {
        int price;
        scanf("%d", &price);
        push(h, (Item){price, i + 1});
        if (h->len > m) {
            pop(h);
        }
    }
    Item* result = (Item*)malloc(sizeof(Item) * m);
    for (int i = 0; i < m; i++) {
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'result' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        result[i] = pop(h);
    }
    for (int i = m - 1; i >= 0; i--) {
        printf("%d %d\n", result[i].id, result[i].price);
    }
    free(result);
    free(h->items);
    free(h);
    return 0;
}