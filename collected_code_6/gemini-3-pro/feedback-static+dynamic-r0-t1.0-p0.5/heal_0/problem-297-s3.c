#include <stdio.h>
#include <stdlib.h>

typedef struct NestedList {
    int isInteger;
    int integer;
    struct NestedList** list;
    int listSize;
} NestedList;

typedef struct FlatList {
    int* data;
    int size;
    int capacity;
} FlatList;

FlatList* createFlatList(int capacity) {
    FlatList* flatList = (FlatList*)malloc(sizeof(FlatList));
    if (!flatList) return NULL;
    
    flatList->data = (int*)malloc(capacity * sizeof(int));
    if (!flatList->data) {
        free(flatList);
        return NULL;
    }
    
    flatList->size = 0;
    flatList->capacity = capacity;
    return flatList;
}

void appendToFlatList(FlatList* flatList, int value) {
    if (!flatList) return;
    
    if (flatList->size >= flatList->capacity) {
        int newCapacity = flatList->capacity * 2;
        if (newCapacity == 0) newCapacity = 1;
        
        int* newData = (int*)realloc(flatList->data, newCapacity * sizeof(int));
        if (!newData) return;
        
        flatList->data = newData;
        flatList->capacity = newCapacity;
    }
    
    flatList->data[flatList->size++] = value;
}

void freeFlatList(FlatList* flatList) {
    if (flatList) {
        free(flatList->data);
        free(flatList);
    }
}

void flattenHelper(NestedList* nestedList, FlatList* flatList) {
    if (!nestedList || !flatList) return;
    
    if (nestedList->isInteger) {
        appendToFlatList(flatList, nestedList->integer);
    } else {
        for (int i = 0; i < nestedList->listSize; i++) {
            flattenHelper(nestedList->list[i], flatList);
        }
    }
}

FlatList* flatten(NestedList* nestedList) {
    if (!nestedList) return NULL;
    
    FlatList* flatList = createFlatList(10);
    if (!flatList) return NULL;
    
    flattenHelper(nestedList, flatList);
    return flatList;
}

NestedList* createInteger(int value) {
    NestedList* node = (NestedList*)malloc(sizeof(NestedList));
    if (!node) return NULL;
    
    node->isInteger = 1;
    node->integer = value;
    node->list = NULL;
    node->listSize = 0;
    return node;
}

NestedList* createList(NestedList** list, int size) {
    NestedList* node = (NestedList*)malloc(sizeof(NestedList));
    if (!node) return NULL;
    
    node->isInteger = 0;
    node->integer = 0;
    node->list = list;
    node->listSize = size;
    return node;
}

void freeNestedList(NestedList* node) {
    if (!node) return;
    
    if (!node->isInteger && node->list) {
        for (int i = 0; i < node->listSize; i++) {
            freeNestedList(node->list[i]);
        }
        free(node->list);
    }
    free(node);
}

int main() {
    NestedList* val1 = createInteger(1);
    NestedList* val2 = createInteger(2);
    NestedList* val3 = createInteger(3);
    
    NestedList** innerArray = (NestedList**)malloc(2 * sizeof(NestedList*));
    if (!innerArray) {
        freeNestedList(val1);
        freeNestedList(val2);
        freeNestedList(val3);
        return 1;
    }
    innerArray[0] = val1;
    innerArray[1] = val2;
    
    NestedList* innerList = createList(innerArray, 2);
    if (!innerList) {
        free(innerArray);
        freeNestedList(val1);
        freeNestedList(val2);
        freeNestedList(val3);
        return 1;
    }
    
    NestedList** outerArray = (NestedList**)malloc(2 * sizeof(NestedList*));
    if (!outerArray) {
        freeNestedList(innerList);
        freeNestedList(val3);
        return 1;
    }
    outerArray[0] = innerList;
    outerArray[1] = val3;
    
    NestedList* root = createList(outerArray, 2);
    if (!root) {
        free(outerArray);
        freeNestedList(innerList);
        freeNestedList(val3);
        return 1;
    }
    
    FlatList* flatList = flatten(root);
    
    if (flatList) {
        for (int i = 0; i < flatList->size; i++) {
            printf("%d ", flatList->data[i]);
        }
        printf("\n");
        freeFlatList(flatList);
    }
    
    freeNestedList(root);
    
    return 0;
}