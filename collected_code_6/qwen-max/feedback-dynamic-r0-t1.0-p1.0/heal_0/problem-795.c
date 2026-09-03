#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int price;
    int index;
} Item;

int compare(const void *a, const void *b) {
    return ((Item *)a)->price - ((Item *)b)->price;
}

void find_n_cheapest(Item *items, int size, int n) {
    qsort(items, size, sizeof(Item), compare);
    for (int i = 0; i < n && i < size; i++) {
        printf("Price: %d, Index: %d\n", items[i].price, items[i].index);
    }
}

int main() {
    int prices[] = {100, 50, 20, 90, 10, 60, 30};
    int n = 5;
    int size = sizeof(prices) / sizeof(prices[0]);
    Item *items = (Item *)malloc(size * sizeof(Item));
    if (items == NULL) {
        return 1;
    }
    for (int i = 0; i < size; i++) {
        items[i].price = prices[i];
        items[i].index = i;
    }
    find_n_cheapest(items, size, n);
    free(items);
    return 0;
}