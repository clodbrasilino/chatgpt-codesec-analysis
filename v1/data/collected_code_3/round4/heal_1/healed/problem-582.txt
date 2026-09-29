#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
    int value;
} Item;

typedef struct {
    Item *items;
    int size;
    int capacity;
} Dictionary;

Dictionary* createDictionary(int capacity) {
    Dictionary *dict = (Dictionary*)malloc(sizeof(Dictionary));
    if (dict == NULL) {
        return NULL;
    }
    dict->items = (Item*)malloc(sizeof(Item) * capacity);
    if (dict->items == NULL) {
        free(dict);
        return NULL;
    }
    dict->size = 0;
    dict->capacity = capacity;
    return dict;
}

int isDictionaryEmpty(Dictionary *dict) {
    if(dict == NULL){
        return -1;
    }
    return dict->size == 0;
}

int main() {
    Dictionary *dict = createDictionary(10);
    if(dict == NULL){
        printf("Failed to create dictionary\n");
        return -1;
    }
    if(isDictionaryEmpty(dict)) {
        printf("Dictionary is empty\n");
    } else {
        printf("Dictionary is not empty\n");
    }
    free(dict->items);
    free(dict);
    return 0;
}