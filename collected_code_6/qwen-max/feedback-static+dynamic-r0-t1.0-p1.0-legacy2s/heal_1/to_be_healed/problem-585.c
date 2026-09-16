#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
    int price;
} Item;

typedef struct {
    Item *arr;
    int size;
    int capacity;
} PriorityQueue;

PriorityQueue* createQueue(int capacity) {
    PriorityQueue* q = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    q->arr = (Item*)malloc(capacity * sizeof(Item));
    q->size = 0;
    q->capacity = capacity;
    return q;
}

void swapItems(Item *a, Item *b) {
    Item temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(PriorityQueue *q, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < q->size && q->arr[left].price < q->arr[smallest].price)
        smallest = left;

    if (right < q->size && q->arr[right].price < q->arr[smallest].price)
        smallest = right;

    if (smallest != i) {
        swapItems(&q->arr[i], &q->arr[smallest]);
        heapify(q, smallest);
    }
}

void insert(PriorityQueue *q, Item item) {
    if (q->size == q->capacity) {
        if (item.price > q->arr[0].price) {
            q->arr[0] = item;
            heapify(q, 0);
        }
    } else {
        int i = q->size;
        q->arr[i] = item;
        while (i != 0 && q->arr[(i - 1) / 2].price > q->arr[i].price) {
            swapItems(&q->arr[i], &q->arr[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
        q->size++;
    }
}

void printNExpensiveItems(PriorityQueue *q) {
    for (int i = 0; i < q->size; i++) {
        printf("%s: %d\n", q->arr[i].name, q->arr[i].price);
    }
}

void freeQueue(PriorityQueue *q) {
    free(q->arr);
    free(q);
}

int main() {
    /* Possible weaknesses found:
     *  Variable 'items' can be declared as const array [constVariable]
     */
    Item items[] = {{"Apple", 80}, {"Banana", 50}, {"Cherry", 70}, {"Date", 90}, {"Elderberry", 60}};
    int n = 3;
    PriorityQueue *q = createQueue(n);

    for (int i = 0; i < 5; i++) {
        insert(q, items[i]);
    }

    printNExpensiveItems(q);
    freeQueue(q);

    return 0;
}