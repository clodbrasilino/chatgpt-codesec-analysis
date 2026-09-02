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
    size_t capacity;
} Dictionary;

Dictionary* create_dictionary(size_t initial_capacity) {
    Dictionary *dict = (Dictionary *)malloc(sizeof(Dictionary));
    if (dict == NULL) return NULL;
    dict->entries = (DictionaryEntry *)malloc(initial_capacity * sizeof(DictionaryEntry));
    if (dict->entries == NULL) {
        free(dict);
        return NULL;
    }
    dict->count = 0;
    dict->capacity = initial_capacity;
    return dict;
}

void free_dictionary(Dictionary *dict) {
    for (size_t i = 0; i < dict->count; ++i) {
        free(dict->entries[i].key);
    }
    free(dict->entries);
    free(dict);
}

int add_entry(Dictionary *dict, const char *key, int value) {
    if (dict->count >= dict->capacity) {
        size_t new_capacity = dict->capacity * 2;
        DictionaryEntry *new_entries = (DictionaryEntry *)realloc(dict->entries, new_capacity * sizeof(DictionaryEntry));
        if (new_entries == NULL) return -1;
        dict->entries = new_entries;
        dict->capacity = new_capacity;
    }
    dict->entries[dict->count].key = strdup(key);
    if (dict->entries[dict->count].key == NULL) return -1;
    dict->entries[dict->count].value = value;
    dict->count++;
    return 0;
}

Dictionary* merge_dictionaries(Dictionary *dict1, Dictionary *dict2) {
    Dictionary *merged_dict = create_dictionary(dict1->count + dict2->count);
    if (merged_dict == NULL) return NULL;

    for (size_t i = 0; i < dict1->count; ++i) {
        if (add_entry(merged_dict, dict1->entries[i].key, dict1->entries[i].value) != 0) {
            free_dictionary(merged_dict);
            return NULL;
        }
    }

    for (size_t i = 0; i < dict2->count; ++i) {
        if (add_entry(merged_dict, dict2->entries[i].key, dict2->entries[i].value) != 0) {
            free_dictionary(merged_dict);
            return NULL;
        }
    }

    return merged_dict;
}

int main() {
    Dictionary *dict1 = create_dictionary(2);
    if (dict1 == NULL) return 1;
    if (add_entry(dict1, "key1", 10) != 0 || add_entry(dict1, "key2", 20) != 0) {
        free_dictionary(dict1);
        return 1;
    }

    Dictionary *dict2 = create_dictionary(2);
    if (dict2 == NULL) {
        free_dictionary(dict1);
        return 1;
    }
    if (add_entry(dict2, "key3", 30) != 0 || add_entry(dict2, "key4", 40) != 0) {
        free_dictionary(dict1);
        free_dictionary(dict2);
        return 1;
    }

    Dictionary *merged_dict = merge_dictionaries(dict1, dict2);
    if (merged_dict == NULL) {
        free_dictionary(dict1);
        free_dictionary(dict2);
        return 1;
    }

    for (size_t i = 0; i < merged_dict->count; ++i) {
        printf("%s: %d\n", merged_dict->entries[i].key, merged_dict->entries[i].value);
    }

    free_dictionary(dict1);
    free_dictionary(dict2);
    free_dictionary(merged_dict);
    return 0;
}