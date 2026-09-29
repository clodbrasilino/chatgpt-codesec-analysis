#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char* key;
    char* value;
} KeyValuePair;

typedef struct {
    KeyValuePair* pairs;
    size_t size;
} Dictionary;

Dictionary* createDictionary(size_t size) {
    Dictionary* dict = (Dictionary*) malloc(sizeof(Dictionary));
    if(dict == NULL) {
        return NULL;
    }
    
    dict->pairs = (KeyValuePair*) malloc(size * sizeof(KeyValuePair));
    if(dict->pairs == NULL) {
        free(dict);
        return NULL;
    }

    dict->size = size;
    return dict;
}

void setPair(Dictionary* dict, size_t index, char* key, char* value) {
    if (dict == NULL || index >= dict->size || dict->pairs == NULL) {
        return;
    }
    dict->pairs[index].key = key;
    dict->pairs[index].value = value;
}

char* getPair(Dictionary* dict, size_t index) {
    if (dict == NULL || index >= dict->size || dict->pairs == NULL) {
        return NULL;
    }

    return dict->pairs[index].value;
}

void freeDictionary(Dictionary* dict) {
    if (dict == NULL) {
        return;
    }

    if (dict->pairs != NULL) {
        free(dict->pairs);
    }

    free(dict);
}

int main() {
    Dictionary* dict = createDictionary(3);
    if (dict == NULL) {
        return 1;
    }

    setPair(dict, 0, "key1", "value1");
    setPair(dict, 1, "key2", "value2");
    setPair(dict, 2, "key3", "value3");

    printf("%s\n", getPair(dict, 0));
    printf("%s\n", getPair(dict, 1));
    printf("%s\n", getPair(dict, 2));

    freeDictionary(dict);
    
    return 0;
}