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
    if (dict == NULL) {
        printf("Error: Dictionary pointer is NULL\n");
        return -1;
    }
    return dict->size == 0;
}

int main() {
    Dictionary *dict = malloc(sizeof(Dictionary));
    if (dict == NULL) {
        printf("Error: Memory allocation failed\n");
        return -1;
    }
    dict->pairs = NULL;
    dict->size = 0;

    if (isDictionaryEmpty(dict) == 1) {
        printf("Dictionary is empty\n");
    } else if(isDictionaryEmpty(dict) == 0) {
        printf("Dictionary is not empty\n");
    }
    free(dict);
    return 0;
}