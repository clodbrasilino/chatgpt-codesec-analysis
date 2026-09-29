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

KeyValuePair* get_element_by_index(Dictionary* dict, int index) {
    if(index < 0 || index >= dict->size) {
        return NULL;
    }
    return &(dict->pairs[index]);
}

int main() {
    Dictionary dict;
    dict.size = 3;
    dict.pairs = malloc(sizeof(KeyValuePair) * dict.size);

    dict.pairs[0].key = "key1";
    dict.pairs[0].value = "value1";
    dict.pairs[1].key = "key2";
    dict.pairs[1].value = "value2";
    dict.pairs[2].key = "key3";
    dict.pairs[2].value = "value3";

    KeyValuePair* pair = get_element_by_index(&dict, 1);
    if(pair != NULL) {
        printf("Key: %s, Value: %s\n", pair->key, pair->value);
    } else {
        printf("Index out of range\n");
    }

    free(dict.pairs);

    return 0;
}