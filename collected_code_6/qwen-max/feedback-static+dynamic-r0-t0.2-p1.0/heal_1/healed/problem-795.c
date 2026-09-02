#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int price;
    int index;
} Item;

int compare(const void *a, const void *b) {
    return ((Item *)a)->price - ((Item *)b)->price;
}

void findNcheapest(const int *prices, int n, int size, int *result) {
    Item *items = malloc(size * sizeof(Item));
    if (items == NULL) {
        return;
    }
    for (int i = 0; i < size; ++i) {
        items[i].price = prices[i];
        items[i].index = i;
    }
    qsort(items, size, sizeof(Item), compare);
    for (int i = 0; i < n; ++i) {
        result[i] = items[i].price;
    }
    free(items);
}

int main() {
    int prices[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    int n = 3;
    int size = sizeof(prices) / sizeof(prices[0]);
    int *result = malloc(n * sizeof(int));
    if (result == NULL) {
        return 1;
    }
    findNcheapest(prices, n, size, result);
    for (int i = 0; i < n; ++i) {
        printf("%d ", result[i]);
    }
    free(result);
    return 0;
}