#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
    int value;
} KeyValuePair;

typedef struct {
    KeyValuePair *data;
    size_t size;
    size_t capacity;
} Dictionary;

int isAllValuesSameInDictionary(Dictionary *dict) {
    if(dict->size == 0) {
        return 1;
    }
    
    int value = dict->data[0].value;
    for(size_t i = 1; i < dict->size; i++) {
        if(dict->data[i].value != value) {
            return 0;
        }
    }
    return 1;
}

Dictionary* createDictionary(size_t capacity) {
    Dictionary *dict = (Dictionary*) malloc(sizeof(Dictionary));
    dict->data = (KeyValuePair*) malloc(capacity * sizeof(KeyValuePair));
    dict->size = 0;
    dict->capacity = capacity;
    return dict;
}

void addKeyValuePair(Dictionary *dict, int key, int value) {
    if(dict->size == dict->capacity) {
        return;
    }
    KeyValuePair kvp;
    kvp.key = key;
    kvp.value = value;
    dict->data[dict->size++] = kvp;
}

void freeDictionary(Dictionary *dict) {
    free(dict->data);
    free(dict);
}

int main(){
    Dictionary *dict = createDictionary(5);
    addKeyValuePair(dict, 1, 10);
    addKeyValuePair(dict, 2, 10);
    addKeyValuePair(dict, 3, 10);
    addKeyValuePair(dict, 4, 10);
    addKeyValuePair(dict, 5, 10);
    
    printf("%d\n", isAllValuesSameInDictionary(dict));
    
    freeDictionary(dict);
    return 0;
}