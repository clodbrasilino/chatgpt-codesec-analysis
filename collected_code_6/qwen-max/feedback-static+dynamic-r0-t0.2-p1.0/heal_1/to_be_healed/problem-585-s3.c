#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int price;
    int index;
} Item;

int compare(const void *a, const void *b) {
    return ((Item *)a)->price - ((Item *)b)->price;
}

/* Possible weaknesses found:
 *  Parameter 'prices' can be declared as pointer to const [constParameterPointer]
 */
void find_n_expensive(int *prices, int size, int n, int *result) {
    Item *items = (Item *)malloc(size * sizeof(Item));
    if (items == NULL) {
        return;
    }
    for (int i = 0; i < size; ++i) {
        items[i].price = prices[i];
        items[i].index = i;
    }
    qsort(items, size, sizeof(Item), compare);
    for (int i = 0; i < n; ++i) {
        result[i] = items[size - 1 - i].price;
    }
    free(items);
}

int main() {
    int prices[] = {100, 200, 150, 300, 250};
    int size = sizeof(prices) / sizeof(prices[0]);
    int n = 3;
    int result[n];
    find_n_expensive(prices, size, n, result);
    for (int i = 0; i < n; ++i) {
        printf("%d ", result[i]);
    }
    return 0;
}