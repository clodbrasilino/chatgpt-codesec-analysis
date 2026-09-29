#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int size;
    int *data;
} Heap;

Heap* create_heap(int size) {
    Heap *h = (Heap*)malloc(sizeof(Heap));
    if (h == NULL) exit(EXIT_FAILURE);
    h->size = 0;
    h->data = (int*)malloc(size * sizeof(int));
    if (h->data == NULL) exit(EXIT_FAILURE);
    return h;
}

void free_heap(Heap *h) {
    free(h->data);
    free(h);
}

void push(Heap *h, int value) {
    if (h->size == 0) {
        h->data[h->size++] = value;
    } else {
        int i = h->size++;
        while (i > 0 && h->data[(i - 1) / 2] > value) {
            h->data[i] = h->data[(i - 1) / 2];
            i = (i - 1) / 2;
        }
        h->data[i] = value;
    }
}

int pop(Heap *h) {
    int min_value = h->data[0];
    h->data[0] = h->data[--h->size];
    int i = 0;
    while (2 * i + 1 < h->size) {
        int child = 2 * i + 1;
        if (child + 1 < h->size && h->data[child + 1] < h->data[child]) child++;
        if (h->data[i] <= h->data[child]) break;
        {
            int temp = h->data[i];
            h->data[i] = h->data[child];
            h->data[child] = temp;
            i = child;
        }
    }
    return min_value;
}

int main() {
    int numbers[] = {5, 3, 6, 2, 7, 1, 4};
    int n = sizeof(numbers) / sizeof(numbers[0]);
    Heap *h = create_heap(n);

    for (int i = 0; i < n; ++i) {
        push(h, numbers[i]);
    }

    for (int i = 0; i < n; ++i) {
        printf("%d ", pop(h));
    }

    free_heap(h);
    return 0;
}