#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
    int value;
} Item;

typedef struct {
    Item *items;
    int capacity;
    int size;
} Dictionary;

int isDictionaryEmpty(Dictionary *dict) {
    if (!dict) {
        return 1;
    }
    return dict->size == 0;
}

int main() {
    Dictionary *dict = malloc(sizeof(Dictionary));
    if (!dict) {
        return 1;
    }

    dict->items = malloc(10 * sizeof(Item));
    if (!dict->items) {
        free(dict);
        return 1;
    }

    dict->capacity = 10;
    dict->size = 0;

    if(isDictionaryEmpty(dict)) {
        printf("Dictionary is empty\n");
    } else {
        printf("Dictionary is not empty\n");
    }

    free(dict->items);
    free(dict);

    return 0;
}