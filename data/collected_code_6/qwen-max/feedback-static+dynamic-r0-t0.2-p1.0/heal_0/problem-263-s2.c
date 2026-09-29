#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    int value;
} DictionaryEntry;

typedef struct {
    DictionaryEntry **entries;
    size_t count;
    size_t capacity;
} Dictionary;

Dictionary* create_dictionary(size_t initial_capacity) {
    Dictionary *dict = (Dictionary*)malloc(sizeof(Dictionary));
    dict->entries = (DictionaryEntry**)calloc(initial_capacity, sizeof(DictionaryEntry*));
    dict->count = 0;
    dict->capacity = initial_capacity;
    return dict;
}

void free_dictionary(Dictionary *dict) {
    for (size_t i = 0; i < dict->count; ++i) {
        free(dict->entries[i]->key);
        free(dict->entries[i]);
    }
    free(dict->entries);
    free(dict);
}

int find_entry(Dictionary *dict, const char *key) {
    for (size_t i = 0; i < dict->count; ++i) {
        if (strcmp(dict->entries[i]->key, key) == 0) {
            return i;
        }
    }
    return -1;
}

void add_entry(Dictionary *dict, const char *key, int value) {
    if (dict->count >= dict->capacity) {
        dict->capacity *= 2;
        dict->entries = (DictionaryEntry**)realloc(dict->entries, dict->capacity * sizeof(DictionaryEntry*));
    }

    DictionaryEntry *entry = (DictionaryEntry*)malloc(sizeof(DictionaryEntry));
    entry->key = strdup(key);
    entry->value = value;
    dict->entries[dict->count++] = entry;
}

void merge_dictionaries(Dictionary *dest, Dictionary *src) {
    for (size_t i = 0; i < src->count; ++i) {
        int index = find_entry(dest, src->entries[i]->key);
        if (index == -1) {
            add_entry(dest, src->entries[i]->key, src->entries[i]->value);
        } else {
            dest->entries[index]->value = src->entries[i]->value;
        }
    }
}

int main() {
    Dictionary *dict1 = create_dictionary(4);
    add_entry(dict1, "apple", 1);
    add_entry(dict1, "banana", 2);

    Dictionary *dict2 = create_dictionary(4);
    add_entry(dict2, "banana", 3);
    add_entry(dict2, "cherry", 4);

    merge_dictionaries(dict1, dict2);

    for (size_t i = 0; i < dict1->count; ++i) {
        printf("%s: %d\n", dict1->entries[i]->key, dict1->entries[i]->value);
    }

    free_dictionary(dict1);
    free_dictionary(dict2);

    return 0;
}