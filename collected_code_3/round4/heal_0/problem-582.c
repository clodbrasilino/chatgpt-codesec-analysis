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
    dict->items = (Item*)malloc(sizeof(Item) * capacity);
    dict->size = 0;
    dict->capacity = capacity;
    return dict;
}

int isDictionaryEmpty(Dictionary *dict) {
    return dict->size == 0;
}

int main() {
    Dictionary *dict = createDictionary(10);
    if(isDictionaryEmpty(dict)) {
        printf("Dictionary is empty\n");
    } else {
        printf("Dictionary is not empty\n");
    }
    return 0;
}