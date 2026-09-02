#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    int value;
} DictionaryEntry;

typedef struct {
    DictionaryEntry **entries;
    int size;
    int capacity;
} Dictionary;

Dictionary* create_dictionary(int capacity) {
    Dictionary *dict = (Dictionary*)malloc(sizeof(Dictionary));
    dict->size = 0;
    dict->capacity = capacity;
    dict->entries = (DictionaryEntry**)calloc(capacity, sizeof(DictionaryEntry*));
    return dict;
}

void free_dictionary(Dictionary *dict) {
    for (int i = 0; i < dict->size; ++i) {
        free(dict->entries[i]->key);
        free(dict->entries[i]);
    }
    free(dict->entries);
    free(dict);
}

int find_entry(Dictionary *dict, const char *key) {
    for (int i = 0; i < dict->size; ++i) {
        if (strcmp(dict->entries[i]->key, key) == 0) {
            return i;
        }
    }
    return -1;
}

void add_entry(Dictionary *dict, const char *key, int value) {
    int index = find_entry(dict, key);
    if (index != -1) {
        dict->entries[index]->value = value;
    } else {
        if (dict->size >= dict->capacity) {
            dict->capacity *= 2;
            dict->entries = (DictionaryEntry**)realloc(dict->entries, dict->capacity * sizeof(DictionaryEntry*));
        }
        dict->entries[dict->size] = (DictionaryEntry*)malloc(sizeof(DictionaryEntry));
        dict->entries[dict->size]->key = strdup(key);
        dict->entries[dict->size]->value = value;
        dict->size++;
    }
}

Dictionary* merge_dictionaries(Dictionary *dict1, Dictionary *dict2) {
    Dictionary *merged = create_dictionary(dict1->size + dict2->size);
    for (int i = 0; i < dict1->size; ++i) {
        add_entry(merged, dict1->entries[i]->key, dict1->entries[i]->value);
    }
    for (int i = 0; i < dict2->size; ++i) {
        add_entry(merged, dict2->entries[i]->key, dict2->entries[i]->value);
    }
    return merged;
}

void print_dictionary(Dictionary *dict) {
    for (int i = 0; i < dict->size; ++i) {
        printf("%s: %d\n", dict->entries[i]->key, dict->entries[i]->value);
    }
}

int main() {
    Dictionary *dict1 = create_dictionary(2);
    add_entry(dict1, "apple", 10);
    add_entry(dict1, "banana", 20);

    Dictionary *dict2 = create_dictionary(2);
    add_entry(dict2, "orange", 30);
    add_entry(dict2, "banana", 25);

    Dictionary *merged = merge_dictionaries(dict1, dict2);
    print_dictionary(merged);

    free_dictionary(dict1);
    free_dictionary(dict2);
    free_dictionary(merged);

    return 0;
}