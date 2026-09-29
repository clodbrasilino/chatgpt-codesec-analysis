#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int price;
    int index;
} Item;

int compare(const void *a, const void *b) {
    return ((Item *)a)->price - ((Item *)b)->price;
}

void find_n_cheapest(const int *prices, int n, int size, Item *result) {
    Item *items = (Item *)malloc(size * sizeof(Item));
    if (!items) return;

    for (int i = 0; i < size; ++i) {
        items[i].price = prices[i];
        items[i].index = i;
    }

    qsort(items, size, sizeof(Item), compare);

    for (int i = 0; i < n; ++i) {
        result[i] = items[i];
    }

    free(items);
}

int main() {
    int prices[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    int n = 3;
    int size = sizeof(prices) / sizeof(prices[0]);
    Item result[n];

    find_n_cheapest(prices, n, size, result);

    for (int i = 0; i < n; ++i) {
        printf("Price: %d, Index: %d\n", result[i].price, result[i].index);
    }

    return 0;
}