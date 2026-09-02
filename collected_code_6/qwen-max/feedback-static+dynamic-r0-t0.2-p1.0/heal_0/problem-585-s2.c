#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int price;
    int id;
} Item;

int compare(const void *a, const void *b) {
    return ((Item *)b)->price - ((Item *)a)->price;
}

void find_n_expensive_items(Item *items, int size, int n, Item *result) {
    qsort(items, size, sizeof(Item), compare);
    for (int i = 0; i < n; i++) {
        result[i] = items[i];
    }
}

int main() {
    Item items[] = {{100, 1}, {200, 2}, {50, 3}, {300, 4}, {150, 5}};
    int size = 5;
    int n = 3;
    Item result[n];

    find_n_expensive_items(items, size, n, result);

    for (int i = 0; i < n; i++) {
        printf("Item ID: %d, Price: %d\n", result[i].id, result[i].price);
    }

    return 0;
}