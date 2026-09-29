#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    int count;
} Element;

typedef struct {
    Element *data;
    int size;
    int capacity;
} MinHeap;

MinHeap* createMinHeap(int capacity) {
    MinHeap *heap = (MinHeap*)malloc(sizeof(MinHeap));
    if (!heap) return NULL;
    heap->data = (Element*)malloc(capacity * sizeof(Element));
    if (!heap->data) {
        free(heap);
        return NULL;
    }
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void swap(Element *a, Element *b) {
    Element temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(MinHeap *heap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < heap->size && heap->data[left].count < heap->data[smallest].count)
        smallest = left;

    if (right < heap->size && heap->data[right].count < heap->data[smallest].count)
        smallest = right;

    if (smallest != idx) {
        swap(&heap->data[idx], &heap->data[smallest]);
        minHeapify(heap, smallest);
    }
}

void insertMinHeap(MinHeap *heap, Element element) {
    if (heap->size < heap->capacity) {
        heap->data[heap->size] = element;
        int i = heap->size;
        heap->size++;
        while (i != 0 && heap->data[(i - 1) / 2].count > heap->data[i].count) {
            swap(&heap->data[i], &heap->data[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    } else if (element.count > heap->data[0].count) {
        heap->data[0] = element;
        minHeapify(heap, 0);
    }
}

void freeMinHeap(MinHeap *heap) {
    if (heap) {
        free(heap->data);
        free(heap);
    }
}

typedef struct {
    int value;
    int count;
} HashNode;

typedef struct {
    HashNode *nodes;
    int capacity;
} HashMap;

HashMap* createHashMap(int capacity) {
    HashMap *map = (HashMap*)malloc(sizeof(HashMap));
    if (!map) return NULL;
    map->nodes = (HashNode*)calloc(capacity, sizeof(HashNode));
    if (!map->nodes) {
        free(map);
        return NULL;
    }
    map->capacity = capacity;
    return map;
}

void insertHashMap(HashMap *map, int value) {
    int idx = abs(value) % map->capacity;
    while (map->nodes[idx].count != 0 && map->nodes[idx].value != value) {
        idx = (idx + 1) % map->capacity;
    }
    map->nodes[idx].value = value;
    map->nodes[idx].count++;
}

void freeHashMap(HashMap *map) {
    if (map) {
        free(map->nodes);
        free(map);
    }
}

int* topKFrequent(int** lists, int numLists, const int* listSizes, int k, int* returnSize) {
    if (!lists || numLists <= 0 || !listSizes || k <= 0 || !returnSize) {
        if (returnSize) *returnSize = 0;
        return NULL;
    }

    int totalElements = 0;
    for (int i = 0; i < numLists; i++) {
        totalElements += listSizes[i];
    }

    if (totalElements == 0) {
        *returnSize = 0;
        return NULL;
    }

    int hashCapacity = totalElements * 2;
    HashMap *map = createHashMap(hashCapacity);
    if (!map) {
        *returnSize = 0;
        return NULL;
    }

    for (int i = 0; i < numLists; i++) {
        for (int j = 0; j < listSizes[i]; j++) {
            insertHashMap(map, lists[i][j]);
        }
    }

    MinHeap *heap = createMinHeap(k);
    if (!heap) {
        freeHashMap(map);
        *returnSize = 0;
        return NULL;
    }

    for (int i = 0; i < map->capacity; i++) {
        if (map->nodes[i].count > 0) {
            Element el = {map->nodes[i].value, map->nodes[i].count};
            insertMinHeap(heap, el);
        }
    }

    *returnSize = heap->size;
    int *result = (int*)malloc(heap->size * sizeof(int));
    if (!result) {
        freeMinHeap(heap);
        freeHashMap(map);
        *returnSize = 0;
        return NULL;
    }

    for (int i = heap->size - 1; i >= 0; i--) {
        result[i] = heap->data[0].value;
        heap->data[0] = heap->data[heap->size - 1];
        heap->size--;
        minHeapify(heap, 0);
    }

    freeMinHeap(heap);
    freeHashMap(map);
    return result;
}

int main() {
    int list1[] = {1, 4, 5, 8, 9};
    int list2[] = {3, 4, 5, 9, 10};
    int list3[] = {1, 4, 7, 9, 11};
    
    int* lists[] = {list1, list2, list3};
    const int listSizes[] = {5, 5, 5};
    int numLists = 3;
    int k = 2;
    int returnSize;

    int *result = topKFrequent(lists, numLists, listSizes, k, &returnSize);

    if (result) {
        for (int i = 0; i < returnSize; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");
        free(result);
    }

    return 0;
}