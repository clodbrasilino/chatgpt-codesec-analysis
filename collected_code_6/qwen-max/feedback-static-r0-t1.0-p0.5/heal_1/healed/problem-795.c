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
    for (int i = 0; i < size; ++i) {
        result[i].price = prices[i];
        result[i].index = i;
    }
    qsort(result, size, sizeof(Item), compare);
}

int main() {
    int prices[] = {120, 34, 56, 78, 90, 23, 45, 67, 89, 10};
    int n = 3;
    int size = sizeof(prices) / sizeof(prices[0]);
    Item *result = (Item *)malloc(size * sizeof(Item));
    if (result == NULL) {
        return 1;
    }
    find_n_cheapest(prices, n, size, result);
    for (int i = 0; i < n; ++i) {
        printf("Price: %d, Index: %d\n", result[i].price, result[i].index);
    }
    free(result);
    return 0;
}