#include <stdio.h>
#include <stdlib.h>
#include<string.h>

typedef struct Item {
    int id;
    double price;
} Item;

typedef struct HeapData {
    Item item;
    struct HeapData *left, *right;
} HeapData;

HeapData* newHeapData(double price, int id) {
    HeapData* heapData = (HeapData *)malloc(sizeof(HeapData));
    heapData->item.price = price;
    heapData->item.id = id;
    heapData->left = heapData->right = NULL;
    return heapData;
}

HeapData* insertHeapData(HeapData* h, HeapData* data, int* heap_size, int* max_size) {
    if ((*heap_size) < (*max_size)) {
        if ((*heap_size) == 0) {
            (*heap_size)++;
            h = data;
        }
        else if (h->item.price > data->item.price) {
            (*heap_size)++;
            data->left = h;
            h = data;
        }
        else if (h->right == NULL) {
            (*heap_size)++;
            h->right = data;
        }
        else {
            (*heap_size)++;
            h->right = insertHeapData(h->right, data, heap_size, max_size);
        }
    } else if (h->item.price > data->item.price) {
        h = insertHeapData(h->left, data, heap_size, max_size);
    }
    return h;
}

void heapify(HeapData* h) {
    HeapData *left = h->left, *right = h->right, *smallest;
    if (right != NULL && right->item.price < h->item.price)
        smallest = right;
    else
        smallest = h;
    if (left != NULL && left->item.price < smallest->item.price)
        smallest = left;

    if (smallest != h) {
        Item temp = h->item;
        h->item = smallest->item;
        smallest->item = temp;
        heapify(smallest);
    }
}

void getCheapestItems(HeapData *h, Item *items, int n) {
    int i, max_size = n, heap_size = 0;
    HeapData* temp = NULL;
    for (i = 0; i < n; i++) {
        temp = newHeapData(items[i].price, items[i].id);
        h = insertHeapData(h, temp, &heap_size, &max_size);
    }
    while(h != NULL) {
        printf("Id: %d \tPrice: %.2f\n", h->item.id, h->item.price);
        h = h->left;
    }
}

int main() {
    int n = 10;
    Item items[n];

    items[0].id = 1;
    items[0].price = 20.0;
    items[1].id = 2;
    items[1].price = 15.0;
    items[2].id = 3;
    items[2].price = 22.0;
    items[3].id = 4;
    items[3].price = 13.0;
    items[4].id = 5;
    items[4].price = 20.0;
    items[5].id = 6;
    items[5].price = 21.0;
    items[6].id = 7;
    items[6].price = 16.0;
    items[7].id = 8;
    items[7].price = 25.0;
    items[8].id = 9;
    items[8].price = 13.0;
    items[9].id = 10;
    items[9].price = 18.0;
  
    HeapData* h = NULL;
    getCheapestItems(h, items, n);

    return 0;
}