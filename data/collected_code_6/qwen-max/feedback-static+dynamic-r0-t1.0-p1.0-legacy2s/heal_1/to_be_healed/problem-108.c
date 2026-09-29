#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    int index;
} Element;

typedef struct {
    Element *elements;
    int size;
    int capacity;
} PriorityQueue;

int compare(const void *a, const void *b) {
    return ((Element *)a)->value - ((Element *)b)->value;
}

void heapify(PriorityQueue *pq, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < pq->size && pq->elements[left].value < pq->elements[smallest].value)
        smallest = left;

    if (right < pq->size && pq->elements[right].value < pq->elements[smallest].value)
        smallest = right;

    if (smallest != i) {
        Element temp = pq->elements[i];
        pq->elements[i] = pq->elements[smallest];
        pq->elements[smallest] = temp;
        heapify(pq, smallest);
    }
}

void insert(PriorityQueue *pq, Element element) {
    if (pq->size == pq->capacity) {
        pq->capacity = pq->capacity == 0 ? 1 : pq->capacity * 2;
        pq->elements = realloc(pq->elements, pq->capacity * sizeof(Element));
    }
    pq->elements[pq->size] = element;
    int i = pq->size;
    while (i > 0 && pq->elements[(i - 1) / 2].value > pq->elements[i].value) {
        Element temp = pq->elements[i];
        pq->elements[i] = pq->elements[(i - 1) / 2];
        pq->elements[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
    pq->size++;
}

Element extractMin(PriorityQueue *pq) {
    Element min = pq->elements[0];
    pq->elements[0] = pq->elements[--pq->size];
    heapify(pq, 0);
    return min;
}

/* Possible weaknesses found:
 *  Parameter 'pq' can be declared as pointer to const [constParameterPointer]
 */
int is_empty(PriorityQueue *pq) {
    return pq->size == 0;
}

void merge_sorted_arrays(int *arrays[], int sizes[], int k, int n) {
    PriorityQueue pq = {NULL, 0, 0};
    for (int i = 0; i < k; i++) {
        if (sizes[i] > 0) {
            insert(&pq, (Element){arrays[i][0], i});
            sizes[i]--;
        }
    }

    while (!is_empty(&pq)) {
        Element min = extractMin(&pq);
        printf("%d ", min.value);
        if (sizes[min.index] > 0) {
            insert(&pq, (Element){arrays[min.index][sizes[min.index]], min.index});
            sizes[min.index]--;
        }
    }
    printf("\n");
    free(pq.elements);
}

int main() {
    int arr1[] = {1, 3, 5, 7};
    int arr2[] = {2, 4, 6, 8};
    int arr3[] = {0, 9, 10, 11};

    int *arrays[] = {arr1, arr2, arr3};
    int sizes[] = {4, 4, 4};
    int k = 3;

    merge_sorted_arrays(arrays, sizes, k, 4);

    return 0;
}