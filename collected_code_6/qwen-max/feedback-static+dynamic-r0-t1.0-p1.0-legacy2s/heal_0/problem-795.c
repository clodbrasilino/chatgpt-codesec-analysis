#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int price;
    int index;
} Item;

int compare(const void *a, const void *b) {
    return ((Item *)a)->price - ((Item *)b)->price;
}

void heapify(Item *items, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && items[left].price > items[largest].price)
        largest = left;

    if (right < n && items[right].price > items[largest].price)
        largest = right;

    if (largest != i) {
        Item temp = items[i];
        items[i] = items[largest];
        items[largest] = temp;

        heapify(items, n, largest);
    }
}

void buildHeap(Item *items, int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(items, n, i);
}

void extractNItems(Item *items, int n, int count) {
    for (int i = 0; i < count; i++) {
        Item root = items[0];
        printf("Price: %d, Index: %d\n", root.price, root.index);

        items[0] = items[n - 1 - i];
        heapify(items, n - 1 - i, 0);
    }
}

int main() {
    int prices[] = {25, 10, 89, 76, 45, 34, 23, 12, 6, 3, 2, 1};
    int n = sizeof(prices) / sizeof(prices[0]);
    int count = 4;

    Item items[n];
    for (int i = 0; i < n; i++) {
        items[i].price = prices[i];
        items[i].index = i;
    }

    qsort(items, n, sizeof(Item), compare);

    buildHeap(items, n);

    extractNItems(items, n, count);

    return 0;
}