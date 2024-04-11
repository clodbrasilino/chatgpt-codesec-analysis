#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char* key;
    char* value;
} KeyValuePair;

typedef struct {
    KeyValuePair* pairs;
    int size;
} Dictionary;

char** getKeys(Dictionary* dict) {
    char** keys = malloc(sizeof(char*) * dict->size);
    if (keys == NULL) return NULL;

    for(int i = 0; i < dict->size; i++) {
        keys[i] = dict->pairs[i].key;
    }
    return keys;
}

int main() {
    Dictionary dict;
    dict.size = 3;
    dict.pairs = malloc(sizeof(KeyValuePair) * dict.size);
    if (dict.pairs == NULL) return 1;

    dict.pairs[0].key = "key1";
    dict.pairs[0].value = "value1";
    dict.pairs[1].key = "key2";
    dict.pairs[1].value = "value2";
    dict.pairs[2].key = "key3";
    dict.pairs[2].value = "value3";

    char** keys = getKeys(&dict);
    if (keys == NULL) {
        free(dict.pairs);
        return 1;
    }

    for(int i = 0; i < dict.size; i++) {
        printf("%s\n", keys[i]);
    }

    free(keys);
    free(dict.pairs);

    return 0;
}