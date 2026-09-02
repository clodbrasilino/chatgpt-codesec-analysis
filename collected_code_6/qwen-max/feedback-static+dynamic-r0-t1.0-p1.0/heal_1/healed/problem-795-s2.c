#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int price;
    int index;
} Item;

int compare(const void *a, const void *b) {
    return ((Item *)a)->price - ((Item *)b)->price;
}

void find_n_cheapest(const int *prices, int n, int total, int **result, int *result_size) {
    if (n > total || n < 0) {
        *result_size = 0;
        *result = NULL;
        return;
    }

    Item *items = (Item *)malloc(total * sizeof(Item));
    if (!items) {
        *result_size = 0;
        *result = NULL;
        return;
    }

    for (int i = 0; i < total; ++i) {
        items[i].price = prices[i];
        items[i].index = i;
    }

    qsort(items, total, sizeof(Item), compare);

    *result_size = n;
    *result = (int *)malloc(n * sizeof(int));
    if (*result == NULL) {
        free(items);
        *result_size = 0;
        *result = NULL;
        return;
    }

    for (int i = 0; i < n; ++i) {
        (*result)[i] = items[i].price;
    }

    free(items);
}

int main() {
    int prices[] = {99, 35, 29, 10, 58, 14, 75, 6};
    int n = 4;
    int total = sizeof(prices) / sizeof(*prices);

    int *cheapest_prices = NULL;
    int cheapest_prices_size = 0;

    find_n_cheapest(prices, n, total, &cheapest_prices, &cheapest_prices_size);

    if (cheapest_prices != NULL) {
        for (int i = 0; i < cheapest_prices_size; ++i) {
            printf("%d ", cheapest_prices[i]);
        }
        free(cheapest_prices);
    } else {
        printf("Failed to find the n cheapest items.\n");
    }

    return 0;
}