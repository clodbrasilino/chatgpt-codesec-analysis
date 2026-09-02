#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    int value;
} DictionaryEntry;

typedef struct {
    DictionaryEntry **entries;
    int count;
    int capacity;
} Dictionary;

Dictionary* dictionary_create(int capacity) {
    Dictionary *dict = (Dictionary*)malloc(sizeof(Dictionary));
    dict->count = 0;
    dict->capacity = capacity > 1 ? capacity : 2;
    dict->entries = (DictionaryEntry**)calloc(dict->capacity, sizeof(DictionaryEntry*));
    return dict;
}

void dictionary_free(Dictionary *dict) {
    for (int i = 0; i < dict->count; i++) {
        free(dict->entries[i]->key);
        free(dict->entries[i]);
    }
    free(dict->entries);
    free(dict);
}

int dictionary_add(Dictionary *dict, const char *key, int value) {
    if (dict->count >= dict->capacity) {
        dict->capacity *= 2;
        dict->entries = (DictionaryEntry**)realloc(dict->entries, dict->capacity * sizeof(DictionaryEntry*));
    }

    for (int i = 0; i < dict->count; i++) {
        if (strcmp(dict->entries[i]->key, key) == 0) {
            return -1; // Key already exists
        }
    }

    DictionaryEntry *entry = (DictionaryEntry*)malloc(sizeof(DictionaryEntry));
    entry->key = strdup(key);
    entry->value = value;
    dict->entries[dict->count++] = entry;

    return 0;
}

Dictionary* dictionary_merge(Dictionary *dict1, Dictionary *dict2) {
    Dictionary *merged = dictionary_create(dict1->count + dict2->count);

    for (int i = 0; i < dict1->count; i++) {
        dictionary_add(merged, dict1->entries[i]->key, dict1->entries[i]->value);
    }

    for (int i = 0; i < dict2->count; i++) {
        if (dictionary_add(merged, dict2->entries[i]->key, dict2->entries[i]->value) != 0) {
            // Key already exists, update value
            for (int j = 0; j < merged->count; j++) {
                if (strcmp(merged->entries[j]->key, dict2->entries[i]->key) == 0) {
                    merged->entries[j]->value = dict2->entries[i]->value;
                }
            }
        }
    }

    return merged;
}

int main() {
    Dictionary *dict1 = dictionary_create(2);
    dictionary_add(dict1, "one", 1);
    dictionary_add(dict1, "two", 2);

    Dictionary *dict2 = dictionary_create(2);
    dictionary_add(dict2, "two", 20);
    dictionary_add(dict2, "three", 3);

    Dictionary *merged = dictionary_merge(dict1, dict2);

    for (int i = 0; i < merged->count; i++) {
        printf("%s: %d\n", merged->entries[i]->key, merged->entries[i]->value);
    }

    dictionary_free(dict1);
    dictionary_free(dict2);
    dictionary_free(merged);

    return 0;
}