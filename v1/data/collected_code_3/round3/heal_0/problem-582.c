#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
    int value;
} KeyValuePair;

typedef struct {
    KeyValuePair *pairs;
    int size;
} Dictionary;

int isDictionaryEmpty(Dictionary *dict) {
    return dict->size == 0;
}

int main() {
    Dictionary *dict = malloc(sizeof(Dictionary));
    dict->pairs = NULL;
    dict->size = 0;

    if (isDictionaryEmpty(dict)) {
        printf("Dictionary is empty\n");
    } else {
        printf("Dictionary is not empty\n");
    }

    free(dict);
    return 0;
}