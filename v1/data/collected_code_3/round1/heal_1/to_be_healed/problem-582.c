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
    return dict->size == 0;
}

int main() {
    Dictionary *dict = malloc(sizeof(Dictionary));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'dict' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    dict->items = malloc(10 * sizeof(Item));
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