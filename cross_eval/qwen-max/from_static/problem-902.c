#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    int value;
} DictionaryEntry;

typedef struct {
    DictionaryEntry *entries;
    int capacity;
    int count;
} Dictionary;

Dictionary* create_dictionary(int capacity) {
    Dictionary *dict = (Dictionary*)malloc(sizeof(Dictionary));
    if (dict == NULL) return NULL;
    
    dict->entries = (DictionaryEntry*)calloc(capacity, sizeof(DictionaryEntry));
    if (dict->entries == NULL) {
        free(dict);
        return NULL;
    }
    
    dict->capacity = capacity;
    dict->count = 0;
    return dict;
}

void destroy_dictionary(Dictionary *dict) {
    for (int i = 0; i < dict->count; ++i) {
        free(dict->entries[i].key);
    }
    free(dict->entries);
    free(dict);
}

int get_entry_index(Dictionary *dict, const char *key) {
    for (int i = 0; i < dict->count; ++i) {
        if (strcmp(dict->entries[i].key, key) == 0) {
            return i;
        }
    }
    return -1;
}

int add_or_update_entry(Dictionary *dict, const char *key, int value) {
    int index = get_entry_index(dict, key);
    if (index != -1) {
        dict->entries[index].value += value;
        return 1;
    } else if (dict->count < dict->capacity) {
        dict->entries[dict->count].key = strdup(key);
        dict->entries[dict->count].value = value;
        dict->count++;
        return 1;
    }
    return 0;
}

Dictionary* combine_dictionaries(Dictionary *dict1, Dictionary *dict2) {
    Dictionary *combined = create_dictionary(dict1->count + dict2->count);
    if (combined == NULL) return NULL;

    for (int i = 0; i < dict1->count; ++i) {
        add_or_update_entry(combined, dict1->entries[i].key, dict1->entries[i].value);
    }

    for (int i = 0; i < dict2->count; ++i) {
        add_or_update_entry(combined, dict2->entries[i].key, dict2->entries[i].value);
    }

    return combined;
}

int main() {
    Dictionary *dict1 = create_dictionary(5);
    Dictionary *dict2 = create_dictionary(5);

    add_or_update_entry(dict1, "apple", 10);
    add_or_update_entry(dict1, "banana", 20);
    add_or_update_entry(dict2, "apple", 5);
    add_or_update_entry(dict2, "cherry", 15);

    Dictionary *combined = combine_dictionaries(dict1, dict2);

    if (combined != NULL) {
        for (int i = 0; i < combined->count; ++i) {
            printf("%s: %d\n", combined->entries[i].key, combined->entries[i].value);
        }
        destroy_dictionary(combined);
    }

    destroy_dictionary(dict1);
    destroy_dictionary(dict2);

    return 0;
}