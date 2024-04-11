#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* key;
    char* value;
} KeyValuePair;

typedef struct {
    KeyValuePair* pairs;
    size_t size;
} Dictionary;

Dictionary* createDictionary(size_t size) {
    Dictionary* dict = malloc(sizeof(Dictionary));
    dict->pairs = malloc(sizeof(KeyValuePair) * size);
    dict->size = size;
    return dict;
}

void setKeyValuePair(Dictionary* dict, size_t index, char* key, char* value) {
    dict->pairs[index].key = strdup(key);
    dict->pairs[index].value = strdup(value);
}

Dictionary* mergeDictionaries(Dictionary* dict1, Dictionary* dict2) {
    size_t newSize = dict1->size + dict2->size;
    Dictionary* mergedDict = createDictionary(newSize);

    for (size_t i = 0; i < dict1->size; i++) {
        setKeyValuePair(mergedDict, i, dict1->pairs[i].key, dict1->pairs[i].value);
    }

    for (size_t i = 0; i < dict2->size; i++) {
        setKeyValuePair(mergedDict, i + dict1->size, dict2->pairs[i].key, dict2->pairs[i].value);
    }

    return mergedDict;
}

int main() {
    Dictionary* dict1 = createDictionary(2);
    setKeyValuePair(dict1, 0, "key1", "value1");
    setKeyValuePair(dict1, 1, "key2", "value2");

    Dictionary* dict2 = createDictionary(2);
    setKeyValuePair(dict2, 0, "key3", "value3");
    setKeyValuePair(dict2, 1, "key4", "value4");

    Dictionary* mergedDict = mergeDictionaries(dict1, dict2);

    for (size_t i = 0; i < mergedDict->size; i++) {
        printf("%s: %s\n", mergedDict->pairs[i].key, mergedDict->pairs[i].value);
    }

    return 0;
}