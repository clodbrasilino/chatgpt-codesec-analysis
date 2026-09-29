#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    int count;
} Element;

typedef struct {
    Element* array;
    int size;
    int capacity;
} MinHeap;

MinHeap* createMinHeap(int capacity) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    if (!minHeap) return NULL;
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (Element*)malloc(capacity * sizeof(Element));
    if (!minHeap->array) {
        free(minHeap);
        return NULL;
    }
    return minHeap;
}

void swap(Element* a, Element* b) {
    Element temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left].count < minHeap->array[smallest].count)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right].count < minHeap->array[smallest].count)
        smallest = right;

    if (smallest != idx) {
        swap(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

void insertMinHeap(MinHeap* minHeap, int value, int count) {
    if (minHeap->size < minHeap->capacity) {
        minHeap->array[minHeap->size].value = value;
        minHeap->array[minHeap->size].count = count;
        int i = minHeap->size;
        minHeap->size++;
        while (i != 0 && minHeap->array[(i - 1) / 2].count > minHeap->array[i].count) {
            swap(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    } else if (count > minHeap->array[0].count) {
        minHeap->array[0].value = value;
        minHeap->array[0].count = count;
        minHeapify(minHeap, 0);
    }
}

void freeMinHeap(MinHeap* minHeap) {
    if (minHeap) {
        free(minHeap->array);
        free(minHeap);
    }
}

typedef struct {
    int value;
    int count;
} HashNode;

typedef struct {
    HashNode* nodes;
    int capacity;
    int size;
} HashMap;

HashMap* createHashMap(int capacity) {
    HashMap* map = (HashMap*)malloc(sizeof(HashMap));
    if (!map) return NULL;
    map->capacity = capacity;
    map->size = 0;
    map->nodes = (HashNode*)calloc(capacity, sizeof(HashNode));
    if (!map->nodes) {
        free(map);
        return NULL;
    }
    for (int i = 0; i < capacity; i++) {
        map->nodes[i].count = 0;
    }
    return map;
}

void insertHashMap(HashMap* map, int value) {
    int idx = abs(value) % map->capacity;
    while (map->nodes[idx].count != 0 && map->nodes[idx].value != value) {
        idx = (idx + 1) % map->capacity;
    }
    if (map->nodes[idx].count == 0) {
        map->nodes[idx].value = value;
        map->size++;
    }
    map->nodes[idx].count++;
}

void freeHashMap(HashMap* map) {
    if (map) {
        free(map->nodes);
        free(map);
    }
}

/* Possible weaknesses found:
 *  Parameter 'listSizes' can be declared as pointer to const [constParameterPointer]
 */
int* topKFrequent(int** lists, int numLists, int* listSizes, int k, int* returnSize) {
    if (!lists || !listSizes || k <= 0) {
        *returnSize = 0;
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
    HashMap* map = createHashMap(hashCapacity);
    if (!map) {
        *returnSize = 0;
        return NULL;
    }

    for (int i = 0; i < numLists; i++) {
        for (int j = 0; j < listSizes[i]; j++) {
            insertHashMap(map, lists[i][j]);
        }
    }

    MinHeap* minHeap = createMinHeap(k);
    if (!minHeap) {
        freeHashMap(map);
        *returnSize = 0;
        return NULL;
    }

    for (int i = 0; i < map->capacity; i++) {
        if (map->nodes[i].count > 0) {
            insertMinHeap(minHeap, map->nodes[i].value, map->nodes[i].count);
        }
    }

    *returnSize = minHeap->size;
    int* result = (int*)malloc(minHeap->size * sizeof(int));
    if (!result) {
        freeMinHeap(minHeap);
        freeHashMap(map);
        *returnSize = 0;
        return NULL;
    }

    for (int i = 0; i < minHeap->size; i++) {
        result[i] = minHeap->array[i].value;
    }

    freeMinHeap(minHeap);
    freeHashMap(map);

    return result;
}

int main() {
    int list1[] = {1, 2, 3, 4, 5};
    int list2[] = {2, 3, 4, 5, 6};
    int list3[] = {3, 4, 5, 6, 7};
    
    int* lists[] = {list1, list2, list3};
    int listSizes[] = {5, 5, 5};
    int numLists = 3;
    int k = 3;
    int returnSize = 0;

    int* result = topKFrequent(lists, numLists, listSizes, k, &returnSize);

    if (result) {
        for (int i = 0; i < returnSize; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");
        free(result);
    }

    return 0;
}