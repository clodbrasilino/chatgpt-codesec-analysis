#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    int value;
} DictionaryEntry;

typedef struct {
    DictionaryEntry *entries;
    size_t count;
} Dictionary;

Dictionary* create_dictionary(size_t initial_capacity) {
    Dictionary *dict = (Dictionary*)malloc(sizeof(Dictionary));
    dict->entries = (DictionaryEntry*)calloc(initial_capacity, sizeof(DictionaryEntry));
    dict->count = 0;
    return dict;
}

void free_dictionary(Dictionary *dict) {
    for (size_t i = 0; i < dict->count; ++i) {
        free(dict->entries[i].key);
    }
    free(dict->entries);
    free(dict);
}

int find_entry(Dictionary *dict, const char *key) {
    for (size_t i = 0; i < dict->count; ++i) {
        if (strcmp(dict->entries[i].key, key) == 0) {
            return i;
        }
    }
    return -1;
}

void add_or_update_entry(Dictionary *dict, const char *key, int value) {
    int index = find_entry(dict, key);
    if (index != -1) {
        dict->entries[index].value += value;
    } else {
        dict->entries[dict->count].key = strdup(key);
        dict->entries[dict->count].value = value;
        dict->count++;
    }
}

Dictionary* combine_dictionaries(Dictionary *dict1, Dictionary *dict2) {
    Dictionary *combined = create_dictionary(dict1->count + dict2->count);

    for (size_t i = 0; i < dict1->count; ++i) {
        add_or_update_entry(combined, dict1->entries[i].key, dict1->entries[i].value);
    }

    for (size_t i = 0; i < dict2->count; ++i) {
        add_or_update_entry(combined, dict2->entries[i].key, dict2->entries[i].value);
    }

    return combined;
}

int main() {
    Dictionary *dict1 = create_dictionary(3);
    add_or_update_entry(dict1, "apple", 5);
    add_or_update_entry(dict1, "banana", 3);
    add_or_update_entry(dict1, "cherry", 7);

    Dictionary *dict2 = create_dictionary(3);
    add_or_update_entry(dict2, "apple", 2);
    add_or_update_entry(dict2, "banana", 4);
    add_or_update_entry(dict2, "date", 8);

    Dictionary *combined = combine_dictionaries(dict1, dict2);

    for (size_t i = 0; i < combined->count; ++i) {
        printf("%s: %d\n", combined->entries[i].key, combined->entries[i].value);
    }

    free_dictionary(dict1);
    free_dictionary(dict2);
    free_dictionary(combined);

    return 0;
}