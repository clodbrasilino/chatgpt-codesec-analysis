#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} Entry;

typedef struct {
    Entry **entries;
    size_t count;
    size_t capacity;
} Dictionary;

void init_dictionary(Dictionary *dict, size_t initial_capacity) {
    dict->count = 0;
    dict->capacity = initial_capacity;
    dict->entries = (Entry **)malloc(initial_capacity * sizeof(Entry *));
}

void free_dictionary(Dictionary *dict) {
    for (size_t i = 0; i < dict->count; ++i) {
        free(dict->entries[i]->key);
        free(dict->entries[i]->value);
        free(dict->entries[i]);
    }
    free(dict->entries);
}

int add_entry(Dictionary *dict, const char *key, const char *value) {
    if (dict->count >= dict->capacity) {
        dict->capacity *= 2;
        dict->entries = (Entry **)realloc(dict->entries, dict->capacity * sizeof(Entry *));
    }

    dict->entries[dict->count] = (Entry *)malloc(sizeof(Entry));
    dict->entries[dict->count]->key = strdup(key);
    dict->entries[dict->count]->value = strdup(value);
    ++dict->count;
    return 1;
}

Dictionary convert_tuple_to_dict(char *tuple[], size_t length) {
    Dictionary dict;
    init_dictionary(&dict, 8);

    for (size_t i = 0; i < length; i += 2) {
        if (i + 1 < length) {
            add_entry(&dict, tuple[i], tuple[i + 1]);
        }
    }

    return dict;
}

void print_dictionary(Dictionary dict) {
    for (size_t i = 0; i < dict.count; ++i) {
        printf("%s: %s\n", dict.entries[i]->key, dict.entries[i]->value);
    }
}

int main() {
    char *tuple[] = {"key1", "value1", "key2", "value2", "key3", "value3"};
    size_t length = sizeof(tuple) / sizeof(tuple[0]);

    Dictionary dict = convert_tuple_to_dict(tuple, length);
    print_dictionary(dict);
    free_dictionary(&dict);

    return 0;
}