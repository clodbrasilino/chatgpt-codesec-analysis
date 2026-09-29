#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    void *value;
} DictionaryEntry;

typedef struct {
    DictionaryEntry *entries;
    int size;
    int capacity;
} Dictionary;

int compare(const void *a, const void *b) {
    return strcmp(((DictionaryEntry *)a)->key, ((DictionaryEntry *)b)->key);
}

void sortDictionary(Dictionary *dict) {
    qsort(dict->entries, dict->size, sizeof(DictionaryEntry), compare);
}

void addEntry(Dictionary *dict, const char *key, void *value) {
    if (dict->size + 1 >= dict->capacity) {
        dict->capacity = (dict->capacity == 0) ? 8 : dict->capacity * 2;
        dict->entries = realloc(dict->entries, dict->capacity * sizeof(DictionaryEntry));
    }
    dict->entries[dict->size].key = strdup(key);
    dict->entries[dict->size].value = value;
    dict->size++;
}

void freeDictionary(Dictionary *dict) {
    for (int i = 0; i < dict->size; i++) {
        free(dict->entries[i].key);
    }
    free(dict->entries);
    dict->entries = NULL;
    dict->size = 0;
    dict->capacity = 0;
}

int main() {
    Dictionary dict = {NULL, 0, 0};
    addEntry(&dict, "apple", (void *)1);
    addEntry(&dict, "banana", (void *)2);
    addEntry(&dict, "cherry", (void *)3);

    sortDictionary(&dict);

    for (int i = 0; i < dict.size; i++) {
        printf("%s: %p\n", dict.entries[i].key, dict.entries[i].value);
    }

    freeDictionary(&dict);
    return 0;
}