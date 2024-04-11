#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

typedef struct {
    char key[MAX_SIZE];
    char value[MAX_SIZE];
} KeyValuePair;

typedef struct {
    KeyValuePair pairs[MAX_SIZE];
    int size;
} Dictionary;

void addPair(Dictionary *dict, char *key, char *value) {
    strncpy(dict->pairs[dict->size].key, key, MAX_SIZE - 1);
    dict->pairs[dict->size].key[MAX_SIZE - 1] = '\0';
    strncpy(dict->pairs[dict->size].value, value, MAX_SIZE - 1);
    dict->pairs[dict->size].value[MAX_SIZE - 1] = '\0';
    dict->size++;
}

Dictionary mergeDictionaries(Dictionary *dict1, Dictionary *dict2) {
    Dictionary mergedDict;
    mergedDict.size = 0;

    for(int i = 0; i < dict1->size; i++) {
        addPair(&mergedDict, dict1->pairs[i].key, dict1->pairs[i].value);
    }

    for(int i = 0; i < dict2->size; i++) {
        addPair(&mergedDict, dict2->pairs[i].key, dict2->pairs[i].value);
    }

    return mergedDict;
}

int main() {
    Dictionary dict1, dict2, mergedDict;

    dict1.size = 0;
    dict2.size = 0;

    addPair(&dict1, "key1", "value1");
    addPair(&dict1, "key2", "value2");

    addPair(&dict2, "key3", "value3");
    addPair(&dict2, "key4", "value4");

    mergedDict = mergeDictionaries(&dict1, &dict2);

    for(int i = 0; i < mergedDict.size; i++) {
        printf("Key: %s, Value: %s\n", mergedDict.pairs[i].key, mergedDict.pairs[i].value);
    }

    return 0;
}