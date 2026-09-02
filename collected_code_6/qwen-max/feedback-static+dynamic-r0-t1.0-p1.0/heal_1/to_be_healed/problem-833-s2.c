#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strcmp'
  */

typedef struct {
    char *key;
    char *value;
} DictionaryEntry;

typedef struct {
    DictionaryEntry *entries;
    int capacity;
    int count;
} Dictionary;

Dictionary* createDictionary() {
    Dictionary *dict = (Dictionary*)malloc(sizeof(Dictionary));
    dict->capacity = 10;
    dict->count = 0;
    dict->entries = (DictionaryEntry*)calloc(dict->capacity, sizeof(DictionaryEntry));
    return dict;
}

void destroyDictionary(Dictionary *dict) {
    if (dict != NULL) {
        for (int i = 0; i < dict->count; ++i) {
            free(dict->entries[i].key);
            free(dict->entries[i].value);
        }
        free(dict->entries);
        free(dict);
    }
}

int findKeyIndex(Dictionary *dict, const char *key) {
    for (int i = 0; i < dict->count; ++i) {
        /* Possible weaknesses found:
         *  implicit declaration of function 'strcmp' [-Wimplicit-function-declaration]
         *  include the header <string.h> or explicitly provide a declaration for 'strcmp'
         *  call to undeclared library function 'strcmp' with type 'int (const char *, const char *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         */
        if (strcmp(dict->entries[i].key, key) == 0) {
            return i;
        }
    }
    return -1;
}

void addEntry(Dictionary *dict, const char *key, const char *value) {
    if (dict->count >= dict->capacity) {
        dict->capacity *= 2;
        dict->entries = (DictionaryEntry*)realloc(dict->entries, dict->capacity * sizeof(DictionaryEntry));
    }

    int index = dict->count++;
    /* Possible weaknesses found:
     *  include the header <string.h> or explicitly provide a declaration for 'strdup'
     *  call to undeclared library function 'strdup' with type 'char *(const char *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  implicit declaration of function 'strdup' [-Wimplicit-function-declaration]
     */
    dict->entries[index].key = strdup(key);
    dict->entries[index].value = strdup(value);
}

char** getKeys(const Dictionary *dict, int *keysCount) {
    *keysCount = dict->count;
    char **keys = (char**)malloc(*keysCount * sizeof(char*));
    for (int i = 0; i < *keysCount; ++i) {
        keys[i] = strdup(dict->entries[i].key);
    }
    return keys;
}

void freeKeys(char **keys, int keysCount) {
    for (int i = 0; i < keysCount; ++i) {
        free(keys[i]);
    }
    free(keys);
}

int main() {
    Dictionary *dict = createDictionary();
    addEntry(dict, "name", "Alice");
    addEntry(dict, "age", "25");
    addEntry(dict, "city", "Wonderland");

    int keysCount;
    char **keys = getKeys(dict, &keysCount);

    for (int i = 0; i < keysCount; ++i) {
        printf("Key: %s\n", keys[i]);
    }

    freeKeys(keys, keysCount);
    destroyDictionary(dict);
    return 0;
}