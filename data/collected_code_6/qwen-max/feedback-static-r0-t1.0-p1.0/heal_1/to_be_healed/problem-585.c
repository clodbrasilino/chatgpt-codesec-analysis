#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int price;
    void *item;
} Item;

typedef struct {
    int size;
    int capacity;
    Item **array;
} PriorityQueue;

PriorityQueue* createPriorityQueue(int capacity) {
    PriorityQueue* pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    pq->size = 0;
    pq->capacity = capacity;
    pq->array = (Item**)malloc(capacity * sizeof(Item*));
    return pq;
}

void swap(Item **a, Item **b) {
    Item *temp = *a;
    *a = *b;
    *b = temp;
}

int parent(int i) {
    return (i - 1) / 2;
}

int leftChild(int i) {
    return (2 * i + 1);
}

int rightChild(int i) {
    return (2 * i + 2);
}

void heapify(PriorityQueue *pq, int i) {
    int largest = i;
    int l = leftChild(i);
    int r = rightChild(i);

    if (l < pq->size && pq->array[l]->price > pq->array[largest]->price)
        largest = l;
    if (r < pq->size && pq->array[r]->price > pq->array[largest]->price)
        largest = r;
    if (largest != i) {
        swap(&pq->array[i], &pq->array[largest]);
        heapify(pq, largest);
    }
}

void insert(PriorityQueue *pq, Item *item) {
    if (pq->size == pq->capacity) {
        if (pq->array[0]->price < item->price) {
            pq->array[0] = item;
            heapify(pq, 0);
        }
    } else {
        int i = pq->size;
        pq->array[i] = item;
        while (i != 0 && pq->array[parent(i)]->price < pq->array[i]->price) {
            swap(&pq->array[i], &pq->array[parent(i)]);
            i = parent(i);
        }
        pq->size++;
    }
}

Item** findNExpensiveItems(Item *items, int n, int totalItems) {
    PriorityQueue *pq = createPriorityQueue(n);
    for (int i = 0; i < totalItems; ++i) {
        insert(pq, &items[i]);
    }
    return pq->array;
}

int main() {
    /* Possible weaknesses found:
     *  Variable 'prices' can be declared as const array [constVariable]
     */
    int prices[] = {50, 100, 20, 80, 70, 90};
    char items[][10] = {"ItemA", "ItemB", "ItemC", "ItemD", "ItemE", "ItemF"};
    int n = 3;
    int totalItems = 6;

    Item *dataset = (Item*)malloc(totalItems * sizeof(Item));
    for (int i = 0; i < totalItems; ++i) {
        dataset[i].price = prices[i];
        dataset[i].item = &items[i];
    }

    Item** result = findNExpensiveItems(dataset, n, totalItems);
    for (int i = 0; i < n; ++i) {
        printf("%s: %d\n", (char*)(result[i]->item), result[i]->price);
    }

    free(dataset);
    free(result);
    return 0;
}