#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int price;
    int index;
} Item;

int compare(const void *a, const void *b) {
    return ((Item *)a)->price - ((Item *)b)->price;
}

void find_n_cheapest_items(Item *items, int size, int n, Item *result) {
    qsort(items, size, sizeof(Item), compare);
    for (int i = 0; i < n; ++i) {
        result[i] = items[i];
    }
}

int main() {
    int prices[] = {10, 5, 8, 3, 6, 2, 7};
    int n = 4;
    int size = sizeof(prices) / sizeof(prices[0]);

    Item *items = (Item *)malloc(size * sizeof(Item));
    Item *result = (Item *)malloc(n * sizeof(Item));

    for (int i = 0; i < size; ++i) {
        items[i].price = prices[i];
        items[i].index = i;
    }

    find_n_cheapest_items(items, size, n, result);

    for (int i = 0; i < n; ++i) {
        printf("Price: %d, Index: %d\n", result[i].price, result[i].index);
    }

    free(items);
    free(result);

    return 0;
}