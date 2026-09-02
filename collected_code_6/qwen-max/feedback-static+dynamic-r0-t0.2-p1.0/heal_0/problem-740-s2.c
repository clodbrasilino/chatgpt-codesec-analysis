#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} KeyValuePair;

typedef struct {
    KeyValuePair *pairs;
    int count;
} Dictionary;

Dictionary* createDictionary(int size) {
    Dictionary *dict = (Dictionary *)malloc(sizeof(Dictionary));
    if (dict == NULL) return NULL;
    dict->pairs = (KeyValuePair *)malloc(size * sizeof(KeyValuePair));
    if (dict->pairs == NULL) {
        free(dict);
        return NULL;
    }
    dict->count = 0;
    return dict;
}

void addKeyValuePair(Dictionary *dict, const char *key, const char *value) {
    if (dict->count >= (int)(sizeof(dict->pairs) / sizeof(KeyValuePair))) return;
    dict->pairs[dict->count].key = strdup(key);
    dict->pairs[dict->count].value = strdup(value);
    dict->count++;
}

void freeDictionary(Dictionary *dict) {
    for (int i = 0; i < dict->count; i++) {
        free(dict->pairs[i].key);
        free(dict->pairs[i].value);
    }
    free(dict->pairs);
    free(dict);
}

Dictionary* tupleToDictionary(const char *tuple[], int length) {
    if (length % 2 != 0) return NULL;
    Dictionary *dict = createDictionary(length / 2);
    if (dict == NULL) return NULL;
    for (int i = 0; i < length; i += 2) {
        addKeyValuePair(dict, tuple[i], tuple[i + 1]);
    }
    return dict;
}

int main() {
    const char *tuple[] = {"key1", "value1", "key2", "value2", "key3", "value3"};
    int length = sizeof(tuple) / sizeof(tuple[0]);
    Dictionary *dict = tupleToDictionary(tuple, length);
    if (dict == NULL) {
        printf("Failed to create dictionary.\n");
        return 1;
    }
    for (int i = 0; i < dict->count; i++) {
        printf("%s: %s\n", dict->pairs[i].key, dict->pairs[i].value);
    }
    freeDictionary(dict);
    return 0;
}